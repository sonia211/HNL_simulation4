import random,sys,os
from tools import signal_background,compare_train_test,correlations
import ROOT
import python.cuts
from  python.vars_db_Lb2Lee import vars_db
from getdata.getdata import getData

from glob import glob

from corr_plot import corr_plot

import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.lines as lines

from sklearn import datasets,cross_validation
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier,GradientBoostingClassifier
from sklearn.metrics import classification_report, roc_auc_score
from root_numpy import root2array, rec2array, tree2array

from Lb2LemuEnv import *
from locations import dataids

sys.path.append(os.getenv("LB2LEMUROOT")+"/MVA/tools/")
from features_selection import entropy_normalised

from optparse import OptionParser

#import xgboost as xgb



parser = OptionParser()
parser.add_option("-c","--compare",      dest = "Compare",    action = "store_true")
parser.add_option("-m",                  dest = "MassCorr",   action = "store_true")
parser.add_option("-p","--plot",         dest = "Plot",       action = "store_true")
parser.add_option("-t","--train",        dest = "Train",      action = "store_true")

parser.add_option("--dataset",           dest = "dataset",    choices = ["All","Run1","Run2","2011","2012","2015","2016","2017"], default = "2016")
parser.add_option("--decay",             dest = "decay",      choices = ["Lb_Lee","Lb_JpsiL_ee","Lb_Lemu","Lb_Lmm"], default = "Lb_Lee")
parser.add_option("--strip_line",        dest = "strip_line", choices = ["Lb2JpsiL_ee","Lb2JpsiL_mm"], default = "Lb2JpsiL_ee")
parser.add_option("--brem_cat",          dest = "brem_cat",   choices = ["All","NoBrem","1Brem","2Brem"], default = "All")
parser.add_option("--tt","--track_type", dest = "trk_type",   choices = ["All","DD","LL"], default = "All")
parser.add_option("--q2",                dest = "q2",         choices = ["All",'ulow',"low","mid",'lowmid',"high","Jps","Jps6","Psi2S"], default = "All")

parser.add_option("--branches",          dest = "branches",   choices = ["Small","MVA","MVA_plus","MVA_check","All","Explore"], default = "MVA")


(options,args) = parser.parse_args()

type_name = "{3}_Data{2}_{4}_{5}q2_{0}_{1}".format(options.branches,options.trk_type,options.dataset,options.decay,options.brem_cat,options.q2)



#def feature_importances_(self):
#    total_sum = np.zeros((self.n_features, ), dtype=np.float64)
#    for tree in self.estimators_:
#        tree = tree[0]# SOMEHOW LOOPING OVER ESTIMATORS STILL GIVES SINGLE ENTRY ARRAYS SO [0] ADDED
#        tree.compute_feature_importances(normalize=True)
#        total_sum += tree[0].feature_importances_     
#        importances = total_sum / len(self.estimators_)
#    return importances

# FUNCTION THAT TAKES A SAMPLE AND COMPUTES THE HOP EFFICIENCY 
def eff_hop(sample,const,slope):
    return float(sample.loc[sample['Lb_hop_LoKi_mass_bv']>const+slope*sample['log(Lb_FDCHI2_OWNPV)']].shape[0])/sample.shape[0]
 
def eff_hop_grid(sig,bkg):

    max_ratio, max_i, max_j,max_sig,max_bkg = {},{},{},{},{}
    sig_effis = [0.999,0.998,0.995,0.99,0.98,0.97,0.95,0.90,0.85,0.80]
    n_i,n_j = 100,100

    for effi in sig_effis:
        max_ratio[effi]=0.

    for i in range(n_i):
        for j in range(n_j):
            sig_effi = eff_hop(sig,4000*i/n_i,400*j/n_j)
            bkg_effi = eff_hop(bkg,4000*i/n_i,400*j/n_j)

            for effi in sig_effis:
                if sig_effi > effi:
                    if 4000*i/n_i == 2080 and 400*j/n_j == 248: 
                        print "At const =",4000*i/n_i,"and",400*j/n_j
                        print "Sig effi =",sig_effi 
                        print "Bkg effi =",bkg_effi
                        print "sig/bkg  =",sig_effi/bkg_effi
                    if sig_effi/bkg_effi > max_ratio[effi]: 
                        max_ratio[effi] = sig_effi/bkg_effi
                        max_i[effi]     = i
                        max_j[effi]     = j
                        max_sig[effi]   = sig_effi
                        max_bkg[effi]   = bkg_effi

    for effi in sig_effis:

        print "Minimal sig_effi:",effi
        print "At const =",4000*max_i[effi]/n_i,"and",400*max_j[effi]/n_j
        print "Sig effi =",max_sig[effi] 
        print "Bkg effi =",max_bkg[effi]
        print "sig/bkg  =",max_ratio[effi]

