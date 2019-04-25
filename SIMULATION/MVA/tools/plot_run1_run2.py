#author: Guido Andreassi <guido.andreassi@cern.ch>


#plot vars
import numpy as np
import matplotlib.pyplot as plt
import ROOT
import os

def plot_run1_run2(chain_run1, chain_run2, variable, cut_run1, cut_run2, subfolder):

    #print "run1 entries:", chain_run1.GetEntries(cut_run1)
    #print "run2 entries:", chain_run2.GetEntries(cut_run2)

    variable = .replace("/", "_OVER_") #slashes make a mess when creating the plot file...

    c = ROOT.TCanvas("c")
    h_run1 = ROOT.TH1D ("h_run1_"+variable, "h_run1_"+variable, 100, 0, 0)
    chain_run1.Draw(variable+'>>h_run1_'+variable, cut_run1, 'goff')
    h_run2 = ROOT.TH1D ("h_run2_"+variable, "h_run2_"+variable, h_run1.GetNbinsX(), h_run1.GetXaxis().GetXmin(), h_run1.GetXaxis().GetXmax())
    chain_run2.Draw(variable+'>>h_run2_'+variable, cut_run2, 'goff')
   


    h_run1.SetLineColor(ROOT.kBlue-7);
    h_run1.SetFillColor(ROOT.kBlue-7);

    h_run2.SetLineColor(ROOT.kOrange+7);
    h_run2.SetFillColorAlpha(ROOT.kOrange+7, 0.3);

    #h_run1.DrawNormalized()
    #h_run2.DrawNormalized("same")
    h_run2.DrawNormalized()

    legend = ROOT.TLegend(0.70,0.85,0.9,0.75)
    legend.SetTextFont(72);                                                                                                                                         
    legend.SetTextSize(0.03);                                                                                                                        
    legend.AddEntry(h_run1,"Run1","l");
    legend.AddEntry(h_run2,"Run2","l");
    legend.Draw();

    plots_dir = "plots/variables_comparison_run1_run2/"+subfolder+"/"
    if not os.path.exists(plots_dir):
        os.makedirs(plots_dir)
    c.SaveAs(plots_dir+variable+"_run1_vs_run2.pdf")




    ################





##############

branches = ['Lb_TAU',
    'Lb_PT',
    'Lb_P',
    'Lb_OWNPV_CHI2/Lb_OWNPV_NDOF',
    'Lb_IPCHI2_OWNPV',
    'Lb_IP_OWNPV',
    'Lb_FDCHI2_OWNPV',
    'Lb_hop_LoKi_mass_bv',
    'Lb_ConeIsoInfoH1_CC_MULT',
    'Lb_ConeIsoInfoH2_CC_MULT',
    'Lb_ConeIsoInfoL1_CC_MULT+Lb_ConeIsoInfoL2_CC_MULT',
    'Lb_ConeIsoInfoH1_CC_PTASYM',
    'Lb_ConeIsoInfoH2_CC_PTASYM',
    'Lb_ConeIsoInfoL1_CC_PTASYM',
    'Lb_ConeIsoInfoL2_CC_PTASYM',
    'Lb_TrackIsoBDTInfoH1_TRKISOBDTFIRSTVALUE',
    'Lb_TrackIsoBDTInfoH2_TRKISOBDTFIRSTVALUE',
    'Lb_TrackIsoBDTInfoL1_TRKISOBDTFIRSTVALUE',
    'Lb_TrackIsoBDTInfoL2_TRKISOBDTFIRSTVALUE',
    'Lb_TrackIsoInfoH1_CONEMULT',
    'Lb_TrackIsoInfoH2_CONEMULT',
    'Lb_TrackIsoInfoL1_CONEMULT+Lb_TrackIsoInfoL2_CONEMULT',
    'Lb_VtxIsoBDT_VTXISOBDTHARDFIRSTVALUE',
    'Lb_VtxIso_VTXISODCHI2TWOTRACK',
    'L0_P']



import os
import cuts


from glob import glob
data_tree_run2 = ROOT.TChain('Lb2LemuTuple/DecayTree')

for file in glob(os.getenv("LBMICKJOBLOC")+"209/[0-4][0-9]/DVNtuple.root"):
    data_tree_run2.AddFile(file)
