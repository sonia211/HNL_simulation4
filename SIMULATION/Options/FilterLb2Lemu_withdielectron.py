"""
Stripping Filtering file for the Bu2LLK line with also a lines without PID defined 
@author Luca Pescatore
@date   2017-01-31

modified by Guido Andreassi, 16.05.2017
"""
from Gaudi.Configuration import *
MessageSvc().Format = "% F%60W%S%7W%R%T %0W%M"

#
# Configuration of my costumized stripping line
#

config = {                       
        'BFlightCHI2'            : 100   
        , 'BDIRA'                : 0.9995 
        , 'BIPCHI2'              : 25   
        , 'BVertexCHI2'          : 9    
        , 'DiLeptonPT'           : 0    
        , 'DiLeptonFDCHI2'       : 16   
        , 'DiLeptonIPCHI2'       : 0    
        , 'LeptonIPCHI2'         : 9   
        , 'LeptonPT'             : 300  
        , 'TauPT'                : 0
        , 'TauVCHI2DOF'          : 150
        , 'KaonIPCHI2'           : 9
        , 'KaonPT'               : 400
        , 'KstarPVertexCHI2'     : 25
        , 'KstarPMassWindow'     : 300
        , 'KstarPADOCACHI2'      : 30
        , 'DiHadronMass'         : 2600
        , 'UpperMass'            : 5500
        , 'BMassWindow'          : 1500
        , 'BMassWindowTau'       : 5000
        , 'PIDe'                 : 0
        , 'Trk_Chi2'             : 3
        , 'Trk_GhostProb'        : 0.4
        , 'K1_MassWindow_Lo'     : 0
        , 'K1_MassWindow_Hi'     : 6000
        , 'K1_VtxChi2'           : 12
        , 'K1_SumPTHad'          : 800
        , 'K1_SumIPChi2Had'      : 48.0  
        , 'RelatedInfoTools'     : [
            {'Type'              : 'RelInfoVertexIsolation',
             'Location'          : 'VertexIsoInfo'},
            {'Type'              : 'RelInfoVertexIsolationBDT',
             'Location'          : 'VertexIsoBDTInfo'},
            {'Type'              : 'RelInfoConeVariables',
             'ConeAngle'         : 0.5,
             'IgnoreUnmatchedDescriptors': True, 
             'DaughterLocations' : { 
                    # OPPOSITE SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l-)]CC" : "TrackIsoInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l-)]CC" : "TrackIsoInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l-)]CC" : "TrackIsoInfoL2",
                    # 5-body (quasi 3-body)
                    "[Beauty -> (X+ -> ^X+  X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ ^X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X+ ->  X+  X+ ^X-) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH3",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 -> ^l+  l-)]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 ->  l+ ^l-)]CC" : "TrackIsoInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l-)]CC" : "TrackIsoInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l-)]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l-)]CC" : "TrackIsoInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^StableCharged  StableCharged)]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  StableCharged ^StableCharged)]CC" : "TrackIsoInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l- ->  X-  X-  X+))]CC" : "TrackIsoInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- -> ^X-  X-  X+))]CC" : "TrackIsoInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X- ^X-  X+))]CC" : "TrackIsoInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X-  X- ^X+))]CC" : "TrackIsoInfoL23",
                    # SAME SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l+)]CC" : "TrackIsoInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l+)]CC" : "TrackIsoInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l+)]CC" : "TrackIsoInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l+)]CC" : "TrackIsoInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l+)]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l+)]CC" : "TrackIsoInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  l+)]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  l+)]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  l+)]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^l+)]CC" : "TrackIsoInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l+ ->  X+  X-  X+))]CC" : "TrackIsoInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ -> ^X+  X-  X+))]CC" : "TrackIsoInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+ ^X-  X+))]CC" : "TrackIsoInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+  X- ^X+))]CC" : "TrackIsoInfoL23"
                    }
             },
            {'Type'              : 'RelInfoConeIsolation',
             'ConeSize'          : 0.5,
             'IgnoreUnmatchedDescriptors': True, 
             'DaughterLocations' : { 
                    # OPPOSITE SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l-)]CC" : "ConeIsoInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l-)]CC" : "ConeIsoInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l-)]CC" : "ConeIsoInfoL2",
                    # 5-body (quasi 3-body)
                    "[Beauty -> (X+ -> ^X+  X+  X-) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ ^X+  X-) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X+ ->  X+  X+ ^X-) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH3",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 -> ^l+  l-)]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 ->  l+ ^l-)]CC" : "ConeIsoInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l-)]CC" : "ConeIsoInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l-)]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l-)]CC" : "ConeIsoInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  StableCharged  StableCharged)]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  StableCharged  StableCharged)]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^StableCharged  StableCharged)]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  StableCharged ^StableCharged)]CC" : "ConeIsoInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l- ->  X-  X-  X+))]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l- ->  X-  X-  X+))]CC" : "ConeIsoInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- -> ^X-  X-  X+))]CC" : "ConeIsoInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X- ^X-  X+))]CC" : "ConeIsoInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X-  X- ^X+))]CC" : "ConeIsoInfoL23",
                    # SAME SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l+)]CC" : "ConeIsoInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l+)]CC" : "ConeIsoInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l+)]CC" : "ConeIsoInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l+)]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l+)]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l+)]CC" : "ConeIsoInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l+)]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l+)]CC" : "ConeIsoInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  l+)]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  l+)]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  l+)]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^l+)]CC" : "ConeIsoInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "ConeIsoInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "ConeIsoInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l+ ->  X+  X-  X+))]CC" : "ConeIsoInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l+ ->  X+  X-  X+))]CC" : "ConeIsoInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ -> ^X+  X-  X+))]CC" : "ConeIsoInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+ ^X-  X+))]CC" : "ConeIsoInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+  X- ^X+))]CC" : "ConeIsoInfoL23"
                    }
             },
            {'Type'              : 'RelInfoTrackIsolationBDT',
             'IgnoreUnmatchedDescriptors': True,
             # Use the BDT with 9 input variables
             # This requires that the "Variables" value is set to 2
             'Variables' : 2,
             'WeightsFile'  :  'BsMuMu_TrackIsolationBDT9vars_v1r4.xml',
             'DaughterLocations' : { 
                    # OPPOSITE SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l-)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l-)]CC" : "TrackIsoBDTInfoL2",
                    # 5-body (quasi 3-body)
                    "[Beauty -> (X+ -> ^X+  X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X+ ->  X+ ^X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X+ ->  X+  X+ ^X-) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH3",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 -> ^l+  l-)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 ->  l+ ^l-)]CC" : "TrackIsoBDTInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBDTInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l-)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l-)]CC" : "TrackIsoBDTInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^StableCharged  StableCharged)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  StableCharged ^StableCharged)]CC" : "TrackIsoBDTInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l- ->  X-  X-  X+))]CC" : "TrackIsoBDTInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- -> ^X-  X-  X+))]CC" : "TrackIsoBDTInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X- ^X-  X+))]CC" : "TrackIsoBDTInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X-  X- ^X+))]CC" : "TrackIsoBDTInfoL23",
                    # SAME SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l+)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l+)]CC" : "TrackIsoBDTInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l+)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l+)]CC" : "TrackIsoBDTInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  l+)]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  l+)]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^l+)]CC" : "TrackIsoBDTInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBDTInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBDTInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBDTInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l+ ->  X+  X-  X+))]CC" : "TrackIsoBDTInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ -> ^X+  X-  X+))]CC" : "TrackIsoBDTInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+ ^X-  X+))]CC" : "TrackIsoBDTInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+  X- ^X+))]CC" : "TrackIsoBDTInfoL23"
                    }
             },
            {'Type'              : 'RelInfoBs2MuMuTrackIsolations',
             'IgnoreUnmatchedDescriptors': True,
             'DaughterLocations' : { 
                    # OPPOSITE SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l-)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l-)]CC" : "TrackIsoBs2MMInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l-)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l-)]CC" : "TrackIsoBs2MMInfoL2",
                    # 5-body (quasi 3-body)
                    "[Beauty -> (X+ -> ^X+  X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X+ ->  X+ ^X+  X-) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X+ ->  X+  X+ ^X-) (X0 ->  l+  l-)]CC" : "TrackIsoBs2MMInfoH3",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 -> ^l+  l-)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X+ ->  X+  X+  X-) (X0 ->  l+ ^l-)]CC" : "TrackIsoBs2MMInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  StableCharged  StableCharged)]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^StableCharged  StableCharged)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  StableCharged ^StableCharged)]CC" : "TrackIsoBs2MMInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l- ->  X-  X-  X+))]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l- ->  X-  X-  X+))]CC" : "TrackIsoBs2MMInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- -> ^X-  X-  X+))]CC" : "TrackIsoBs2MMInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X- ^X-  X+))]CC" : "TrackIsoBs2MMInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l- ->  X-  X- ^X+))]CC" : "TrackIsoBs2MMInfoL23",
                    # SAME SIGN
                    # 3-body
                    "[Beauty -> ^StableCharged (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH",
                    "[Beauty ->  StableCharged (X0 -> ^l+  l+)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty ->  StableCharged (X0 ->  l+ ^l+)]CC" : "TrackIsoBs2MMInfoL2",
                    # 5-body
                    "[Beauty -> (X+ -> ^X+ (X0 ->  X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X+ ->  X+ (X0 -> ^X+  X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+ ^X-)) (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH3",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 -> ^l+  l+)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X+ ->  X+ (X0 ->  X+  X-)) (X0 ->  l+ ^l+)]CC" : "TrackIsoBs2MMInfoL2",
                    # 4-body
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  l+)]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  l+)]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^l+)]CC" : "TrackIsoBs2MMInfoL2",
                    # 7-body (quasi 4-body)
                    "[Beauty -> (X0 -> ^X+  X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBs2MMInfoH1",
                    "[Beauty -> (X0 ->  X+ ^X-) (X0 ->  l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBs2MMInfoH2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 -> ^l+  (l+ ->  X+  X-  X+))]CC" : "TrackIsoBs2MMInfoL1",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+ ^(l+ ->  X+  X-  X+))]CC" : "TrackIsoBs2MMInfoL2",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ -> ^X+  X-  X+))]CC" : "TrackIsoBs2MMInfoL21",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+ ^X-  X+))]CC" : "TrackIsoBs2MMInfoL22",
                    "[Beauty -> (X0 ->  X+  X-) (X0 ->  l+  (l+ ->  X+  X- ^X+))]CC" : "TrackIsoBs2MMInfoL23"
                    },
             }
            ],
        }
    

