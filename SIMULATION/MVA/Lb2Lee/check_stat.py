import cuts
from ROOT import TCanvas,gROOT,TCut, TFile
from getdata.getdata import getData
gROOT.SetBatch()

mc_cut   = cuts.Lb_JpsiL_ee_matching+cuts.Lb_Lee_trig_Run2
data_cut = cuts.Lb_Lemu_sidebands+cuts.Lb_Lee_trig_Run2

loc = "/eos/lhcb/user/m/mmulder/Lb2Lee/"

try:
    sig = TFile.Open(loc+"sig_train_Lb2Lee.root")
    tree_sig = sig.Get("DecayTree")
    tree_sig.GetEntries()

except:
    sig = getData(['Lb2JpsiL_eeCPTuple/DecayTree'],dtype="MC16_JpsiL_ee")
    tree_sig = sig['Lb2JpsiL_eeCPTuple/DecayTree']

    file_sig_cut = TFile.Open(loc+"sig_train_Lb2Lee.root","RECREATE")
    tree_sig_cut = tree_sig.CopyTree(mc_cut.GetTitle())
    file_sig_cut.Write()
    file_sig_cut.Close()

    sig = TFile.Open(loc+"sig_train_Lb2Lee.root")
    tree_sig = sig.Get("DecayTree")
    tree_sig.GetEntries()

try:
    bkg = TFile.Open(loc+"bkg_train_Lb2Lee.root")
    tree_bkg = bkg.Get("DecayTree")
    tree_bkg.GetEntries()
    tree_bkg.Draw("Lb_MM")

except:
    bkg = getData(['Lb2JpsiL_eeCPTuple/DecayTree'],dtype="CL16_S28")
    tree_bkg = bkg['Lb2JpsiL_eeCPTuple/DecayTree']

    file_bkg_cut = TFile.Open(loc+"bkg_train_Lb2Lee.root","RECREATE")
    tree_bkg_cut = tree_bkg.CopyTree(data_cut.GetTitle())
    file_bkg_cut.Write()
    file_bkg_cut.Close()

    bkg = TFile.Open(loc+"bkg_train_Lb2Lee.root")
    tree_bkg = bkg.Get("DecayTree")
    tree_bkg.GetEntries()


print tree_sig.GetEntries( mc_cut.GetTitle())
print tree_bkg.GetEntries(data_cut.GetTitle())

c = TCanvas("c","c",1600,900)

tree_bkg.SetLineColor(2)


# NOW RUN OVER ALL THE VARIABLES
for i in range(tree_sig.GetListOfBranches().GetEntries()):
    var = tree_sig.GetListOfBranches().At(i).GetName()

    tree_sig.Draw(var,"1./{0}".format(str(tree_sig.GetEntries())))
    tree_bkg.Draw(var,"1./{0}".format(str(tree_bkg.GetEntries())),"SAME")
    c.SaveAs("plots/{0}.pdf".format(var))

