isTest = False #### CHANGE HERE

#dtype = 'CL'
#if True : 
dtype = 'MC'

import os, sys
lbroot = os.getenv("LB2LEMUROOT")
if lbroot is not None : sys.path.append( lbroot+"/Options" )
sys.path.append(os.getcwd())

import TestFilteringOption as opt
from DV_Config import ConfigDaVinci

opt.setalgs(True,'Filtered_Lb_Lemu')

MDST = False
if MDST:
    ConfigDaVinci(dtype,"11_Filtered",opt.algs,Mag='MD',RootInTES="Bu2KLL_NoPID_LongLived.Strip",restrip=[],isTest=isTest)
else: 
    ConfigDaVinci(dtype,"11_Filtered",opt.algs,Mag='MD',RootInTES="",restrip=[],isTest=isTest)