from Gaudi.Configuration import *
from GaudiConfUtils.ConfigurableGenerators import FilterDesktop, CombineParticles
#, DaVinci__N3BodyDecays
from PhysSelPython.Wrappers import Selection, DataOnDemand, MergedSelection, AutomaticData
from StrippingConf.StrippingLine import StrippingLine
from StrippingUtils.Utils import LineBuilder

####################### Add Ks lines back in!!

class Bu2LLK_NoPID_LineBuilder(LineBuilder) :
        
    # now just define keys. Default values are fixed later
    __configuration_keys__ = ( 
        'BFlightCHI2'        
        , 'BDIRA'             
        , 'BIPCHI2'           
        , 'BVertexCHI2'       
        , 'DiLeptonPT'        
        , 'DiLeptonFDCHI2'     
        , 'DiLeptonIPCHI2'     
        , 'LeptonIPCHI2'       
        , 'LeptonPT'          
        , 'TauPT' 
        , 'TauVCHI2DOF'
        , 'KaonIPCHI2'        
        , 'KaonPT'
        , 'KstarPVertexCHI2'
        , 'KstarPMassWindow'
        , 'KstarPADOCACHI2'
        , 'DiHadronMass'               
        , 'UpperMass'
        , 'BMassWindow'
        , 'BMassWindowTau'
        , 'PIDe' 
        , 'Trk_Chi2'
        , 'Trk_GhostProb'
        , 'K1_MassWindow_Lo'
        , 'K1_MassWindow_Hi'
        , 'K1_VtxChi2'
        , 'K1_SumPTHad'
        , 'K1_SumIPChi2Had'
        , 'RelatedInfoTools'
      )
    
    def __init__(self, name, config):
        LineBuilder.__init__(self, name, config)

        self._name = name

        mmXLine_name   = name + "_mm"
        eeXLine_name   = name + "_ee"
        meXLine_name   = name + "_me"
        meXSSLine_name = name + "_meSS"

        from StandardParticles import StdAllNoPIDsPions as Pions
        from StandardParticles import StdAllNoPIDsKaons as Kaons
        from StandardParticles import StdAllNoPIDsKaons as Protons
        from StandardParticles import StdLooseKsLL as KshortsLL 
        from StandardParticles import StdLooseKsDD as KshortsDD  
        from StandardParticles import StdVeryLooseLambdaLL as LambdasLL
        from StandardParticles import StdLooseLambdaDD as LambdasDD  
        
        #from StandardParticles import StdLooseKstar2Kpi as Kstars
        #from StandardParticles import StdLooseLambdastar2pK as Lambdastars  

        CombKstars = CombineParticles()
        #Kstars.Inputs = ["Phys/StdAllNoPIDsKaons/Particles",
        #                    "Phys/StdAllNoPIDsPions/Particles"]
        CombKstars.DecayDescriptor = "[K*(892)0 -> K+ pi-]cc"
        CombKstars.CombinationCut = "(APT > 500.*MeV) & (ADAMASS('K*(892)0') < 300.*MeV) & (ADOCACHI2CUT(30, ''))"
        CombKstars.MotherCut = "(VFASPF(VCHI2) < 25.)"
        Kstars = Selection("SelNoPIDKstars", Algorithm = CombKstars, RequiredSelections = [ Kaons, Pions ] )
 

        CombLambdastars = CombineParticles()
        #Lambdastars.Inputs = ["Phys/StdAllNoPIDsKaons/Particles",
        #                        "Phys/StdAllNoPIDsProtons/Particles"]
        CombLambdastars.DecayDescriptor = "[Lambda(1520)0 -> p+ K-]cc"
        CombLambdastars.CombinationCut = "(AM < 2600.*MeV) &  (ADOCACHI2CUT(30, ''))"
        CombLambdastars.MotherCut = "(VFASPF(VCHI2) < 25.)"
        Lambdastars = Selection("SelNoPIDLambdastars", Algorithm = CombLambdastars, RequiredSelections = [ Protons, Pions ] )

        # 1 : Make K, Ks, K*, and Lambdas

        SelKaons  = self._filterHadron( name   = "KaonsFor" + self._name,
                                        sel    = Kaons,
                                        params = config )

        SelKstars = self._filterHadron( name   = "KstarsFor" + self._name,
                                        sel    =  Kstars,
                                        params = config )

        SelKshortsLL = self._filterHadron( name   = "KshortsLLFor" + self._name,
                                           sel    =  KshortsLL, 
                                           params = config )
      
        SelKshortsDD = self._filterHadron( name   = "KshortsDDFor" + self._name,
                                           sel    =  KshortsDD,
                                           params = config )

        SelLambdasLL = self._filterHadron( name   = "LambdasLLFor" + self._name,
                                           sel    =  LambdasLL,
                                           params = config )

        SelLambdasDD = self._filterHadron( name   = "LambdasDDFor" + self._name,
                                           sel    =  LambdasDD,
                                           params = config )

        SelLambdastars = self._filterHadron( name   = "LambdastarsFor" + self._name,
                                             sel    =  Lambdastars,
                                             params = config )

 
        # 2 : Make Dileptons

        #from StandardParticles import StdLooseDiElectron as DiElectrons
        #from StandardParticles import StdLooseDiMuon as DiMuons 
        from StandardParticles import StdAllNoPIDsMuons as Muons 
        from StandardParticles import StdAllNoPIDsElectrons as Electrons

        CombDiMuons = CombineParticles()
        CombDiMuons.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
        #CombDiMuons.Inputs = ["Phys/StdAllNoPIDsMuons/Particles"]
        CombDiMuons.CombinationCut="(ADOCACHI2CUT(30, ''))"
        CombDiMuons.MotherCut = "(VFASPF(VCHI2) < 25)"
        DiMuons = Selection("SelNoPIDMuons", Algorithm = CombDiMuons, RequiredSelections = [ Muons ] )

        CombDiElectrons = CombineParticles()
        CombDiElectrons.DecayDescriptor = "J/psi(1S) -> e+ e-"
        #CombDiElectrons.Inputs = ["Phys/StdAllNoPIDsElectrons/Particles"]
        CombDiElectrons.DaughtersCuts = { "e+" : "(PT>500*MeV)" }
        CombDiElectrons.CombinationCut = "(AM>30*MeV) & (ADOCACHI2CUT(30,''))"
        CombDiElectrons.MotherCut = "(VFASPF(VCHI2)<25)"
        DiElectrons = Selection("SelNoPIDDiElectrons", Algorithm = CombDiElectrons, RequiredSelections = [ Electrons ] )



        # Now same container as above, but with DiElectronMaker
        from Configurables import DiElectronMaker, ProtoParticleCALOFilter
        from GaudiKernel.SystemOfUnits import *
        from CommonParticles.Utils import *
        

        MakeDiElectronsFromTracks = DiElectronMaker("MakeNoPIDDiElectronsFromTracks")
        MakeDiElectronsFromTracks.Particle = "J/psi(1S)"
        selector = trackSelector (MakeDiElectronsFromTracks , trackTypes = ["Long"])
        MakeDiElectronsFromTracks.addTool(ProtoParticleCALOFilter, name='Electron')
        MakeDiElectronsFromTracks.Electron.Selection = ["RequiresDet='CALO'"]
        MakeDiElectronsFromTracks.DiElectronMassMax = 1000000.*GeV #just to give a high limit.  Not setting anything defaults it to 200 which is wrong.
        MakeDiElectronsFromTracks.DiElectronMassMin = 30.*MeV
        MakeDiElectronsFromTracks.ElectronPtMin = 500.*MeV
        DiElectronsFromTracks = Selection("SelNoPIDDiElectronsFromTracks", Algorithm = MakeDiElectronsFromTracks)




        MuE    = self._makeMuE( "MuEFor"   + self._name, params = config, electronid = None, muonid = None )
        MuE_SS = self._makeMuE( "MuESSFor" + self._name, params = config, electronid = None, muonid = None, samesign = True )
        
        SelDiElectron = self._filterDiLepton( "SelDiElectronFor" + self._name, 
                                              dilepton = DiElectrons,
                                              params   = config,
                                              idcut    = None )

        SelDiElectronFromTracks = self._filterDiLepton( "SelDiElectronFromTracksFor" + self._name, 
                                              dilepton = DiElectronsFromTracks,
                                              params   = config,
                                              idcut    = None )
        
        SelDiMuon = self._filterDiLepton( "SelDiMuonsFor" + self._name, 
                                          dilepton = DiMuons,
                                          params   = config,
                                          idcut    = None )
        
        SelMuE = self._filterDiLepton( "SelMuEFor" + self._name, 
                                       dilepton = MuE,
                                       params   = config,
                                       idcut    = None )

        SelMuE_SS = self._filterDiLepton( "SelMuESSFor" + self._name, 
                                          dilepton = MuE_SS,
                                          params   = config,
                                          idcut    = None )
        
        # 4 : Combine Particles

        SelB2eeX = self._makeB2LLX(eeXLine_name,
                                   dilepton = SelDiElectron,
                                   hadrons  = [ SelKaons, SelKstars, SelLambdasLL, SelLambdasDD , SelLambdastars, SelKshortsLL, SelKshortsDD ],
                                   params   = config,
                                   masscut  = "ADAMASS('B+') <  %(BMassWindow)s *MeV" % config )

        SelB2eeXFromTracks = self._makeB2LLX(eeXLine_name + "dem",
                                   dilepton = SelDiElectronFromTracks,
                                   hadrons  = [ SelKaons, SelKstars, SelLambdasLL, SelLambdasDD , SelLambdastars, SelKshortsLL, SelKshortsDD ],
                                   params   = config,
                                   masscut  = "ADAMASS('B+') <  %(BMassWindow)s *MeV" % config )

        SelB2mmX = self._makeB2LLX(mmXLine_name,
                                   dilepton = SelDiMuon,
                                   hadrons  = [ SelKaons, SelKstars, SelLambdasLL, SelLambdasDD , SelLambdastars, SelKshortsLL, SelKshortsDD ],
                                   params   = config,
                                   masscut  = "ADAMASS('B+') <  %(BMassWindow)s *MeV"% config)         

        SelB2meX = self._makeB2LLX(meXLine_name,
                                   dilepton = SelMuE,
                                   hadrons  = [ SelKaons, SelKstars, SelLambdasLL, SelLambdasDD , SelLambdastars, SelKshortsLL, SelKshortsDD ],
                                   params   = config,
                                   masscut  = "ADAMASS('B+') <  %(BMassWindow)s *MeV" % config )  

        SelB2meX_SS = self._makeB2LLX(meXSSLine_name,
                                      dilepton = SelMuE_SS,
                                      hadrons  = [ SelKaons, SelKstars, SelLambdasLL, SelLambdasDD , SelLambdastars, SelKshortsLL, SelKshortsDD ],
                                      params   = config,
                                      masscut  = "ADAMASS('B+') <  %(BMassWindow)s *MeV" % config )


        # 5 : Declare Lines

        SPDFilter = {
            'Code'      : " ( recSummary(LHCb.RecSummary.nSPDhits,'Raw/Spd/Digits') < 600 )" ,
            'Preambulo' : [ "from LoKiNumbers.decorators import *", "from LoKiCore.basic import LHCb" ]
            }
        
        self.B2eeXLine = StrippingLine(eeXLine_name + "Line",
                                       prescale          = 1,
                                       postscale         = 1,
                                       selection         = SelB2eeX,
                                       RelatedInfoTools  = config['RelatedInfoTools'],
                                       FILTER            = SPDFilter, 
                                       RequiredRawEvents = [],
                                       MDSTFlag          = False )

        self.B2eeXFromTracksLine = StrippingLine(eeXLine_name + "Line_dem",
                                        prescale          = 1,
                                        postscale         = 1,
                                        selection         = SelB2eeXFromTracks,
                                        RelatedInfoTools  = config['RelatedInfoTools'],
                                        FILTER            = SPDFilter, 
                                        RequiredRawEvents = [],
                                        MDSTFlag          = False )

        self.B2mmXLine = StrippingLine(mmXLine_name + "Line",
                                       prescale          = 1,
                                       postscale         = 1,
                                       selection         = SelB2mmX,
                                       RelatedInfoTools  = config['RelatedInfoTools'],
                                       FILTER            = SPDFilter, 
                                       RequiredRawEvents = [],
                                       MDSTFlag          = False )

        self.B2meXLine = StrippingLine(meXLine_name + "Line",
                                       prescale          = 1,
                                       postscale         = 1,
                                       selection         = SelB2meX,
                                       RelatedInfoTools  = config['RelatedInfoTools'],
                                       FILTER            = SPDFilter, 
                                       RequiredRawEvents = [],
                                       MDSTFlag          = False )


        self.B2meX_SSLine = StrippingLine(meXSSLine_name + "Line",
                                          prescale          = 1,
                                          postscale         = 1,
                                          selection         = SelB2meX_SS,
                                          RelatedInfoTools  = config['RelatedInfoTools'],
                                          FILTER            = SPDFilter, 
                                          RequiredRawEvents = [],
                                          MDSTFlag          = False )

        # 6 : Register Lines

        self.registerLine( self.B2eeXLine )
        self.registerLine( self.B2eeXFromTracksLine )
        self.registerLine( self.B2mmXLine )
        self.registerLine( self.B2meXLine )
        self.registerLine( self.B2meX_SSLine )

