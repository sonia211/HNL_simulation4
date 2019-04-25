import easyanalysis as ea
import ROOT as r
from Lb2LemuEnv import cuts, loc
from Lb2LemuEnv import db, dumpDB
#print db
import utils
#print utils
from utils.getreader import getreader
import sys, os, argparse
from glob import glob
import datetime
import pickle
import yaml
from math import *
r.RooDataSet.setDefaultStorageType(r.RooAbsData.Tree) # Needed for saving the tree in the end
r.gROOT.SetBatch(r.kTRUE)


### PARSE FILENAME, TREE AND VARNAME ###
filename = "pytree_m2p0_w0_t3e1.root"
bool m_or_d = true # mother=1, daughter=0
varname = "N_tau"

### LOAD CFG FILE ###
with open("fit_cfg.yml", 'r') as stream:
    try:
        cfg_file = yaml.load(stream)
    except yaml.YAMLError as exc:
        print(exc)

datapath = cfg_file['datapath']
#filename = cfg_file['filename']
TM = cfg_file['TM']
TD = cfg_file['TD']
odir = cfg_file['odir']

outfile = odir+"D02mumu_sw.root"
f = r.TFile(outfile,"RECREATE")


finput = datapath+filename

fitopt = "-ncpu8-nochi2-nocost-quiet-andpulls-linlog-leg[0.25,0.75,0.50,0.9]-layout[0.6,0.5,0.92,0.9]-xm(D_0 #pi#pi )-allformats"
vM 		= r.RooRealVar(varname,varname,1797,1920)
reader  = getreader(tree,datapath,("(%s)" % f_data),"local")
ana = ea.Analysis("N2pimu","N#rightarrow #mu^+#pi^-", reader,r.TCut(""),vM)

f.cd()
ana.SetSignal("Exp-b[0,1e-1,3e-1]")
ana.Initialize("", -1)

### FIT

ana.Fit(100,False,fitopt)


'''
print "HEREEEE"
print "sigma_0g_MC = ", s0gMC, " +/- ", serr0gMC

fitEE_file=open("/home/bouchiba/TP4b/Lb2Lemu_test/python/Mass_Selection/ofitEE.dat","a+")
fitEE_file.write("\n \nTrack Type : %s \nDate : %s \n### MC ###\nm0g=%f s0g=%f N0g=%f \n m1g=%f s1g=%f N1g=%f\n### DATA ###\nm0g=%f s0g=%f \nm1g=%f s1g=%f \n frac=%f  k = %f" % (str(cutTT),datetime.datetime.now(), m0gMC, s0gMC, N0g, m1gMC, s1gMC, N1g, m0gDA, s0gDA, m1gDA, s1gDA, frac, k))


dataEE={"m0gEE_MC":m0gMC, "s0gEE_MC":s0gMC, "m1gEE_MC":m1gMC, "s1gEE_MC":s1gMC, "m0gEE_DA":m0gDA, "s0gEE_DA":s0gDA, "m1gEE_DA":m1gDA, "s1gEE_DA":s1gDA, "merr0gEE_MC":merr0gMC, "serr0gEE_MC":serr0gMC, "merr1gEE_MC":merr1gMC, "serr1gEE_MC":serr1gMC, "merr0gEE_DA":merr0gDA, "serr0gEE_DA":serr0gDA, "merr1gEE_DA":merr1gDA, "serr1gEE_DA":serr1gDA }
pickle_out=open("/home/bouchiba/TP4b/Lb2Lemu_test/python/Mass_Selection/fitDB_TT%s_EE.pickle" % str(cutTT),"wb+")
pickle.dump(dataEE,pickle_out); 
#pickle_out.close()

#fitEE_file=open("./results_C.dat",'a+')
#fitEE_file.write("%f %f %f %f %f %f %f %f" % (m0gMC, s0gMC, m0gDA, s0gDA))
'''
raw_input("..")
f.Close()



