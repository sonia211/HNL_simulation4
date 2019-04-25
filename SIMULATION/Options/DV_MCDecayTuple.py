from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *

#####################################################################
#
# Define template MCtuple
#
######################################################################

from Configurables import MCDecayTreeTuple
MCTupTmp          = MCDecayTreeTuple()

MCTupTmp.ToolList += [ "MCTupleToolHierarchy" ]
MCTupTmp.ToolList += [ "MCTupleToolKinematic" ]
MCTupTmp.ToolList += [ "MCTupleToolPID" ]
#from Configurables import MCTupleToolReconstructed
#TupTmpMC.addTool( MCTupleToolReconstructed)
#MCTupTmp.ToolList += ["MCTupleToolReconstructed"]

#from Configurables import TupleToolDecay
#MCTupTmp.addTool( TupleToolDecay, name = "B0" )


######################################################################

from Configurables import LoKi__Hybrid__EvtTupleTool
MCTupTmp.addTool( LoKi__Hybrid__EvtTupleTool, name = "LoKiHybrid" )
MCTupTmp.ToolList += [ "LoKi::Hybrid::EvtTupleTool/LoKiHybrid" ]
MCTupTmp.LoKiHybrid.Preambulo = [
    "from LoKiCore.basic import LHCb"
    ]
MCTupTmp.LoKiHybrid.VOID_Variables = {
    "nSPDHits" : "RECSUMMARY( LHCb.RecSummary.nSPDhits, -1, '/Event/Rec/Summary', False )"
    }