#####################################################
    def _filterHadron( self, name, sel, params ):
        """
        Filter for all hadronic final states
        """

        # requires all basic particles to have IPCHI2 > KaonIPCHI2
        # and hadron PT > KaonPT
        # need to add the ID here
        _Code = "(PT > %(KaonPT)s *MeV) & " \
                "(M < %(DiHadronMass)s*MeV) & " \
                "((ISBASIC & (MIPCHI2DV(PRIMARY) > %(KaonIPCHI2)s)) | " \
                "(NDAUGHTERS == NINTREE(ISBASIC & (MIPCHI2DV(PRIMARY) > %(KaonIPCHI2)s))))" % params

        _Filter = FilterDesktop( Code = _Code )

        return Selection( name, Algorithm = _Filter, RequiredSelections = [ sel ] )
#####################################################
    def _filterDiLepton( self, name, dilepton, params, idcut = None ) :
        """
        Handy interface for dilepton filter
        """

        _Code = "(ID=='J/psi(1S)') & "\
                "(PT > %(DiLeptonPT)s *MeV) & "\
                "(MM < %(UpperMass)s *MeV) & "\
                "(MINTREE(ABSID<14,PT) > %(LeptonPT)s *MeV) & "\
                "(MINTREE(ABSID<14,MIPCHI2DV(PRIMARY)) > %(LeptonIPCHI2)s) & "\
                "(VFASPF(VCHI2/VDOF) < 9) & (BPVVDCHI2 > %(DiLeptonFDCHI2)s) & "\
                "(MIPCHI2DV(PRIMARY) > %(DiLeptonIPCHI2)s)" % params

        # add additional cut on PID if requested
        if idcut : _Code += ( " & " + idcut ) 

        _Filter = FilterDesktop( Code = _Code )
    
        return Selection(name, Algorithm = _Filter, RequiredSelections = [ dilepton ] )

