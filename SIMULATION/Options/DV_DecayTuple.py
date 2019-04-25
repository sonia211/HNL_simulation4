from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *

#####################################################################
#
# Define template tuple
#
######################################################################

from Configurables import DecayTreeTuple
TupTmp          = DecayTreeTuple()
######################################################################
from Configurables import TupleToolDecay
TupTmp.addTool( TupleToolDecay, name = "Lb" )
TupTmp.addTool( TupleToolDecay, name = "L0" )
TupTmp.addTool( TupleToolDecay, name = "JPs" )
TupTmp.addTool( TupleToolDecay, name = "l1" )
TupTmp.addTool( TupleToolDecay, name = "l2" )
TupTmp.addTool( TupleToolDecay, name = "p" )
TupTmp.addTool( TupleToolDecay, name = "pi" )

######################################################################
TupTmp.ToolList += [
    "TupleToolANNPID",
    "TupleToolBremInfo",
    "TupleToolEventInfo",
    "TupleToolGeometry",
    "TupleToolKinematic",
    "TupleToolPid",
    "TupleToolPrimaries",
    "TupleToolPropertime",
    "TupleToolRecoStats",
    "TupleToolTrackInfo"
    ]
######################################################################
# Include TupleToolL0Calo for correction of ET cut in 2016 samples + possibility to bin in CaloRegions
#from Configurables import TupleToolL0Calo 
#for particle in [TupTmp.l1,TupTmp.l2,TupTmp.p,TupTmp.pi]:
#    particle.addTool(TupleToolL0Calo,name='L0Calo')
#    particle.ToolList += [ "TupleToolL0Calo/L0Calo"]
    #particle.WhichCalo = "ECAL"

#from Configurables import TupleToolMaterialVeto 
#for particle in [TupTmp.l1,TupTmp.l2]:
#    particle.addTool(TupleToolL0Calo,name='L0Calo')
#    particle.ToolList += [ "TupleToolL0Calo/L0Calo"]
    #particle.WhichCalo = "ECAL"


from Configurables import TupleToolTISTOS
for particle in [TupTmp.Lb,TupTmp.JPs,TupTmp.L0,TupTmp.l1,TupTmp.l2,TupTmp.p,TupTmp.pi]:
    particle.addTool( TupleToolTISTOS, name = "L0TISTOS" )
    particle.ToolList += [ "TupleToolTISTOS/L0TISTOS" ]

    particle.L0TISTOS.TriggerList = [
	"L0ElectronDecision",
	"L0HadronDecision",
	"L0MuonDecision",
	"L0DiMuonDecision",
	"L0PhotonDecision",
    ]
    particle.L0TISTOS.Verbose = True

TupTmp.Lb.addTool( TupleToolTISTOS, name = "HltTISTOS" )
TupTmp.Lb.ToolList += [ "TupleToolTISTOS/HltTISTOS" ]

TupTmp.Lb.HltTISTOS.TriggerList = [
	"Hlt1TrackAllL0Decision",
	"Hlt1TrackAllL0TightDecision",
	"Hlt1TrackMuonDecision",
	"Hlt1TrackPhotonDecision",
	"Hlt1TrackMVADecision",
	"Hlt1TrackMVALooseDecision",
	"Hlt1TrackMuonMVADecision",
	"Hlt1TwoTrackMVALooseDecision",
	"Hlt1TwoTrackMVADecision",
	"Hlt1SingleMuonHighPTDecision",
	"Hlt1SingleMuonDecision",
	"Hlt1DiMuonHighMassDecision",

        "Hlt2SingleMuonDecision",
	"Hlt2DiMuonDetachedDecision",
        "Hlt2SingleElectronTFHighPtDecision",
	"Hlt2SingleElectronTFLowPtDecision",

	"Hlt2Topo2BodyDecision",
	"Hlt2Topo3BodyDecision",
	"Hlt2Topo4BodyDecision",
	"Hlt2TopoE2BodyDecision",
	"Hlt2TopoE3BodyDecision",
	"Hlt2TopoE4BodyDecision",
	"Hlt2TopoEE2BodyDecision",
	"Hlt2TopoEE3BodyDecision",
	"Hlt2TopoEE4BodyDecision",
	"Hlt2TopoMu2BodyDecision",
	"Hlt2TopoMu3BodyDecision",
	"Hlt2TopoMu4BodyDecision",
	"Hlt2TopoMuE2BodyDecision",
	"Hlt2TopoMuE3BodyDecision",
	"Hlt2TopoMuE4BodyDecision",

	"Hlt2Topo2BodyBBDTDecision",
	"Hlt2Topo3BodyBBDTDecision",
	"Hlt2Topo4BodyBBDTDecision",
	"Hlt2TopoE2BodyBBDTDecision",
	"Hlt2TopoE3BodyBBDTDecision",
	"Hlt2TopoE4BodyBBDTDecision",
	"Hlt2TopoMu2BodyBBDTDecision",
	"Hlt2TopoMu3BodyBBDTDecision",
	"Hlt2TopoMu4BodyBBDTDecision",
	]
TupTmp.Lb.HltTISTOS.Verbose = True

