import os, sys
#sys.path.append( os.environ["LB2LEMUROOT"]+"/Options" )
sys.path.append(os.getcwd())

from DV_Routines import set_branches
from DV_RelatedInfo import getLoKiTool
#from DV_DecayTuple_Reduced import TupTmp, TupTmpMC
from DV_DecayTuple import TupTmp, TupTmpMC
from DV_Config import ConfigDaVinci
from DB import decays_db

from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *
from Configurables import TupleToolDecay
from Configurables import DeterministicPrescaler

#####################################################################
#
# Define DecayTreeTuple tuple
#
######################################################################

branches = ["Lb","JPs","l1","l2","L0","p","pi"]
branches_noL = branches[:-2]
branchesRareMC = ["Lb","l1","l2","L0","p","pi"]
branchesRareMC_noL = branchesRareMC[:-2]

algs = []

def setalgs(isMC=False,decay='LEPTONIC') :

    global TupTmp, TupTmpMC
    if isMC : TupTmp = TupTmpMC
    
    #if isMC: 
    linesprefix = 'Bu2LLKNoPID'
    #else:    linesprefix = 'Bu2LLK'
    line = linesprefix+"_meLine"
    lineSS = linesprefix+"_meSSLine"
    lineEE = linesprefix+"_eeLine2"
    lineMM = linesprefix+"_mmLine"
    lineEECP = linesprefix+"_eeLine"
    lineEEConv = linesprefix+"_eeLine3"

    if decay in ['Lb_Lee','Lb_Lemu','Lb_Lmm','Bd_Ksee','Bd_Ksmm']:
        branches_MC     = branchesRareMC
	branches_MC_noL = branchesRareMC_noL
    else:
        branches_MC     = branches
	branches_MC_noL = branches_noL  

    if isMC: 
        if "Filtered" in decay:  inputname = "Phys/{0}/Particles"#"Event/Bu2LLK_NoPID_LongLived.Strip/Phys/{0}/Particles"
        else:                    inputname = "AllStreams/Phys/{0}/Particles"
    else:    inputname = "Phys/{0}/Particles"

    Lb2LemuTuple = TupTmp.clone("Lb2LemuTuple")
    Lb2LemuTuple.Inputs   = [ inputname.format(line) ]
    Lb2LemuTuple.Decay    = "([Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^mu-) ^(Lambda0 -> ^p+ ^pi-)]CC) || ([Lambda_b0 -> ^(J/psi(1S) -> ^e- ^mu+) ^(Lambda0 -> ^p+ ^pi-)]CC)"
    Lb2LemuTuple.Branches = set_branches(Lb2LemuTuple.Decay,branches)


    LoKi_ToolEM = getLoKiTool("EM",line,isMC)
    Lb2LemuTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolEM"]
    Lb2LemuTuple.Lb.addTool(LoKi_ToolEM)

    Lb2JpsiL_eeTuple = TupTmp.clone("Lb2JpsiL_eeTuple")
    Lb2JpsiL_eeTuple.Inputs   = [ inputname.format(lineEE)] 
    Lb2JpsiL_eeTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_eeTuple.Branches = set_branches(Lb2JpsiL_eeTuple.Decay,branches)


    LoKi_ToolJPsEE = getLoKiTool("JPsEE",lineEE,isMC)
    Lb2JpsiL_eeTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsEE"]
    Lb2JpsiL_eeTuple.Lb.addTool(LoKi_ToolJPsEE)

    Lb2JpsiL_mmTuple = TupTmp.clone("Lb2JpsiL_mmTuple")
    Lb2JpsiL_mmTuple.Inputs   = [ inputname.format(lineMM)] 
    Lb2JpsiL_mmTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_mmTuple.Branches = set_branches(Lb2JpsiL_mmTuple.Decay,branches)

    LoKi_ToolJPsMM = getLoKiTool("JPsMM",lineMM,isMC)
    Lb2JpsiL_mmTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsMM"]
    Lb2JpsiL_mmTuple.Lb.addTool(LoKi_ToolJPsMM)


    Lb2LstMMTuple = TupTmp.clone("Lb2LstMMTuple")
    Lb2LstMMTuple.Inputs   = [ inputname.format(lineMM) ] 
    Lb2LstMMTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(Lambda(1520)0 -> ^p+ ^pi-)]CC"

    Bu2MMKTuple = TupTmp.clone("Bu2MMKTuple")
    Bu2MMKTuple.Inputs   = [ inputname.format(lineMM)]
    Bu2MMKTuple.Decay    = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) K+]CC"

    Bd2MMKstTuple = TupTmp.clone("Bd2MMKstTuple")
    Bd2MMKstTuple.Inputs   = [ inputname.format(lineMM)] 
    Bd2MMKstTuple.Decay    = "[B0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-)]CC"

    Bd2MMKSTuple = TupTmp.clone("Bd2MMKSTuple")
    Bd2MMKSTuple.Inputs   = [ inputname.format(lineMM)] 
    Bd2MMKSTuple.Decay    = "[B0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-)]CC"


    Lb2LstEETuple = TupTmp.clone("Lb2LstEETuple")
    Lb2LstEETuple.Inputs   = [ inputname.format(lineEE) ] 
    Lb2LstEETuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(Lambda(1520)0 -> ^p+ ^pi-)]CC"

    Bu2EEKTuple = TupTmp.clone("Bu2EEKTuple")
    Bu2EEKTuple.Inputs   = [ inputname.format(lineEE)]
    Bu2EEKTuple.Decay    = "[B+ -> ^(J/psi(1S) -> ^e+ ^e-) K+]CC"

    Bd2EEKstTuple = TupTmp.clone("Bd2EEKstTuple")
    Bd2EEKstTuple.Inputs   = [ inputname.format(lineEE)] 
    Bd2EEKstTuple.Decay    = "[B0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(K*(892)0 -> ^K+ ^pi-)]CC"

    Bd2EEKSTuple = TupTmp.clone("Bd2EEKSTuple")
    Bd2EEKSTuple.Inputs   = [ inputname.format(lineEE)] 
    Bd2EEKSTuple.Decay    = "[B0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(KS0 -> ^pi+ ^pi-)]CC"


    Lb2LstemuTuple = TupTmp.clone("Lb2LstemuTuple")
    Lb2LstemuTuple.Inputs   = [ inputname.format(line) ] 
    Lb2LstemuTuple.Decay    = "([Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^mu-) ^(Lambda(1520)0 -> ^p+ ^pi-)]CC) || [Lambda_b0 -> ^(J/psi(1S) -> ^e- ^mu+) ^(Lambda(1520)0 -> ^p+ ^pi-)]CC"

    Bu2emuKTuple = TupTmp.clone("Bu2emuKTuple")
    Bu2emuKTuple.Inputs   = [ inputname.format(line)]
    Bu2emuKTuple.Decay    = "([B+ -> ^(J/psi(1S) -> ^e+ ^mu-) ^K+]CC) || ([B+ -> ^(J/psi(1S) -> ^e- ^mu+) ^K+]CC)"

    Bd2emuKstTuple = TupTmp.clone("Bd2emuKstTuple")
    Bd2emuKstTuple.Inputs   = [ inputname.format(line)] 
    Bd2emuKstTuple.Decay    = "([B0 -> ^(J/psi(1S) -> ^e+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-)]CC) || ([B0 -> ^(J/psi(1S) -> ^e- ^mu+) ^(K*(892)0 -> ^K+ ^pi-)]CC)"

    Bd2emuKSTuple = TupTmp.clone("Bd2emuKSTuple")
    Bd2emuKSTuple.Inputs   = [ inputname.format(line)] 
    Bd2emuKSTuple.Decay    = "([B0 -> ^(J/psi(1S) -> ^e+ ^mu-) ^(KS0 -> ^pi+ ^pi-)]CC) || ([B0 -> ^(J/psi(1S) -> ^e- ^mu+) ^(KS0 -> ^pi+ ^pi-)]CC)"

    global algs
    algs = [ Lb2LemuTuple, Lb2JpsiL_eeTuple, Lb2JpsiL_mmTuple, 
        Lb2LstMMTuple, Bu2MMKTuple, Bd2MMKstTuple, Bd2MMKSTuple,
        Lb2LstEETuple, Bu2EEKTuple, Bd2EEKSTuple, Bd2EEKstTuple,
        Lb2LstemuTuple, Bu2emuKTuple, Bd2emuKSTuple, Bd2emuKstTuple
         ]

    if not isMC : return
    
    #print "Adding MCDecayTreeTuple"
    #from DV_MCDecayTuple import MCTupTmp

    #MCTuple          = MCTupTmp.clone("MCTuple")
    #MCTuple.Decay    = '({0})'.format(decays_db[decay.replace('Filtered_',"")]['descriptor'])
    #print MCTuple.Decay
    #MCTuple.Branches = set_branches(MCTuple.Decay,branches_MC)
    #algs += [ MCTuple ]

    #print algs