####################################################
    def _makeMuE( self, name, params, electronid = None, muonid = None , samesign = False):
        """
        Makes MuE combinations 
        """

        from StandardParticles import StdAllNoPIDsMuons as Muons
        from StandardParticles import StdAllNoPIDsElectrons as Electrons 

        _DecayDescriptor = "[J/psi(1S) -> mu+ e-]cc"
        if samesign : _DecayDescriptor = "[J/psi(1S) -> mu+ e+]cc"

        _MassCut = "(AM > 100*MeV)" 
        
        _MotherCut = "(VFASPF(VCHI2/VDOF) < 9)"

        _DaughtersCut = "(PT > %(LeptonPT)s) & " \
                        "(MIPCHI2DV(PRIMARY) > %(LeptonIPCHI2)s)" % params

        _Combine = CombineParticles( DecayDescriptor = _DecayDescriptor,
                                     CombinationCut  = _MassCut,
                                     MotherCut       = _MotherCut )

        _MuonCut     = _DaughtersCut
        _ElectronCut = _DaughtersCut

        if muonid     : _MuonCut     += ( "&" + muonid )
        if electronid : _ElectronCut += ( "&" + electronid )

        _Combine.DaughtersCuts = {
            "mu+" : _MuonCut,
            "e+"  : _ElectronCut
            }
        
        return Selection(name, Algorithm = _Combine, RequiredSelections = [ Muons, Electrons ] )

