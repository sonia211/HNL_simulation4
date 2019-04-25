isTest = False #### CHANGE HERE

rerunCalo = False
dtype = 'CL'
if True : dtype = 'MC'

import os, sys
lbroot = os.getenv("LB2LEMUROOT")
if lbroot is not None : sys.path.append( lbroot+"/Options" )
sys.path.append(os.getcwd())

import Lb2LemuOption as opt
from DV_Config import ConfigDaVinci


opt.setalgs(True,'28','Lb_JpsiL_mm',Restrip = rerunCalo, MDST=False, Filtered = False)
ConfigDaVinci(dtype,'16_S28',opt.algs,Mag='MD',RootInTES='',decay='Lb_JpsiL_mm',restrip=[],isTest=isTest, rerunCalo = rerunCalo)

