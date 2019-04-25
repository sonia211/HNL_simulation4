isTest = True

import os, sys
lbroot = os.getenv("LB2LEMUROOT")
if lbroot is not None : sys.path.append(lbroot+"/Options" )

import Lb2LemuOption as opt
from DV_Config import ConfigDaVinci

opt.setalgs()
ConfigDaVinci("CL",16,opt.algs,RootInTES="Leptonic",isTest=isTest)


