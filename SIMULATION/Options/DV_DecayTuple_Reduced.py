from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *

#####################################################################
#
# Define template tuple
#
######################################################################

from Configurables import DecayTreeTuple
TupTmp          = DecayTreeTuple()

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

TupTmpMC = TupTmp.clone("DecayTreeTupleForMC") 
 
from Configurables import TupleToolMCTruth 

TupTmpMC.addTool( TupleToolMCTruth ) 
TupTmpMC.ToolList += [ "TupleToolMCTruth" ] 
TupTmpMC.TupleToolMCTruth.ToolList += [ "MCTupleToolHierarchy" ] 
TupTmpMC.TupleToolMCTruth.ToolList += [ "MCTupleToolKinematic" ] 
  
#TupTmpMC.Lb.addTool( TupleToolMCTruth ) 
#TupTmpMC.Lb.ToolList += [ "TupleToolMCTruth" ] 

#from Configurables import TupleToolMCBackgroundInfo
#TupTmpMC.Lb.ToolList += [ "TupleToolMCBackgroundInfo" ]