#####################################################
    def _makeB2LLX( self, name, dilepton, hadrons, params, masscut = "(ADAMASS('B+')< 1500 *MeV" ):
        """
        CombineParticles / Selection for the B 
        """

        _Decays = [ "[ B+ -> J/psi(1S) K+ ]cc",
                    "[ B0 -> J/psi(1S) KS0 ]cc", 
                    "[ B0 -> J/psi(1S) K*(892)0 ]cc",
                    "[ Lambda_b0 -> J/psi(1S) Lambda0 ]cc",                            
                    "[ Lambda_b0 -> J/psi(1S) Lambda(1520)0 ]cc" ]
        
        _Cut = "((VFASPF(VCHI2/VDOF) < %(BVertexCHI2)s) "\
               "& (BPVIPCHI2() < %(BIPCHI2)s) "\
               "& (BPVDIRA > %(BDIRA)s) "\
               "& (BPVVDCHI2 > %(BFlightCHI2)s))" % params
        
        _Combine = CombineParticles( DecayDescriptors = _Decays,
                                     CombinationCut   = masscut,
                                     MotherCut        = _Cut )
        
        _Merge = MergedSelection( "Merge" + name, RequiredSelections = hadrons )

        return Selection(name, Algorithm = _Combine, RequiredSelections = [ dilepton, _Merge ] ) 

