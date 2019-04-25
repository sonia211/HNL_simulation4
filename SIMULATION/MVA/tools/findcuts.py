#author: Guido Andreassi <guido.andreassi@cern.ch>

#this code finds an optimal set of cuts for a set of variables,
#in order to cut very long and almost empty tails that degrade the discriminant
#power of the variables in the MVA and the readibility of the plots

import numpy as np
import matplotlib.pyplot as plt
import ROOT
import os
from math import floor


def findcuts_old(chain, variables, entry_cut):

    print "entry cut: ", entry_cut

    threshold = 0.1

    #print "run1 entries:", chain_run1.GetEntries(cut_run1)
    #print "run2 entries:", chain_run2.GetEntries(cut_run2)
    total_cut = ROOT.TCut("1")
    for variable in variables:
        print variable
        h = ROOT.TH1D ("h", "h", 100, 0, 0)
        chain.Draw(variable+'>>h', entry_cut, 'goff')

        min_ = h.GetXaxis().GetXmin()
        max_ = h.GetXaxis().GetXmax()
        print "min, max = ", min_, max_,
        if (min_<max_):
            interval = float(max_-min_)
        else:
            #raise BaseException
            print "ERROR: this variables seems constant or not valid!"
            continue
        step = interval/10

        ntot = h.GetMaximum()#chain.GetEntries(entry_cut+" && "+total_cut.GetTitle())
        #print "ntot: ", ntot
        changes_min = 0
        changes_max = 0
        print ">>", variable+"<"+str(min_+step)
        print "threshold:", threshold*ntot
        print variable+"<"+str(min_+step), " :  ", chain.GetEntries(variable+"<"+str(min_+step))
        while ((chain.GetEntries(variable+"<"+str(min_+step))<threshold*ntot) and (min_<max_)):
            print ">>"
            min_ = min_+step
            interval = float(max_-min_)
            changes_min = changes_min+1
            step = interval/10
            ntot = h.GetMaximum()#chain.GetEntries(entry_cut+" && ("+variable+"<"+str(min_+step)+") && "+total_cut.GetTitle())
        print "<<", variable+">"+str(max_-step)
        print variable+">"+str(max_-step), " :  ", chain.GetEntries(variable+">"+str(max_-step))
        while ((chain.GetEntries(variable+">"+str(max_-step))<threshold*ntot) and (min_<max_)):
            print "<<"
            max_ = max_-step
            interval = float(max_-min_)
            changes_max = changes_max+1
            step = interval/10
            ntot = h.GetMaximum()#chain.GetEntries(entry_cut+" && ("+variable+">"+str(max_-step)+") && "+total_cut.GetTitle())


        cut = ROOT.TCut("")
        if (changes_min != 0):
            cut += ROOT.TCut(variable+">"+str(min_))

        if (changes_max != 0):
            cut += ROOT.TCut(variable+"<"+str(max_))

        #print cut.GetTitle()
        total_cut += cut

        del h

    print "Optimal cut: ", total_cut.GetTitle()
    eff = float(chain.GetEntries(entry_cut+" && "+total_cut.GetTitle()))/chain.GetEntries(entry_cut)
    print "Efficiency: ", eff
    return total_cut




def findcuts2(chain, variables, entry_cut):

    print "entry cut: ", entry_cut

    threshold = 0.01
    minimum_eff = 0.97

    #print "run1 entries:", chain_run1.GetEntries(cut_run1)
    #print "run2 entries:", chain_run2.GetEntries(cut_run2)
    total_cut = ROOT.TCut("")
    for variable in variables:
        #print variable
        bins = 200
        h = ROOT.TH1D ("h", "h", bins, 0, 0)
        chain.Draw(variable+'>>h', entry_cut, 'goff')

        min_ = h.GetXaxis().GetXmin()
        max_ = h.GetXaxis().GetXmax()

        if (min_<max_):
            interval = float(max_-min_)
        else:
            #raise BaseException
            print "ERROR: this variables seems constant or not valid!"
            continue

        nmax = h.GetMaximum()#chain.GetEntries(entry_cut+" && "+total_cut.GetTitle())
        #print "nmax: ", nmax


        margin = floor(0.05*bins)

        lowest_bin = int(h.FindFirstBinAbove(threshold*nmax)-margin)
        highest_bin = int(h.FindLastBinAbove(threshold*nmax)+margin)

        min_new = h.GetBinLowEdge (lowest_bin)
        max_new = h.GetBinLowEdge (highest_bin)+h.GetBinWidth(highest_bin)

        if (lowest_bin<=0):
            min_new = min_ #if the change is too small or even worse if it goes below the minimum, discard it
        if (highest_bin>=h.GetNbinsX()):
            max_new = max_ #if the change is too small or even worse if it goes below the minimum, discard it

        if (chain.GetEntries("("+entry_cut+") && ("+variable+">"+str(min_new)+")")<minimum_eff*chain.GetEntries(entry_cut)):
            min_new = min_ #if the cut is too little efficient, discard it
        if (chain.GetEntries("("+entry_cut+") && ("+variable+"<"+str(max_new)+")")<minimum_eff*chain.GetEntries(entry_cut)):
            max_new = max_ #if the cut is too little efficient, discard it

        cut = ROOT.TCut("")
        if (min_new != min_):
            cut += ROOT.TCut(variable+">"+str(min_new))
        if (max_new != max_):
            cut += ROOT.TCut(variable+"<"+str(max_new))

        #print "added cut: ", cut.GetTitle()
        #print "min_, max_ = ", min_, max_
        total_cut += cut

        del h

    print "Optimal cut: ", total_cut.GetTitle()
    eff = float(chain.GetEntries(entry_cut+" && "+total_cut.GetTitle()))/chain.GetEntries(entry_cut)
    print "Efficiency: ", eff
    return total_cut


"""
#for testing
import os
import cuts


from glob import glob
data_tree_run2 = ROOT.TChain('Lb2LemuTuple/DecayTree')

for file in glob(os.getenv("LBMICKJOBLOC")+"209/[0-1][0-9]/DVNtuple.root"):
    data_tree_run2.AddFile(file)
for file in glob(os.getenv("LBMICKJOBLOC")+"210/[0-1][0-9]/DVNtuple.root"):
    data_tree_run2.AddFile(file)


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


findcuts2(data_tree_run2, branches, (cuts.Lb_Lemu_sidebands+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle())
"""
