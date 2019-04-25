import random
from tools import signal_background,compare_train_test
import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score
from root_numpy import root2array, rec2array

from Lb2LemuEnv import *

branch_names = """l1_IPCHI2_OWNPV,l2_IPCHI2_OWNPV,Lb_FDCHI2_OWNPV,p_PT,pi_PT,pi_IPCHI2_OWNPV,p_IPCHI2_OWNPV
""".split(",")
branch_names = [c.strip() for c in branch_names]
branch_names = (b.replace(" ", "_") for b in branch_names)
branch_names = list(b.replace("-", "_") for b in branch_names)

signal = root2array("{0}samples/Lb2JpsiLeeCP_MC_16.root".format(loc.MICKANAEOS),"DecayTree",branch_names)
signal = rec2array(signal)

backgr = root2array("{0}samples/Lb2Lee_Data_AllData_Jps6_BothTT_AllL0_AllBrem_high_mass.root".format(loc.MICKANAEOS),"DecayTree",branch_names)
backgr = rec2array(backgr)




X = np.concatenate((signal, backgr))
y = np.concatenate((np.ones(signal.shape[0]),
                    np.zeros(backgr.shape[0])))

# SIG FRAME
df_sig = pd.DataFrame(np.hstack(signal)),columns=branch_names)
df_bbk = pd.DataFrame(np.hstack(backgr)),columns=branch_names)


print "MAKING DATAFRAME"

# Create a pandas DataFrame for our data
# this provides many convenience functions
# for exploring your dataset
# need to reshape y so it is a 2D array with one column
df = pd.DataFrame(np.hstack((X, y.reshape(y.shape[0], -1))),
                  columns=branch_names+['y'])

print "TIME TO PLOT"

#plots = signal_background(df[df.y<0.5], df[df.y>0.5],  column=branch_names,  bins=20)

#plots[0].plot()

#boxplot = df.boxplot(by='y', column=branch_names, return_type='axes')

#boxplot.plot()

print "TIME TO TRAIN"