#
# Build the streams and stripping object
#
from StrippingConf.Configuration import StrippingConf, StrippingStream
from StrippingSettings.Utils import strippingConfiguration
from StrippingArchive.Utils import buildStream, cloneLinesFromStream
from StrippingArchive import strippingArchive

stripping='stripping26'

def quickBuild(streamName,stripping):
    config  = strippingConfiguration(stripping)
    archive = strippingArchive(stripping)
    return buildStream(stripping=config, streamName=streamName, archive=archive)

streams = []

leptonic         = quickBuild('Leptonic',stripping)
leptonic.lines[:] = [ x for x in leptonic.lines if 'Bu2LLK' in x.name() ]
for line in leptonic.lines :
   print "Leptonic has a line called " + line.name()
   line._prescale = 1
   line._postscale = 1
streams.append( leptonic )

AllStreams = StrippingStream("Bu2KLL_NoPID.Strip")
for stream in streams:
    AllStreams.appendLines(stream.lines)

## Add also my line
myBuilder = Bu2LLK_NoPID_LineBuilder('Bu2LLKNoPID', config)
AllStreams.appendLines( myBuilder.lines() )

prefix = 'Strip'
sc = StrippingConf( Streams = [ AllStreams ],
                    TESPrefix = prefix,
#                    HDRLocation='Phys/DecReports',
                    MaxCandidates = 2000 )