# NEED A FIX FOR WRONG SAMPLES; FOR NOW INCLUDE CHECK IN THIS WAY
wrong = ["/eos/lhcb/user/m/mmulder/ganga/210/363/DVNtuple.root","/eos/lhcb/user/m/mmulder/ganga/207/239/DVNtuple.root"]

def get_sample(dtype):
    sample = dataids[dtype] 
    files = []
    for job_id in sample[1]:
        string = "{0}{1}/*/DVNtuple.root".format(sample[0],job_id)
        file_list  = glob.glob(string)
        for i in wrong:
            if i in file_list: file_list.remove(i)
        files += file_list
    return files


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

def roc_plot(bdt,X_test,y_test,options):
    from sklearn.metrics import roc_curve, auc

    decisions = bdt.decision_function(X_test)
    # Compute ROC curve and area under the curve
    fpr, tpr, thresholds = roc_curve(y_test, decisions)
    roc_auc = auc(fpr, tpr)

    plt.plot(fpr, tpr, lw=1, label='ROC (area = %0.2f)'%(roc_auc))

    plt.plot([0, 1], [0, 1], '--', color=(0.6, 0.6, 0.6), label='Luck')
    plt.xlim([-0.05, 1.05])
    plt.ylim([-0.05, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver operating characteristic')
    plt.legend(loc="lower right")
    plt.grid()

#################
### LOAD DATA ###
#################
if options.dataset in ["Run1",'Run2','All']:
     datasets = datasets_db[options.dataset]
else datasets = [options.dataset]

sig_files = []
bkg_files = []

for dataset in datasets:
    sig_dtype='MC{0}_Filtered_{1}'.format(options.dataset[2:],options.decay)
    bkg_dtype='CL{0}'.format(options.dataset[2:])

    sig_files += get_sample(sig_dtype)
    bkg_files += get_sample(bkg_dtype)

# LOAD BRANCHES
# FIXME: WORK WITH LOADING TOTAL DATASET
if options.branches == "All":
    branch_sig = get_branches_tree(sig_files[0],"DecayTree")
    branch_bkg = get_branches_tree(bkg_files[0],"DecayTree")

    branch_names = [branch for branch in branch_sig if branch in branch_bkg]


else:  
    if options.branches == "MVA_check":
        branch_names = [branch for branch in vars_db if vars_db[branch]['considered_for_MVA']] 
    elif options.branches == "MVA":
        branch_names = [branch for branch in vars_db if vars_db[branch]['in_MVA']] 
    elif options.branches == "MVA_plus":
        branch_names = [branch for branch in vars_db if vars_db[branch]['in_MVA']] 
        for var in ["Lb_VtxIso_VTXISODCHI2MASSONETRACK","L0_M","Lb_TAU","L0_TAU","Lb_DIRA_OWNPV","L0_PT","L0_ENDVERTEX_Z"]:
            if var not in branch_names: branch_names.append(var)
    elif options.branches == "Explore":
        branch_names = [branch for branch in vars_db]
    elif options.branches == "Small":
        branch_names =  """l1_IPCHI2_OWNPV,l2_IPCHI2_OWNPV,Lb_FDCHI2_OWNPV,p_PT,pi_PT,pi_IPCHI2_OWNPV,p_IPCHI2_OWNPV,pi_TRACK_Type,Lb_HOP
        """.split(",")

    if options.Plot: 
        branch_names.append("log(Lb_FDCHI2_OWNPV)")
        branch_names.append("Lb_hop_LoKi_mass_bv")          
    if options.Train or options.Plot:
        branch_names.append("Lb_MM")
        branch_names.append("Lb_M23")
        branch_names.append("Lb_M23**2")
    if options.Train: 
        branch_names.append("Lb_DTF_Lambda_PV_M[0]")

    branch_names = [c.strip() for c in branch_names]
    branch_names = (b.replace(" ", "_") for b in branch_names)
    branch_names = list(b.replace("-", "_") for b in branch_names)
    n_lists = 1


if not "MVA" in options.branches:
    # TO MAKE SURE NOT TOO MANY VARS ARE IN FRAME
    list_len = 20
    n_lists  = len(branch_names)/list_len + 1 # FOR EXAMPLE IF 61 vars, n_lists = 4
else:
    list_len = len(branch_names)


# DEFINE CUTS: SIDEBANDS+2016 vs MATCHING AND  
# HOP?
cut_shared = python.cuts.Lb2Lee_presel_tight

if   options.trk_type == "DD": cut_shared += python.cuts.DD
elif options.trk_type == "LL": cut_shared += python.cuts.LL

if  options.brem_cat == "NoBrem" : cut_shared += python.cuts.NoBrem
elif options.brem_cat == "1Brem" : cut_shared += python.cuts.OneBrem
elif options.brem_cat == "2Brem" : cut_shared += python.cuts.TwoBrem

cut_shared += python.cuts.q2_cut[options.q2]

cut_data   = (cut_shared+python.cuts.Lb_Lee_sidebands+python.cuts.data_cut[options.dataset]).GetTitle()
cut_MC     = (cut_shared+python.cuts.Lb_Lee_matching).GetTitle()




for i in range(n_lists):
    #print i*list_len
    branch_names_short = branch_names[i*list_len:(i+1)*list_len]
    print "These are the branches considered: ", branch_names_short
    if options.branches == "All":
        print (len(branch_sig))
        print (len(branch_names_short))

    print "NOW MAKING SIGNAL SAMPLE"
    # ADD CHECK THAT BRANCHES ARE IN BOTH FILES 
    j = 0
    for f in sig_files:
        if j == 0:
            signal = root2array(f,options.strip_line+"Tuple/DecayTree",branch_names_short, selection= cut_MC )
            signal = rec2array(signal)
            j += 1
        else: 
            tmp    = root2array(f,options.strip_line+"Tuple/DecayTree",branch_names_short, selection= cut_MC )
            tmp    = rec2array(tmp)
            signal = np.concatenate((signal,tmp))

    print "NOW MAKING BACKGROUND SAMPLE"

    j = 0
    for f in bkg_files:
        if j == 0:
            backgr = root2array(f,options.strip_line+"Tuple/DecayTree",branch_names_short, selection= cut_data )
            backgr = rec2array(backgr)
            j += 1
        else: 
            tmp    = root2array(f,options.strip_line+"Tuple/DecayTree",branch_names_short, selection= cut_data )
            tmp    = rec2array(tmp)
            backgr = np.concatenate((backgr,tmp))

    print "Signal entries = ",signal.shape[0]
    print "Background entries = ",backgr.shape[0]

    X = np.concatenate((signal, backgr))
    y = np.concatenate((np.ones(signal.shape[0]),np.zeros(backgr.shape[0])))

    print "MAKING DATAFRAME"

    # Create a pandas DataFrame for our data
    # this provides many convenience functions
    # for exploring your dataset
    # need to reshape y so it is a 2D array with one column
    df = pd.DataFrame(np.hstack((X, y.reshape(y.shape[0], -1))), columns=branch_names_short+['y'])

    # FIX FOR ARRAY VARS
    array_vars = ["Lb_DTF_Lambda_PV_M[0]"]
    for var in array_vars:
        if var in df:
            df[var]=df[var].astype(str).str.replace('[','')
            df[var]=pd.to_numeric(df[var].astype(str).str.replace(']',''))


    if options.Compare:
        print "TIME TO COMPARE"
        comp_dict = {}         

        for var in branch_names_short:
            try:
                entropy = entropy_normalised(df[df.y<0.5], df[df.y>0.5],  var)
                #print var,entropy
                comp_dict[var]=entropy['min entropy']
            except ValueError:
                print ("THIS VARIABLE, {0}, IS USELESS".format(var))

        sort_list = sorted(comp_dict,key=comp_dict.__getitem__)
        sort_vals = sorted(comp_dict.values())

        for i in range(len(sort_list)):
            print sort_list[i],sort_vals[i]
            

    if options.Plot:
        print "TIME TO PLOT"

        for var in branch_names_short:

            plots = signal_background(df[df.y<0.5], df[df.y>0.5], column = var ,  bins=20)

            for plot in plots:    
                for subplot in plot:
                   plt.savefig('plots/{3}_Data{2}_{4}_{5}q2_{1}_{0}.pdf'.format(var.replace('/','_'),options.trk_type,options.dataset,options.decay,options.brem_cat,options.q2))


        # PLOT CORRELATIONS
        bg = df.y < 0.5
        sig = df.y > 0.5

        print 40*"#"
        print "#### CORRELATIONS FOR BACKGROUND"
        print 40*"#"

        corr_bkg = correlations(df[bg].drop('y', 1)) 
        plt.savefig('plots/{0}_corr_bkg.pdf'.format(type_name))

        print 40*"#"
        print "#### CORRELATIONS FOR SIGNAL"
        print 40*"#"


        corr_sig = correlations(df[sig].drop('y', 1))
        plt.savefig('plots/{0}_corr_sig.pdf'.format(type_name))


        print 40*"#"
        print "#### PLOTS FOR HOP"
        print 40*"#"

        plt.close("all")


        scatter = df[bg].plot( kind='scatter',
                                    y='Lb_hop_LoKi_mass_bv',
                                    x='log(Lb_FDCHI2_OWNPV)',
                                    xlim=(4,14),
                                    ylim=(1200,10000),
                                    edgecolors='None',
                                    color = 'red',
                                    label = 'Background (data)',
                                    s = 3, 
                                   )


        signal_mhist = df[sig].plot(kind='scatter',
                                    y='Lb_hop_LoKi_mass_bv',
                                    x='log(Lb_FDCHI2_OWNPV)',
                                    xlim=(4,14),
                                    ylim=(1200,10000),
                                    edgecolors='None',
                                    color = 'blue',
                                    label = 'Signal (MC)',
                                    s = 3, 
                                    ax = scatter
                                   )

        if options.q2 in ['ulow','low','mid','lowmid']:
            # ADD LINE WITH HOP MASS CUT
            def linear_cut(x): return 2080+248*x

            line_point1 = ( 4,linear_cut( 4))
            line_point2 = (14,linear_cut(14))

            (line_xs,line_ys)= zip(*[line_point1,line_point2]) 
            scatter.add_line(lines.Line2D(line_xs,line_ys,linewidth=2,color='black'))


        plt.savefig('plots/{0}_HOP_FDCHI2.pdf'.format(type_name))
        plt.close("all")

        # CHECK EFFICIENCY FOR ALL KINDS OF HOP CUTS
        eff_hop_grid(df[sig],df[bg])

    if options.Train:
        print "TIME TO TRAIN"
        
        from sklearn import grid_search 
        from sklearn.cross_validation import train_test_split,cross_val_score,StratifiedKFold

        X_full  = X
        X       = np.delete(X, np.s_[-4:], axis=1) 

        X_dev,X_eval, y_dev,y_eval = train_test_split(X, y,test_size=0.33, random_state=42)

        param_grid = {"n_estimators"  : [100,200,500],
                      "max_leaf_nodes": [2,4,8],
                      "learning_rate" : [0.1,0.2,0.5] }      
 
        n_kfolds = 3

        bdt = GradientBoostingClassifier(max_leaf_nodes=2,n_estimators=200,learning_rate=0.5,random_state=42)
        clf = grid_search.GridSearchCV(bdt,param_grid,scoring = "roc_auc",n_jobs=6,cv=StratifiedKFold(y,n_kfolds,shuffle=True))          
        clf.fit(X_dev, y_dev)

        print "Best parameter set found on development set:"
        print
        print clf.best_estimator_
        print
        print "Grid scores on a subset of the development set:"
        print
        for params, mean_score, scores in clf.grid_scores_:
            print "%0.4f (+/-%0.04f) for %r"%(mean_score, scores.std(), params)
        print
        print "With the model trained on the full development set:"

        y_true, y_pred = y_dev, clf.decision_function(X_dev)
        print "  It scores %0.4f on the full development set"%roc_auc_score(y_true, y_pred)
        y_true, y_pred = y_eval, clf.decision_function(X_eval)
        print "  It scores %0.4f on the full evaluation set"%roc_auc_score(y_true, y_pred)

        print "  Now train with cross validation and best parameter set"
        
        scores = cross_val_score(clf.best_estimator_,X_dev,y_dev,scoring="roc_auc",n_jobs=6,cv=StratifiedKFold(y,n_kfolds,shuffle=True))
        print "Accuracy: %0.5f (+/- %0.5f)"%(scores.mean(), scores.std())
        
        roc_plot(clf.best_estimator_,X_eval,y_eval,options)

        plt.savefig("plots/ROC_{0}.pdf".format(type_name))
        plt.gcf().clear()
        
        something = compare_train_test(clf.best_estimator_, X_dev, y_dev, X_eval, y_eval)

        plt.savefig("plots/overtrain_{0}.pdf".format(type_name))
        plt.gcf().clear()
       
        # SHOW ABSOLUTE FEATURE IMPORTANCES
        importances = clf.best_estimator_.feature_importances_
        indices = np.argsort(importances)[::-1]
        branches_sorted = []
        for i in indices:
            branches_sorted.append(branch_names[i])
        

        # Print the feature ranking
        print("Feature ranking:")

        for f in range(X.shape[1]):
            print("%d. feature %s (%f)" % (f + 1, branch_names[indices[f]], importances[indices[f]]))

        # Plot the feature importances of the BDT
        plt.figure()
        plt.title("Feature importances")
        plt.bar(range(X.shape[1]), importances[indices],color="r", align="center")
        plt.xticks(range(X.shape[1]), branches_sorted)
        plt.xlim([-1, X.shape[1]])
        plt.savefig("plots/feature_importances_{0}.pdf".format(type_name))

        # NOW APPLY TO THE DATASET
        df['GBDT'] = clf.predict_proba(X)[:,1]
        df['q2']   = df['Lb_M23']**2

        corr_vars = ['Lb_MM','q2','Lb_DTF_Lambda_PV_M[0]']

        bg = df.y < 0.5
        sig = df.y > 0.5


 
        for corr_var in corr_vars:
            if "[" in corr_var: pass
                #df[corr_var] = pd.to_numeric(df[corr_var].str.replace(']',''))
                #df[corr_var] = pd.to_numeric(df[corr_var].str.replace('[',''))
            else:
                df[corr_var] = pd.to_numeric(df[corr_var])


            print "CORRELATION FOR SIGNAL:"
            x = corr_plot(df[sig],corr_var,'GBDT',[100,20],x_label='$q^{2}$',y_label='GBDT response')
            x.saveAs("plots/sig_corr_{0}_GBDT_{1}.pdf".format(corr_var,type_name))

            print "CORRELATION FOR BACKGROUND:"
            x = corr_plot(df[bg],corr_var,'GBDT',[100,20],x_label='$q^{2}$',y_label='GBDT response')
            x.saveAs("plots/bg_corr_{0}_GBDT_{1}.pdf".format(corr_var,type_name))

            df_leftbg  = df[bg & df.Lb_MM<5500] 
            df_rightbg = df[bg & df.Lb_MM>5500] 

            if not df_leftbg.empty: 
                print "CORRELATION FOR LOW MASS BACKGROUND:"
                x = corr_plot(df_leftbg,corr_var,'GBDT',[100,20],x_label='$q^{2}$',y_label='GBDT response')
                x.saveAs("plots/bg_low_corr_{0}_GBDT_{1}.pdf".format(corr_var,type_name))

            if not df_rightbg.empty: 
                print "CORRELATION FOR HIGH MASS BACKGROUND:"
                x = corr_plot(df_rightbg,corr_var,'GBDT',[100,20],x_label='$q^{2}$',y_label='GBDT response')
                x.saveAs("plots/bg_high_corr_{0}_GBDT_{1}.pdf".format(corr_var,type_name))

        # DUMPING THE CLASSIFIER IN A FILE
        import pickle
        file_name = "classifier/{0}_trained.pickle.dat".format(type_name)
        if os.path.exists(file_name):
            os.remove(file_name)
        pickle.dump(clf, open(file_name, "wb"))

    #########################################
    ### CHECK CORRELATIONS               ####
    #########################################


    if options.MassCorr:
        # CHECK CORRELATIONS
        print "NOTHING IMPLEMENTED YET"


        # OPEN ESTIMATOR


        # PLOT THE CORRELATIONS
        #x = corr_plot()
        