# Hlt1 info for each particle to calibrate TrackMVA
for particle in [TupTmp.JPs,TupTmp.L0,TupTmp.l1,TupTmp.l2,TupTmp.p,TupTmp.pi]:
    particle.addTool( TupleToolTISTOS, name = "HltTISTOS" )
    particle.ToolList += [ "TupleToolTISTOS/HltTISTOS" ]
    particle.HltTISTOS.TriggerList = [
            "Hlt1TrackAllL0Decision",
            "Hlt1TrackAllL0TightDecision",
            "Hlt1TrackMuonDecision",
            "Hlt1TrackPhotonDecision",
            "Hlt1TrackMVADecision",
            "Hlt1TrackMVALooseDecision",
            "Hlt1TrackMuonMVADecision",
            "Hlt1TwoTrackMVALooseDecision",
            "Hlt1TwoTrackMVADecision",
            "Hlt1SingleMuonDecision",
    ]
    particle.HltTISTOS.Verbose = True

# Hlt2 info for JPsi
TupTmp.JPs.addTool( TupleToolTISTOS, name = "HltTISTOS" )
TupTmp.JPs.ToolList += [ "TupleToolTISTOS/HltTISTOS" ]

TupTmp.JPs.HltTISTOS.TriggerList = [
 	"Hlt2Topo2BodyDecision",
	"Hlt2TopoE2BodyDecision",
	"Hlt2TopoEE2BodyDecision",
	"Hlt2TopoMu2BodyDecision",
	"Hlt2TopoMuE2BodyDecision",

	"Hlt2Topo2BodyBBDTDecision",
	"Hlt2TopoE2BodyBBDTDecision",
	"Hlt2TopoMu2BodyBBDTDecision",
	]
TupTmp.JPs.HltTISTOS.Verbose = True


from Configurables import TupleToolDecayTreeFitter
TupTmp.Lb.addTool( TupleToolDecayTreeFitter, name = "DTF" )
TupTmp.Lb.ToolList += [ "TupleToolDecayTreeFitter/DTF" ]
TupTmp.Lb.addTool( TupTmp.Lb.DTF.clone( "DTF_PV",
                                      Verbose = True,
                                      constrainToOriginVertex = True ) )
TupTmp.Lb.ToolList += [ "TupleToolDecayTreeFitter/DTF_PV" ]
TupTmp.Lb.addTool( TupTmp.Lb.DTF.clone( "DTF_Lambda_PV",
                                      Verbose = True,
                                      constrainToOriginVertex = True,
                                      daughtersToConstrain = [ "Lambda0" ] ) )
TupTmp.Lb.ToolList += [ "TupleToolDecayTreeFitter/DTF_Lambda_PV" ]
TupTmp.Lb.addTool( TupTmp.Lb.DTF.clone( "DTF_Lambdab_PV",
                                      Verbose = True,
                                      constrainToOriginVertex = True,
                                      daughtersToConstrain = [ "Lambda_b0" ] ) )
TupTmp.Lb.ToolList += [ "TupleToolDecayTreeFitter/DTF_Lambdab_PV" ]

TupTmp.Lb.addTool( TupTmp.Lb.DTF.clone( "DTF_Lambda_JPs_PV",
                                      Verbose = True,
                                      constrainToOriginVertex = True,
                                      daughtersToConstrain = [ "Lambda0","J/psi(1S)" ] ) )
TupTmp.Lb.ToolList += [ "TupleToolDecayTreeFitter/DTF_Lambda_JPs_PV" ]


#adding hop from loki functor
from Configurables import  LoKi__Hybrid__TupleTool    
LoKi_HOP = LoKi__Hybrid__TupleTool("LoKi_HOP")
LoKi_HOP.Variables ={
    'hop_LoKi_mass_bv': 'BPVHOPM()',
    'hop_LoKi_mass': 'HOPM(0,0,0)',
            }

TupTmp.Lb.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_HOP" ]
TupTmp.Lb.addTool(LoKi_HOP)

# adding MIPCHI2 variable to p and pi
LoKi_MIPCHI2 = LoKi__Hybrid__TupleTool("LoKi_MIPCHI2DV")
LoKi_MIPCHI2.Variables ={
    "MIPCHI2" : "MIPCHI2DV(PRIMARY)",
            }

# adding Track momenta to l1 and l2
LoKi_Track_mom = LoKi__Hybrid__TupleTool("LoKi_Track_mom")
LoKi_Track_mom.Variables ={
    "TRACK_P"  : "PPINFO(504,-100,-200)",
    "TRACK_PT" : "PPINFO(505,-100,-200)",
    "TRACK_PX" : "PPINFO(505,-1e7,-1e7) * cos( PHI )",
    "TRACK_PY" : "PPINFO(505,-1e7,-1e7) * sin( PHI )",
    "TRACK_PZ" : "PPINFO(505,-1e7,-1e7) * sinh(ETA )",
            }

TupTmp.l1.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_Track_mom" ]
TupTmp.l1.addTool(LoKi_Track_mom)
TupTmp.l2.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_Track_mom" ]
TupTmp.l2.addTool(LoKi_Track_mom)


