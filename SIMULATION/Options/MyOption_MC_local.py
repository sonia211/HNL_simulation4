isTest = False

import os, sys
lbroot = os.getenv("LB2LEMUROOT")
if lbroot is not None : sys.path.append(lbroot+"/Options" )
sys.path.append(os.getcwd())

import Lb2LemuOption as opt
from DV_Config import ConfigDaVinci

decay = "Lb_Lee"
#opt.setalgs(True,decay=decay)
opt.setalgs(True,decay=decay,Filtered=True)
ConfigDaVinci("MC","16_Filtered",opt.algs,Mag='MD',restrip=[],isTest=isTest,decay=decay)


