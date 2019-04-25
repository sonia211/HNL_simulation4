from argparse import ArgumentParser
parser = ArgumentParser()
parser.add_argument('-i','--input-emuMC-files', nargs='+', dest="infiles_names_emuMC",#infiles_names_emuMC is a list
                    help='List of input signal MC files (regexp allowed)', required=True)
parser.add_argument('-m','--input-mumuMC-files', nargs='+', dest="infiles_names_mumuMC",#infiles_names_emuMC is a list
                    help='List of input mumu MC files (regexp allowed)', required=True)
parser.add_argument('-d','--input-mumudata-files', nargs='+', dest="infiles_names_mumudata",#infiles_names_emuMC is a list
                    help='List of input mumu MC files (regexp allowed)', required=True)
parser.add_argument('-r', '--run', type=int, dest="run",
					help='LHC run.')
parser.add_argument('-b', '--nbins', type=int, dest="nbins", default=20,
                    help='Number of bins')
parser.add_argument('--decay', type=str, dest="decay", default="emu",
                    help='Decay (ee or emu)')
opts = parser.parse_args()



import ROOT
from Lb2LemuEnv import loc, xroot
import cuts
from tools.hist_ratio import hist_ratio
from Lb2LemuEnv import db
from Lb_reweighting.getweight import get_P_PT_reco_weight_from_event


Lb2JpsiL_MM_presel = cuts.Lb2JpsiL_MM_presel_RunI if opts.run==1 else cuts.Lb2JpsiL_MM_presel_RunII
run_cut = cuts.data_cut["Run1"] if opts.run==1 else cuts.data_cut["Run2"]
decay = "emu"
tag = db["best_classifier_tag_"+decay]
best_classifier_name = db["best_classifier_name_"+decay]
mva_var = best_classifier_name+str(tag)

mva_fixhop_var = mva_var+"_fixhop"

t = ROOT.TChain("DecayTree")
for f in opts.infiles_names_emuMC:
    t.AddFile(f)


h = ROOT.TH1D(mva_var, "Nominal", opts.nbins, -1, 1)
h_fixhop = h.Clone()
h_fixhop.SetTitle("Fixed HOP")
h_fixhop.SetName(mva_var+" fixed HOP")

