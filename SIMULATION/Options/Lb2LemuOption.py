import os, sys
#sys.path.append( os.environ["LB2LEMUROOT"]+"/Options" )
sys.path.append(os.getcwd())

from DV_Routines import set_branches
from DV_RelatedInfo import getLoKiTool
from DV_DecayTuple import TupTmp, TupTmpMC
from DV_Config import ConfigDaVinci
from DB import decays_db

from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *
from Configurables import TupleToolDecay
from Configurables import DeterministicPrescaler

######################################################################



#####################################################################
#
# Define DecayTreeTuple tuple
#
######################################################################

branches = ["Lb","JPs","l1","l2","L0","p","pi"]
branches_noL = branches[:-2]
branchesRareMC = ["Lb","l1","l2","L0","p","pi"]
branchesRareMC_noL = branchesRareMC[:-2]
branchesBu = ['Lb','JPs','l1','l2','p']

algs = []

def setalgs(isMC=False,stripversion="21",decay='LEPTONIC',Restrip=False,MDST=False,Filtered=False) :

    global TupTmp, TupTmpMC, algs
    if isMC : TupTmp = TupTmpMC
    if isMC and Filtered: linesprefix = 'Bu2LLKNoPID'
    else:    linesprefix = 'Bu2LLK'
    line = linesprefix+"_meLine"
    lineSS = linesprefix+"_meSSLine"
    if not Filtered:
        lineEE = linesprefix+"_eeLine2"
    else:
        lineEE = linesprefix+"_eeLine_dem"
    lineMM = linesprefix+"_mmLine"
    lineEECP = linesprefix+"_eeLine"
    lineEEConv = linesprefix+"_eeLine3"
  
    algs = [] # TO ALLOW TO ADD RESTRIPPING OR NOT

    relinfo_phys = Restrip or MDST 

    if Restrip:
        from DV_Routines import ReStrip_old
        lines_to_restrip = [ 
                'StrippingBu2LLK_meLine',
                'StrippingBu2LLK_meSSLine',
                'StrippingBu2LLK_eeLine',
                'StrippingBu2LLK_eeLine2',
                'StrippingBu2LLK_eeLine3',
                'StrippingBu2LLK_mmLine'
                ]

        restrip, restripSq = ReStrip_old(lines_to_restrip,stripversion,['Leptonic'])
        
        algs = restripSq
        
    if decay.replace('Filtered_','') in ['Lb_Lee','Lb_Lemu','Lb_Lmm','Bd_Ksee','Bd_Ksmm']:
        branches_MC     = branchesRareMC
        branches_MC_noL = branchesRareMC_noL
    else:
        branches_MC     = branches
        branches_MC_noL = branches_noL  

    if isMC: 
        if Filtered:             inputname = "/Event/Bu2KLL_NoPID_LongLived.Strip/Phys/{0}/Particles"
        elif Restrip or MDST:    inputname = "Phys/{0}/Particles" # IF RESTRIPPING
        else:                    inputname = "AllStreams/Phys/{0}/Particles" # IF NOT RESTRIPPING

    else:    inputname = "Phys/{0}/Particles"

    Lb2LemuTuple = TupTmp.clone("Lb2LemuTuple")
    Lb2LemuTuple.Inputs   = [ inputname.format(line) ]
    Lb2LemuTuple.Decay    = "([Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^mu-) ^(Lambda0 -> ^p+ ^pi-)]CC) || ([Lambda_b0 -> ^(J/psi(1S) -> ^e- ^mu+) ^(Lambda0 -> ^p+ ^pi-)]CC)"
    Lb2LemuTuple.Branches = set_branches(Lb2LemuTuple.Decay,branches)
    
    LoKi_ToolEM = getLoKiTool("EM",line,isMC,relinfo_phys)
    Lb2LemuTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolEM"]
    Lb2LemuTuple.Lb.addTool(LoKi_ToolEM)

    Lb2LemuSSTuple = TupTmp.clone("Lb2LemuSSTuple")
    Lb2LemuSSTuple.Inputs   = [ inputname.format(lineSS) ]
    Lb2LemuSSTuple.Decay    = "([Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^mu+) ^(Lambda0 -> ^p+ ^pi-)]CC) || ([Lambda_b0 -> ^(J/psi(1S) -> ^e- ^mu-) ^(Lambda0 -> ^p+ ^pi-)]CC)"
    Lb2LemuSSTuple.Branches = set_branches(Lb2LemuSSTuple.Decay,branches)

    LoKi_ToolEMSS = getLoKiTool("EMSS",lineSS,isMC,relinfo_phys)
    Lb2LemuSSTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolEMSS"]
    Lb2LemuSSTuple.Lb.addTool(LoKi_ToolEMSS)
   
    Lb2JpsiL_eeTuple = TupTmp.clone("Lb2JpsiL_eeTuple")
    Lb2JpsiL_eeTuple.Inputs   = [ inputname.format(lineEE)] 
    Lb2JpsiL_eeTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_eeTuple.Branches = set_branches(Lb2JpsiL_eeTuple.Decay,branches)

    LoKi_ToolJPsEE = getLoKiTool("JPsEE",lineEE,isMC,relinfo_phys)
    Lb2JpsiL_eeTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsEE"]
    Lb2JpsiL_eeTuple.Lb.addTool(LoKi_ToolJPsEE)

    Lb2JpsiL_eeCPTuple = TupTmp.clone("Lb2JpsiL_eeCPTuple")
    Lb2JpsiL_eeCPTuple.Inputs   = [ inputname.format(lineEECP) ] 
    Lb2JpsiL_eeCPTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_eeCPTuple.Branches = set_branches(Lb2JpsiL_eeCPTuple.Decay,branches)

    LoKi_ToolJPsEECP = getLoKiTool("JPsEECP",lineEECP,isMC,relinfo_phys)
    Lb2JpsiL_eeCPTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsEECP"]
    Lb2JpsiL_eeCPTuple.Lb.addTool(LoKi_ToolJPsEECP)

    Lb2JpsiL_eeConvTuple = TupTmp.clone("Lb2JpsiL_eeConvTuple")
    Lb2JpsiL_eeConvTuple.Inputs   = [ inputname.format(lineEEConv)]
    Lb2JpsiL_eeConvTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^e+ ^e-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_eeConvTuple.Branches = set_branches(Lb2JpsiL_eeConvTuple.Decay,branches)

    LoKi_ToolJPsEEConv = getLoKiTool("JPsEEConv",lineEEConv,isMC,relinfo_phys)
    Lb2JpsiL_eeConvTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsEEConv"]
    Lb2JpsiL_eeConvTuple.Lb.addTool(LoKi_ToolJPsEEConv)

    Lb2JpsiL_mmTuple = TupTmp.clone("Lb2JpsiL_mmTuple")
    Lb2JpsiL_mmTuple.Inputs   = [ inputname.format(lineMM)] 
    Lb2JpsiL_mmTuple.Decay    = "[Lambda_b0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(Lambda0 -> ^p+ ^pi-)]CC"
    Lb2JpsiL_mmTuple.Branches = set_branches(Lb2JpsiL_mmTuple.Decay,branches)
    
    LoKi_ToolJPsMM = getLoKiTool("JPsMM",lineMM,isMC,relinfo_phys)
    Lb2JpsiL_mmTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolJPsMM"]
    Lb2JpsiL_mmTuple.Lb.addTool(LoKi_ToolJPsMM)

    Bu2JpsiK_eeTuple = TupTmp.clone("Bu2JpsiK_eeTuple")
    Bu2JpsiK_eeTuple.Inputs   = [ inputname.format(lineEE)] 
    Bu2JpsiK_eeTuple.Decay    = "[B+ -> ^(J/psi(1S) -> ^e+ ^e-) ^K+]CC"
    Bu2JpsiK_eeTuple.Branches = set_branches(Bu2JpsiK_eeTuple.Decay,branchesBu)
    Bu2JpsiK_eeTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambda_PV")
    Bu2JpsiK_eeTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambda_JPs_PV")
    Bu2JpsiK_eeTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambdab_PV")

    LoKi_ToolBuJPsEE = getLoKiTool("BuJPsEE",lineEE,isMC,relinfo_phys)
    Bu2JpsiK_eeTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolBuJPsEE"]
    Bu2JpsiK_eeTuple.Lb.addTool(LoKi_ToolBuJPsEE)

    Bu2JpsiK_mmTuple = TupTmp.clone("Bu2JpsiK_mmTuple")
    Bu2JpsiK_mmTuple.Inputs   = [ inputname.format(lineMM)] 
    Bu2JpsiK_mmTuple.Decay    = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+]CC"
    Bu2JpsiK_mmTuple.Branches = set_branches(Bu2JpsiK_mmTuple.Decay,branchesBu)
    Bu2JpsiK_mmTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambda_PV")
    Bu2JpsiK_mmTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambda_JPs_PV")
    Bu2JpsiK_mmTuple.Lb.ToolList.remove("TupleToolDecayTreeFitter/DTF_Lambdab_PV")

    LoKi_ToolBuJPsMM = getLoKiTool("BuJPsMM",lineMM,isMC,relinfo_phys)
    Bu2JpsiK_mmTuple.Lb.ToolList += ["LoKi::Hybrid::TupleTool/LoKi_ToolBuJPsMM"]
    Bu2JpsiK_mmTuple.Lb.addTool(LoKi_ToolBuJPsMM)


    algs += [ Lb2LemuTuple, Lb2LemuSSTuple, Lb2JpsiL_eeTuple, Lb2JpsiL_eeCPTuple, Lb2JpsiL_mmTuple, Lb2JpsiL_eeConvTuple , Bu2JpsiK_eeTuple, Bu2JpsiK_mmTuple]

    if not isMC : return
    
    print "Adding MCDecayTreeTuple"

    from DV_MCDecayTuple import MCTupTmp

    MCTuple          = MCTupTmp.clone("MCTuple")
    MCTuple.Decay    = '({0})'.format(decays_db[decay.replace('Filtered_', '')]['descriptor'])
    MCTuple.Branches = set_branches(MCTuple.Decay,branches_MC)
    algs += [ MCTuple ]
	  
    MCTuple_noLdec          = MCTupTmp.clone("MCTuple_noLdec")
    MCTuple_noLdec.Decay    = '({0})'.format(decays_db[decay.replace('Filtered_', '')]['descriptor_noLdec'])
    MCTuple_noLdec.Branches = set_branches(MCTuple_noLdec.Decay,branches_MC_noL)
    algs += [ MCTuple_noLdec ] 

    print algs
