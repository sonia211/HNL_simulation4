isTest = True 

import os, sys
lbroot = os.getenv("LB2LEMUROOT")
if lbroot is not None : sys.path.append(lbroot+"/Options" )
sys.path.append(os.getcwd())

import Lb2LemuOption as opt
from DV_Config import ConfigDaVinci

opt.setalgs(True,'Lb_Lee')
ConfigDaVinci("MC",12,opt.algs,Mag='MD',restrip=[],isTest=isTest)