#formula = ROOT.TTreeFormula("truth_matching_cut", cuts.Lb_Lemu_matching.GetTitle(), t)
formula = ROOT.TTreeFormula("truth_matching_cut", (cuts.Lb_Lemu_HOP_FD_cut+cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle(), t)

t.SetNotify(formula)
for event in t:
    if formula.EvalInstance():
        h.Fill(getattr(event, mva_var), get_P_PT_reco_weight_from_event(event, opts.run))
        h_fixhop.Fill(getattr(event, mva_fixhop_var), get_P_PT_reco_weight_from_event(event, opts.run))

import imp
import sys
imp.reload (sys.modules['tools.hist_ratio'])
r = hist_ratio(h, h_fixhop)
r.Plot()
r.saveAsCandPdf(loc.PLOTS+"MVA_fixhop_MC_ratio")

####################


#now the real ratio: mumu s-weighted data over mumu MC
sweightvar = "nsig_Lb2JpsiL_MM_sw"
t_data = ROOT.TChain("DecayTree")
for f in opts.infiles_names_mumudata:
    t_data.AddFile(f)

t_MC = ROOT.TChain("DecayTree")
for f in opts.infiles_names_mumuMC:
    t_MC.AddFile(f)


h_data = ROOT.TH1D(mva_var, "data", opts.nbins, -1, 1)
h_MC = h_data.Clone()
h_MC.SetTitle("simulation")
h_MC.SetName(mva_var+" simulation")

#these data are already cut

formula = ROOT.TTreeFormula("cut_mm_MC", (run_cut).GetTitle(), t_data)
t_data.SetNotify(formula)
for event in t_data:
    if formula.EvalInstance():
        h_data.Fill(getattr(event, mva_fixhop_var), getattr(event, sweightvar))


formula = ROOT.TTreeFormula("cut_mm_MC", (cuts.Lb_JpsiL_mm_matching+Lb2JpsiL_MM_presel).GetTitle(), t_MC)
t_MC.SetNotify(formula)
for event in t_MC:
	if formula.EvalInstance():
		h_MC.Fill(getattr(event, mva_fixhop_var), get_P_PT_reco_weight_from_event(event, opts.run))

r2 = hist_ratio(h_MC, h_data)
r2.Plot()
r2.saveAsCandPdf(loc.PLOTS+"MVA_fixhop_ratio")
r2.get_h_ratio().SetName(r2.get_h_ratio().GetName()+"_"+mva_var)
h_weights = r2.get_h_ratio().Clone()
r2.save_h_ratio(loc.ROOT+"/MVA/MVA_reweighting_hist_{0}_run{1}.root".format(opts.decay, opts.run))


### scan cut efficiency
h_eff_MC = h_data.Clone()
h_eff_MC.SetTitle("MC")
h_eff_MC.SetName("eff_MC")
h_eff_data = h_data.Clone()
h_eff_data.SetTitle("data (sweighted)")
h_eff_data.SetName("eff_data")

print "Cut efficiency:"
for a in range(1,opts.nbins+1):
    cut = h_MC.GetBinLowEdge(a)
    eff_MC = (float)(h_MC.Integral(a,opts.nbins))/h_MC.Integral()
    eff_data = (float)(h_data.Integral(a,opts.nbins))/h_data.Integral()
    print "cut: {0} \t MC: {1} \t data: {2} \t relative diff: {3}%".format(cut, eff_MC, eff_data, 100*(eff_data-eff_MC)/eff_MC)

    h_eff_MC.SetBinContent(a, eff_MC)
    h_eff_data.SetBinContent(a, eff_data)

#make histogram of efficiencies
r_eff = hist_ratio(h_eff_MC, h_eff_data, normalize=False)
r_eff.set_legend_xyxy(0.2,0.35,0.5,0.55)
r_eff.set_y_title("Cut efficiency")
r_eff.Plot()
r_eff.saveAsCandPdf(loc.PLOTS+"MVA_fixhop_eff")






#### use weights to check variables:
  
from vars_db import vars_db
training_variables = [var for var in vars_db if vars_db[var]['in_MVA']==True]
import re
math_operators = ["+", "-", "*", "/"]
bad_chars = ["(", ")", "sqrt", "log", "|", "abs", "fabs"]
for var in list(training_variables):
    if any (operator in var for operator in math_operators):
            training_variables.remove(var)
            vars = re.split("|".join("\\"+operator for operator in math_operators), var)
            for v in vars:
                for c in bad_chars:
                    v = v.replace(c, "")
            training_variables.extend(vars)
            print "Replaced {0} with {1}".format(var, vars)
#training_variables.append(mva_fixhop_var)

for var in training_variables:
    if var is "Lb_HOP": continue
    print "Plotting", var, "..."
    h_var_data = ROOT.TH1D(var+"_data", vars_db[var]["title"]+" data", vars_db[var]["binning"][0], vars_db[var]["binning"][1], vars_db[var]["binning"][2])
    h_var_MC = ROOT.TH1D(var+"_MC", vars_db[var]["title"]+" MC", vars_db[var]["binning"][0], vars_db[var]["binning"][1], vars_db[var]["binning"][2])
    h_var_wMC = ROOT.TH1D(var+"_wMC", vars_db[var]["title"]+" MC (weighted)", vars_db[var]["binning"][0], vars_db[var]["binning"][1], vars_db[var]["binning"][2])

    for event in t_data:
        h_var_data.Fill(getattr(event, var), getattr(event, sweightvar))
    for event in t_MC:
        if formula.EvalInstance():
            w = h_weights.GetBinContent(h_weights.FindBin(getattr(event, mva_fixhop_var)))
            h_var_wMC.Fill(getattr(event, var), w*get_P_PT_reco_weight_from_event(event, opts.run))
            h_var_MC.Fill(getattr(event, var), get_P_PT_reco_weight_from_event(event, opts.run))

    c = ROOT.TCanvas()
    s = ROOT.THStack("hstack", "")
    h_var_MC.SetLineColor(ROOT.kRed)
    h_var_wMC.SetLineColor(ROOT.kGreen)
    h_var_data.Scale(1./h_var_data.Integral())
    h_var_MC.Scale(1./h_var_MC.Integral())
    h_var_wMC.Scale(1./h_var_wMC.Integral())
    s.Add(h_var_data)
    s.Add(h_var_MC, "hist")
    s.Add(h_var_wMC, "hist")
    s.Draw("nostack")

    c.SaveAs(loc.PLOTS+"/MVA_rw/"+var+".pdf")
    c.SaveAs(loc.PLOTS+"/MVA_rw/"+var+".C")
  
