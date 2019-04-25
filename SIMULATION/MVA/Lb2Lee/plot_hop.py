import random,sys,os
from tools import signal_background,compare_train_test
import ROOT
import python.cuts
from getdata.getdata import getData

import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score
from root_numpy import root2array, rec2array, tree2array

from Lb2LemuEnv import *

sys.path.append(os.getenv("LB2LEMUROOT")+"/MVA/tools/")
from features_selection import entropy_normalised

def get_branches_tree(file_name,tree_name):
    branch_names = []
    rfile  = ROOT.TFile(file_name)
    tree   = rfile.Get(tree_name)
    branch_list = tree.GetListOfBranches()
    branch_names = []
    for i in branch_list:
        name = i.GetTitle().split("/")[0]
        if not "[" in name and not "MC" in name: branch_names.append(name)
    return branch_names


# NEED SOME CODE TO SET UP BRANCHES AT SOME POINT
# FOR NOW RUNNING OVER ALL BRANCHES
branch_names = """Lb_FDCHI2_OWNPV,Lb_HOP_MASS
""".split(",")
branch_names = [c.strip() for c in branch_names]
branch_names = (b.replace(" ", "_") for b in branch_names)
branch_names = list(b.replace("-", "_") for b in branch_names)

print "SET UP BRANCHES, NOW OPENING FILES"



tree = getData(['Lb2JpsiL_eeTuple/DecayTree'],dtype='MC16_JpsiL_ee')

sig_file =  "{0}samples/Lb2JpsiLeeCP_MC_{1}.root".format(loc.MICKANAEOS,"16")
bkg_file = "{0}samples/Lb2JpsiLee_Data_All.root".format(loc.MICKANAEOS)


n_lists  = len(branch_names)/list_len + 1 # FOR EXAMPLE IF 61 vars, n_lists = 4

# DEFINE CUTS
# TRIGGER
# HOP?
cut_shared = python.cuts.Lb_Lee_trig_Run2
cut_data   = (cut_shared+python.cuts.Lb_Lemu_sidebands+python.cuts.Data_2016).GetTitle()
cut_MC     = (cut_shared+python.cuts.Lb_JpsiL_ee_matching).GetTitle()


print "NOW MAKING SIGNAL SAMPLE"
# ADD CHECK THAT BRANCHES ARE IN BOTH FILES
signal = root2array( sig_file,'DecayTree',branch_names, selection= cut_MC )
signal = rec2array(signal)

print "NOW MAKING BACKGROUND SAMPLE"
backgr  = root2array(bkg_file,'DecayTree',branch_names,selection= cut_data)
backgr = rec2array(backgr)

X = np.concatenate((signal, backgr))
y = np.concatenate((np.ones(signal.shape[0]),np.zeros(backgr.shape[0])))

print "MAKING DATAFRAME"

# Create a pandas DataFrame for our data
# this provides many convenience functions
# for exploring your dataset
# need to reshape y so it is a 2D array with one column
df = pd.DataFrame(np.hstack((X, y.reshape(y.shape[0], -1))), columns=branch_names+['y'])

print "TIME TO PLOT"

for var in branch_names:


    plots = signal_background(df[df.y<0.5], df[df.y>0.5], column = var ,  bins=20)
    for plot in plots:
        
        for subplot in plot:
           plt.savefig('plots/{0}.pdf'.format(var))