AllStreams.sequence().IgnoreFilterPassed = False # so that we get only selected events written out

from DSTWriters.microdstelements import *
from DSTWriters.Configuration import SelDSTWriter, stripDSTStreamConf, stripDSTElements

#############################################################################
#
# Configuration of SelDSTWriter
#
SelDSTWriterElements = {
    'default'              : stripDSTElements(stripPrefix=prefix)
    }


SelDSTWriterConf = {
    'default'              : stripDSTStreamConf(stripPrefix=prefix)
    }

for stream in sc.activeStreams() :
   print "there is a stream called " + stream.name() + " active"

dstWriter = SelDSTWriter( "MyDSTWriter",
                          StreamConf = SelDSTWriterConf,
                          MicroDSTElements = SelDSTWriterElements,
                          OutputFileSuffix ='RD',
                          SelectionSequences = sc.activeStreams()
                          )

# Add stripping TCK
from Configurables import StrippingTCK
stck = StrippingTCK(HDRLocation = '/Event/Strip/Phys/DecReports', TCK=0x409f0045) 

# Fancy things
from Configurables import StrippingReport, AlgorithmCorrelationsAlg
report = StrippingReport(Selections = sc.selections())
correlations = AlgorithmCorrelationsAlg(Algorithms = sc.selections())

from Configurables import EventNodeKiller
event_node_killer = EventNodeKiller('StripKiller')
event_node_killer.Nodes = ['/Event/AllStreams', '/Event/Strip']

#
# DaVinci Configuration
#
from Configurables import DaVinci
DaVinci().InputType = 'MDST'
DaVinci().DataType = "2016"
DaVinci().Simulation = True
DaVinci().EvtMax = 1000
DaVinci().HistogramFile = "DVHistos.root"
DaVinci().appendToMainSequence( [ event_node_killer ] )
DaVinci().appendToMainSequence( [ sc.sequence() ] )
DaVinci().appendToMainSequence( [ stck ] )
#DaVinci().appendToMainSequence( [ report, correlations ] )
#DaVinci().appendToMainSequence( [ dstWriter.sequence() ] )
#DaVinci().UseTrigRawEvent=True
#DaVinci().ProductionType = "Stripping"

