
# coding: utf-8

# In[1]:


from __future__ import division
import sys, os
tag = 0
decay = "emu"

import matplotlib as mpl
mpl.use('Agg') #use for python script mode
import matplotlib.pyplot as plt
plt.ioff()


# In[2]:


output_dir = 'gridscan_output/{0}/{1}'.format(decay, tag)
if not os.path.exists(output_dir):
    os.makedirs(output_dir)
plots_dir = 'plots/{0}/{1}'.format(decay, tag)
if not os.path.exists(plots_dir):
    os.makedirs(plots_dir)


# In[3]:


import numexpr
import os
import root_numpy
import ROOT
import cuts
from getdata.getdata import getData
import pandas as pd
from rep import utils
from sklearn.ensemble import GradientBoostingClassifier
from rep.report.metrics import RocAuc
from rep.metaml import GridOptimalSearchCV, FoldingScorer, RandomParameterOptimizer, SubgridParameterOptimizer
from rep.estimators import SklearnClassifier, TMVAClassifier, XGBoostRegressor, TheanetsClassifier, XGBoostClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.neural_network import MLPClassifier
from rep.metaml import RegressionParameterOptimizer
from rep.metaml import RandomParameterOptimizer
from sklearn.gaussian_process import GaussianProcess
from rep.report.metrics import OptimalMetric, ams
from sklearn.metrics import roc_curve, auc
import numpy as np
from sklearn.utils import check_array, check_consistent_length
from sklearn.utils.multiclass import type_of_target
from scipy.stats import randint, uniform
import random
import re
from tools.findcuts import findcuts2
default_stdout = sys.stdout #I need this to redirect the stdout back on screen at the end


# In[4]:


#define input variables
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
    'l1_OWNPV_CHI2+l2_OWNPV_CHI2',
    'l1_IPCHI2_OWNPV+l2_IPCHI2_OWNPV',
    'l1_ORIVX_CHI2+l2_ORIVX_CHI2',
    'l1_PT+l2_PT',
    'L0_OWNPV_CHI2',
    'L0_IPCHI2_OWNPV',
    'L0_ORIVX_CHI2',
    'L0_ENDVERTEX_CHI2',
    'L0_P',
    'L0_PT',
#    'L0_DIRA_OWNPV',
    'p_PT',
    'pi_PT',
    'p_P',
    'pi_P',
    'p_OWNPV_CHI2+pi_OWNPV_CHI2',
    'p_IPCHI2_OWNPV+pi_IPCHI2_OWNPV',
    'p_ORIVX_CHI2+pi_ORIVX_CHI2']

additional_branches = ['Lb_M'] #spectator variables and others


# In[5]:


#get kerberos token for eos
import getpass
os.system("echo %s | kinit gandreas@CERN.CH" %getpass.getpass()) 


# In[6]:


#%time
#get data and mc trees
MC_tree = ROOT.TChain('Lb2LemuTuple/DecayTree')
MC_tree.Add(os.getenv("GUIDOANAEOSLOC")+"tuples/S28/MC/Lb_Lemu_MC_2016_M*.root")

data_tree = ROOT.TChain('Lb2LemuTuple/DecayTree')
#temporary fix:
from glob import glob
for file in glob(os.getenv("LBMICKJOBLOC")+"209/[0-2][0-9]/DVNtuple.root"):
    data_tree.AddFile(file)
for file in glob(os.getenv("LBMICKJOBLOC")+"210/[0-2][0-9]/DVNtuple.root"):
    data_tree.AddFile(file)

#data_tree = getData(['Lb2LemuTuple/DecayTree'], dtype = 'CL16_S28')

#de-activate not needed branches since otherwise the tree will be very heavy to handle
#data_tree['Lb2LemuTuple/DecayTree'].SetBranchStatus('*', 0)
#for branch in branches+additional_branches:#
#    data_tree['Lb2LemuTuple/DecayTree'].SetBranchStatus(branch, 1)
#data_tree['Lb2LemuTuple/DecayTree'].SetBranchStatus("Lb_M", 1)



# In[7]:


import imp
import sys
imp.reload (sys.modules['tools.findcuts'])
from tools.findcuts import findcuts2