for file in glob(os.getenv("LBMICKJOBLOC")+"210/[0-4][0-9]/DVNtuple.root"):
    data_tree_run2.AddFile(file)



data_tree_run1 = ROOT.TChain('Lb2LemuTuple/DecayTree')

for file in glob(os.getenv("LBMICKJOBLOC")+"207/[0-3][0-6]/DVNtuple.root"):
    data_tree_run1.AddFile(file)
for file in glob(os.getenv("LBMICKJOBLOC")+"208/[0-3][0-6]/DVNtuple.root"):
    data_tree_run1.AddFile(file)


Optimal_cut = "((((((((((((((((((((((((1)&&(Lb_PT<33750.0))&&(Lb_P<591700.0))&&((Lb_OWNPV_CHI2/Lb_OWNPV_NDOF>0.186)&&(Lb_OWNPV_CHI2/Lb_OWNPV_NDOF<0.73005)))&&(Lb_IPCHI2_OWNPV<26.441))&&(Lb_IP_OWNPV<0.28798))&&(Lb_FDCHI2_OWNPV<12740.0))&&((Lb_hop_LoKi_mass_bv>1947.75)&&(Lb_hop_LoKi_mass_bv<10228.5)))&&(Lb_ConeIsoInfoH1_CC_MULT<10.725))&&(Lb_ConeIsoInfoH2_CC_MULT<10.78))&&(Lb_ConeIsoInfoL1_CC_MULT+Lb_ConeIsoInfoL2_CC_MULT<21.372))&&((Lb_ConeIsoInfoH1_CC_PTASYM>-1.0781)&&(Lb_ConeIsoInfoH1_CC_PTASYM<1.1215)))&&((Lb_ConeIsoInfoH2_CC_PTASYM>-1.0738)&&(Lb_ConeIsoInfoH2_CC_PTASYM<1.121)))&&((Lb_ConeIsoInfoL1_CC_PTASYM>-1.0588)&&(Lb_ConeIsoInfoL1_CC_PTASYM<1.122)))&&((Lb_ConeIsoInfoL2_CC_PTASYM>-1.062)&&(Lb_ConeIsoInfoL2_CC_PTASYM<1.121)))&&((Lb_TrackIsoBDTInfoH1_TRKISOBDTFIRSTVALUE>-0.187375)&&(Lb_TrackIsoBDTInfoH1_TRKISOBDTFIRSTVALUE<0.390475)))&&((Lb_TrackIsoBDTInfoH2_TRKISOBDTFIRSTVALUE>-0.196225)&&(Lb_TrackIsoBDTInfoH2_TRKISOBDTFIRSTVALUE<0.386025)))&&((Lb_TrackIsoBDTInfoL1_TRKISOBDTFIRSTVALUE>-0.17925)&&(Lb_TrackIsoBDTInfoL1_TRKISOBDTFIRSTVALUE<0.381375)))&&((Lb_TrackIsoBDTInfoL2_TRKISOBDTFIRSTVALUE>-0.17535)&&(Lb_TrackIsoBDTInfoL2_TRKISOBDTFIRSTVALUE<0.3767)))&&(Lb_TrackIsoInfoH1_CONEMULT<11.726))&&(Lb_TrackIsoInfoH2_CONEMULT<10.78))&&(Lb_TrackIsoInfoL1_CONEMULT+Lb_TrackIsoInfoL2_CONEMULT<21.372))&&((Lb_VtxIsoBDT_VTXISOBDTHARDFIRSTVALUE>-1.1021)&&(Lb_VtxIsoBDT_VTXISOBDTHARDFIRSTVALUE<0.41295)))&&((Lb_VtxIso_VTXISODCHI2TWOTRACK>-7475.0)&&(Lb_VtxIso_VTXISODCHI2TWOTRACK<9445.0)))&&(L0_P<171600.0)"

for var in branches:
    plot_run1_run2(data_tree_run1, data_tree_run2, var, Optimal_cut+" && "+(cuts.Lb_Lemu_sidebands+cuts.Lb_Lemu_trigger_run1_l0+cuts.Lb_Lemu_trigger_run1_hlt1).GetTitle(), Optimal_cut+" && "+(cuts.Lb_Lemu_sidebands+cuts.Lb_Lemu_trigger_run2_l0+cuts.Lb_Lemu_trigger_run2_hlt1).GetTitle(), "/")