TupTmp.p.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_MIPCHI2DV" ]
TupTmp.p.addTool(LoKi_MIPCHI2)
TupTmp.pi.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_MIPCHI2DV" ]
TupTmp.pi.addTool(LoKi_MIPCHI2)

#adding DOCA variables
LoKi_DOCA = LoKi__Hybrid__TupleTool("LoKi_DOCA")
LoKi_DOCA.Variables = {
    "DOCA01"  :  "DOCA(0,1)",
    "DOCA02"  :  "DOCA(0,2)",
    "DOCA12"  :  "DOCA(1,2)",
    "DOCA_MAX":  "DOCAMAX",
    }

TupTmp.Lb.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_DOCA"]
TupTmp.Lb.addTool(LoKi_DOCA)
TupTmp.JPs.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_DOCA"]
TupTmp.JPs.addTool(LoKi_DOCA)
TupTmp.L0.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_DOCA"]
TupTmp.L0.addTool(LoKi_DOCA)
#######################################################################

from Configurables import TupleToolSubMass
TupTmp.Lb.addTool( TupleToolSubMass )
TupTmp.Lb.ToolList += [ "TupleToolSubMass" ]
TupTmp.Lb.TupleToolSubMass.EndTreePIDs = [22]

#for particle in ["p",'pi','e','mu']: 
#    for particle2 in set(["p",'pi','K','e','mu']) - {particle}: # LOOP OVER ALL BUT PARTICLE
#        TupTmp.Lb.TupleToolSubMass.Substitution       += [ "{0}+ => {1}+".format(particle,particle2) ]

TupTmp.Lb.TupleToolSubMass.Substitution       += [ "p+ => pi+" ]
TupTmp.Lb.TupleToolSubMass.Substitution       += [ "p+ => K+" ]
TupTmp.Lb.TupleToolSubMass.Substitution       += [ "pi- => p~-" ]
TupTmp.Lb.TupleToolSubMass.Substitution       += [ "pi- => K-" ]

#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "mu- => e-" ]
#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "e- => mu-" ]
#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "e- => pi-" ]
#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "e- => K-" ]
#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "e- => p+" ]
#TupTmp.Lb.TupleToolSubMass.Substitution       += [ "mu+ => e+" ]

TupTmp.Lb.TupleToolSubMass.DoubleSubstitution += [ "mu+/e- => e+/mu-" ]
TupTmp.Lb.TupleToolSubMass.DoubleSubstitution += [ "e+/e- => mu+/mu-" ]
TupTmp.Lb.TupleToolSubMass.DoubleSubstitution += [ "mu+/mu- => e+/e-" ]
TupTmp.Lb.TupleToolSubMass.DoubleSubstitution += [ "p+/pi- => pi+/p~-" ]

#########################################################################
## Adding hop from tuple tool
from Configurables import TupleToolHOP
TupTmp.Lb.addTool(TupleToolHOP, name = "LbHOP")
TupTmp.Lb.ToolList += [ "TupleToolHOP/LbHOP"]

########################################### MC truth info for simulated samples

TupTmpMC = TupTmp.clone("DecayTreeTupleForMC") 
 
from Configurables import TupleToolMCTruth,MCMatchObjP2MCRelator

# Work around for Turbo locations being included in the default list    # of relations table locations, which triggers Turbo unpacking and    # seg. faults
default_rel_locs = MCMatchObjP2MCRelator().getDefaultProperty('RelTableLocations')
rel_locs = [loc for loc in default_rel_locs if 'Turbo' not in loc] 

TupTmpMC.addTool( TupleToolMCTruth ) 
TupTmpMC.ToolList += [ "TupleToolMCTruth" ] 
TupTmpMC.TupleToolMCTruth.ToolList += [ "MCTupleToolHierarchy" ] 
TupTmpMC.TupleToolMCTruth.ToolList += [ "MCTupleToolKinematic" ] 
TupTmpMC.TupleToolMCTruth.addTool(MCMatchObjP2MCRelator)
TupTmpMC.TupleToolMCTruth.MCMatchObjP2MCRelator.RelTableLocations = rel_locs  

TupTmpMC.Lb.addTool( TupleToolMCTruth ) 
TupTmpMC.Lb.ToolList += [ "TupleToolMCTruth" ] 
TupTmpMC.Lb.TupleToolMCTruth.addTool(MCMatchObjP2MCRelator)
TupTmpMC.Lb.TupleToolMCTruth.MCMatchObjP2MCRelator.RelTableLocations = rel_locs  

from Configurables import TupleToolMCBackgroundInfo
TupTmpMC.Lb.ToolList += [ "TupleToolMCBackgroundInfo" ]



#LoKi_RecType = LoKi__Hybrid__TupleTool("LoKi_RecType")
#LoKi_RecType.Variables ={
#    "UpstreamCharged" : "MCREC()",
#            }

#TupTmpMC.p.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_" ]
#TupTmpMC.p.addTool(LoKi_RecType)
#TupTmpMC.pi.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_RecType" ]
#TupTmpMC.pi.addTool(LoKi_RecType)