data_tree_cut = data_tree.CopyTree((cuts.Lb_Lemu_sidebands+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle())
MC_tree_cut = MC_tree.CopyTree((cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle())
treelist = ROOT.TList();
treelist.Add(data_tree_cut);
treelist.Add(MC_tree_cut);
total_tree = ROOT.TTree.MergeTrees(treelist)

preselection_cut = findcuts2(total_tree, branches, "1")
#preselection_cut


# In[8]:



#convert tree ntuples in train and test data with respectivle lables, under the form of pandas datasets
from tools.convert_data import convert_data

import imp
import sys
imp.reload (sys.modules['tools.convert_data'])


signal_training_cut = cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run1_full

#print signal_training_cut.GetTitle()
train_data, train_labels, test_data, test_labels = convert_data (MC_tree,
                                                                 (preselection_cut+cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle(),
                                                                 data_tree,
                                                                 (preselection_cut+cuts.Lb_Lemu_sidebands+cuts.Lb_Lemu_trigger_run2_full_for_MVA_training).GetTitle(),
                                                                 branches+additional_branches,
                                                                 test_frac = 0.2)

#let's also prepare signal and background in separate dataframes for convenience
train_data_with_labels = pd.DataFrame(np.hstack((train_data, train_labels.reshape(train_labels.shape[0], -1))),
                  columns=branches+additional_branches+['labels'])
test_data_with_labels = pd.DataFrame(np.hstack((test_data, test_labels.reshape(test_labels.shape[0], -1))),
                  columns=branches+additional_branches+['labels'])

train_data_signal_with_labels = train_data_with_labels.loc[train_data_with_labels['labels']>0.5]
train_data_background_with_labels = train_data_with_labels.loc[train_data_with_labels['labels']<0.5]
test_data_signal_with_labels = test_data_with_labels.loc[test_data_with_labels['labels']>0.5]
test_data_background_with_labels = test_data_with_labels.loc[test_data_with_labels['labels']<0.5]


# In[9]:


print train_data_signal_with_labels.shape[0]
print test_data_signal_with_labels.shape[0]
print train_data_background_with_labels.shape[0]
print test_data_background_with_labels.shape[0]


# In[10]:


#fraction of signal events in sidebands
tot = MC_tree.GetEntries((cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run2_full).GetTitle())
side = MC_tree.GetEntries((cuts.Lb_Lemu_matching+cuts.Lb_Lemu_trigger_run2_full+cuts.Lb_Lemu_sidebands).GetTitle())
print "Percentage of signal events in sidebands (normalised to total signal events after trigger cuts):", 100.*side/tot, "%"


# In[19]:


from tools.plot_sig_bkg import plot_sig_bkg
import imp
import sys
imp.reload (sys.modules['tools.plot_sig_bkg'])
for var in branches+additional_branches:
    plot_sig_bkg(train_data_signal_with_labels, train_data_background_with_labels, var, plots_dir)


# In[11]:


import imp
import sys
from math import exp, log
from tools.features_selection import entropy
from tools.features_selection import entropy_normalised


imp.reload (sys.modules['tools.features_selection'])
from tools.features_selection import entropy


scores = []
for branch in branches:
    res = entropy(train_data_signal_with_labels, train_data_background_with_labels, branch)
    scores.append(1./res['min entropy'])

branches_with_scores = pd.DataFrame(
    {'variable': branches,
     'score': scores,
    })

branches_with_scores=branches_with_scores.sort_values(by='score', ascending=False)


# In[21]:


fig = plt.figure(figsize=(10,10))
ax = fig.add_subplot(111)
pos = np.arange(5)+.5    # the bar centers on the y axis
ax.barh(range(len(branches_with_scores['variable'])),branches_with_scores['score'], align='center')
plt.yticks(range(len(branches_with_scores['variable'])), branches_with_scores['variable'])
plt.xlabel('Score')
plt.title(r'Input variables scores (entropy$^{-1}$)')
plt.tight_layout()
plt.ylim([-1,len(branches_with_scores['variable'])])
plt.gca().invert_yaxis() #otherwise it's lowest to highest
plt.savefig(plots_dir+"/scores.pdf") #replace is necessary for slashes, otherwise part of the name
plt.show()


# In[12]:


training_variables = branches_with_scores['variable'][:15].values.tolist() #the 15 best scored variables


# In[13]:


#now we have to change names to the input variables removing the mathematical symbols, otherwise tmva gets confused
branches = [var.replace("+","_PLUS_").replace("-","_MINUS_").replace("*","_TIMES_").replace("/","_OVER_") for var in branches]
training_variables = [var.replace("+","_PLUS_").replace("-","_MINUS_").replace("*","_TIMES_").replace("/","_OVER_") for var in training_variables]
train_data.columns = [var.replace("+","_PLUS_").replace("-","_MINUS_").replace("*","_TIMES_").replace("/","_OVER_") for var in train_data.columns]
test_data.columns = [var.replace("+","_PLUS_").replace("-","_MINUS_").replace("*","_TIMES_").replace("/","_OVER_") for var in test_data.columns]


# In[14]:


sys.stdout = default_stdout


#prepare normalised set for skMLP
from sklearn.preprocessing import StandardScaler  
scaler = StandardScaler()  
scaler.fit(train_data[training_variables])  
train_data_scaled = scaler.transform(train_data[training_variables])  
# apply same transformation to test data
test_data_scaled = scaler.transform(test_data[training_variables])  

scaled_training_variables = [var+"_scaled" for var in training_variables]
train_data_with_scaled_vars = pd.DataFrame(np.hstack((train_data, train_data_scaled.reshape(train_data_scaled.shape[0], -1))),
                  columns=(branches+additional_branches+scaled_training_variables))

test_data_with_scaled_vars = pd.DataFrame(np.hstack((test_data, test_data_scaled.reshape(test_data_scaled.shape[0], -1))),
                  columns=(branches+additional_branches+scaled_training_variables))



#re-do the dataframes with labels
train_data_with_scaled_vars_with_labels = pd.DataFrame(np.hstack((train_data_with_scaled_vars, train_labels.reshape(train_labels.shape[0], -1))),
                  columns=branches+additional_branches+scaled_training_variables+['labels'])
test_data_with_scaled_vars_with_labels = pd.DataFrame(np.hstack((test_data_with_scaled_vars, test_labels.reshape(test_labels.shape[0], -1))),
                  columns=branches+additional_branches+scaled_training_variables+['labels'])


# In[15]:


#The goal here is to optimise all the classifiers before comparing them

#So now we define grid search params for each classifier
grid_params = {} #empty dictionary (of dictionaries) of grid params
classifiers = {} #empty dictionary of classifiers

classifiers['TMVA_kBDT'] = TMVAClassifier(method='kBDT', features=training_variables)
grid_params['TMVA_kBDT'] = {}
grid_params['TMVA_kBDT']['Ntrees'] = randint(400, 2500)
grid_params['TMVA_kBDT']['MaxDepth'] = randint(2,6)
grid_params['TMVA_kBDT']['MinNodeSize'] = ['0.2%', '0.3%', '0.5%', '1%', '2%', '3%']
grid_params['TMVA_kBDT']['NCuts'] = randint(10,40)
grid_params['TMVA_kBDT']['AdaBoostBeta'] = uniform(0.05, 0.4)

classifiers['xgboost'] = XGBoostClassifier(features=training_variables)
grid_params['xgboost'] = {}
grid_params['xgboost']['n_estimators'] = randint(200, 2500)
#grid_params['xgboost']['gamma'] = randint(0, 1000) #minimum loss reduction required to make a further partition on a leaf node of the tree. The larger, the more conservative the algorithm will be.
grid_params['xgboost']['max_depth'] = randint(2,6)
grid_params['xgboost']['min_child_weight'] = randint(1,20)

classifiers['skboost'] = SklearnClassifier(GradientBoostingClassifier(), features=training_variables)
grid_params['skboost'] = {}
grid_params['skboost']['loss'] = ['deviance', 'exponential']
grid_params['skboost']['n_estimators'] = randint(50, 500)
grid_params['skboost']['max_depth'] = randint(2,6)
grid_params['skboost']['learning_rate'] = uniform(0.01, 0.2)
grid_params['skboost']['min_weight_fraction_leaf'] = uniform(0,0.05)

classifiers['Theanets'] = TheanetsClassifier(features=training_variables)
#filling list of possible sized of layers for Theanets
list_layers_theanets = [] 

for i in range(10): #10 different random configurations for each lenght
    for i in range(1,5):
        layer = []#[len(training_variables)] # the firs element is the size of the input layer
        for j in range(i):
            layer.append(random.randint(7,15))
        list_layers_theanets.append(layer)
    
grid_params['Theanets'] = {}
grid_params['Theanets']['layers'] = list_layers_theanets #layers configuration
grid_params['Theanets']['trainers']=[[{'learning_rate': 0.1, 'min_improvement': 0.1}],
                                    [{'learning_rate': 0.2, 'min_improvement': 0.1}],
                                    [{'learning_rate': 0.3, 'min_improvement': 0.1}],
                                    [{'learning_rate': 0.1, 'min_improvement': 0.2}],
                                    [{'learning_rate': 0.2, 'min_improvement': 0.2}],
                                    [{'learning_rate': 0.3, 'min_improvement': 0.2}],
                                    [{'learning_rate': 0.1, 'min_improvement': 0.3}],
                                    [{'learning_rate': 0.2, 'min_improvement': 0.3}],
                                    [{'learning_rate': 0.3, 'min_improvement': 0.3}],
                                    [{'learning_rate': 0.1, 'min_improvement': 0.4}],
                                    [{'learning_rate': 0.2, 'min_improvement': 0.4}],
                                    [{'learning_rate': 0.3, 'min_improvement': 0.4}]]

classifiers['skMLP'] = SklearnClassifier(MLPClassifier(), features=scaled_training_variables) #this needs the scaled variables
list_layers_skMLP = []
for k in range(5,50):
    for i in range(1,5):
        tuple_layer = ()
        kk=k
        for j in range(i):
            tuple_layer+=(kk,)
            kk = kk-1
        list_layers_skMLP.append(tuple_layer)     
        
grid_params['skMLP'] = {}
#grid_params['skMLP']['activation'] = ['identity', 'logistic', 'tanh', 'relu']
grid_params['skMLP']['solver'] = ['lbfgs', 'adam']#, 'sgd']
grid_params['skMLP']['hidden_layer_sizes'] = list_layers_skMLP #hidden layer configuration
grid_params['skMLP']['learning_rate_init'] = uniform(0.001, 0.2)
grid_params['skMLP']['alpha'] = 10.0 ** -np.arange(1, 7)


# Using gradient boosting with default settings
classifiers['GaussNB'] = SklearnClassifier(GaussianNB(), features=training_variables) #if I understand correctly this has only one parameter, which is better to leave free


# In[16]:


from tools.auc_no_overtrain import auc_no_overtrain
import datetime
#.strftime("%Y-%m-%d_%H:%M:%S")
    
#for each estimator, run the grid search
grid_finder = {}


for classifier in classifiers:
    if classifier is 'GaussNB': continue #GaussNB doesn't need to be optimised
 
    sys.stdout = open(output_dir+'/stdout_{1}.txt'.format(tag, classifier), 'w')
    now = datetime.datetime.now()
    print now
    generator = RandomParameterOptimizer(grid_params[classifier], n_evaluations=4)
    estimator = classifiers[classifier]
    scorer = auc_no_overtrain(train_data_with_scaled_vars_with_labels, test_data_with_scaled_vars_with_labels)
    grid_finder[classifier] = GridOptimalSearchCV(estimator, generator, scorer, parallel_profile='threads-16')
    grid_finder[classifier].fit(train_data_with_scaled_vars, train_labels)
    sys.stdout = open(output_dir+'/scores_{1}.txt'.format(tag, classifier), 'w')
    now = datetime.datetime.now()
    print now
    grid_finder[classifier].params_generator.print_results()
    
sys.stdout = default_stdout


# In[17]:


sys.stdout = default_stdout

#get report object, containing the info about performances
from rep.metaml import ClassifiersFactory

estim = {}

factory = ClassifiersFactory()
for classifier in classifiers:
        
    print "Training ", classifier, "..."
    if classifier is 'GaussNB':
        classifiers['GaussNB'].fit(train_data_with_scaled_vars, train_labels)
        estim[classifier]=classifiers['GaussNB']
    else:
        estim[classifier] = grid_finder[classifier].fit_best_estimator(train_data_with_scaled_vars, train_labels, sample_weight=None)
    factory.add_classifier(classifier, estim[classifier])

    print "done!"

report = factory.test_on(test_data_with_scaled_vars, test_labels)


# In[18]:


#plot roc curves
fig = plt.figure(figsize=(15,10))
report.roc(physics_notion=True).plot(xlim=(0, 1), ylim=(0, 1))
plt.savefig(plots_dir+"/rocs_all.pdf")
plt.show()


fig = plt.figure(figsize=(15,10))
report.roc(physics_notion=True).plot(xlim=(0, 1), ylim=(0.7, 1))
plt.savefig(plots_dir+"/rocs_all_zoommed.pdf")
plt.show()


# In[ ]:




