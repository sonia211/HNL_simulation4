from Gaudi.Configuration import *

def ConfigDaVinci(DataType,DataYear,UserAlgs=[],RootInTES="",isTest=False,Mag="",restrip=[],onlytuple=False,rerunCalo=False,decay="") :
    
    from Configurables import DaVinci
    from Configurables import CondDB

    DaVinci().UserAlgorithms  += UserAlgs
    DaVinci().EvtMax    = -1
    DaVinci().PrintFreq = 10000
    if isTest :
        DaVinci().EvtMax     = 1000
        if DataType == "CL" :
            DaVinci().EvtMax = 100000
        DaVinci().PrintFreq  = 100

    DaVinci().TupleFile = "DVNtuple.root"


    if onlytuple : return
    DaVinci().DataType = "20"+DataYear.split('_')[0]
    if isTest: print DataYear

    if DataType == "CL" :
        
        DaVinci().InputType  = "MDST"
        DaVinci().RootInTES  = "/Event/"+RootInTES
        DaVinci().Simulation = False
        DaVinci().Lumi       = True
        CondDB( LatestGlobalTagByDataType = "20" + DataYear.split('_')[0])

    if DataType == "MC" :
    
        DaVinci().appendToMainSequence( restrip )
        if RootInTES == "" or RootInTES == "Bu2LLK_NoPID.Strip" or RootInTES == 'Bu2LLK_NoPID_LongLived.Strip':
            DaVinci().RootInTES = ""
            DaVinci().InputType = "DST"
        else:
            DaVinci().InputType = "MDST"
            DaVinci().RootInTES = "/Event/"+RootInTES
          
        #importOptions("$STRIPPINGSELECTIONSROOT/tests/data/Reco16_Run182594.py")
        if rerunCalo: importOptions("$APPCONFIGOPTS/DaVinci/DV-RedoCaloPID-Stripping21.py")
        
        from Configurables import EventTuple       
        DaVinci().UserAlgorithms += [ EventTuple("EventTuple") ]
        
        DaVinci().Simulation = True
        DaVinci().Lumi       = False

        """
        TagDDDB              = "dddb-20150522"
        TagCondDB            = "sim-20150522"
        if DataYear == "11" :
            TagDDDB   += "-1"
            TagCondDB += "-1"
        if DataYear == "12" :
            TagDDDB   += "-2"
            TagCondDB += "-2"
        TagCondDB += "-vc"
        if Mag == "MD" or Mag == "Down" or Mag == "DOWN":
            TagCondDB += "-md100"
        if Mag == "MU" or Mag == "Up" or Mag == "UP":
            TagCondDB += "-mu100"
        DaVinci().DDDBtag   = "dddb-20150724" #BRUTAL TagDDDB
        DaVinci().CondDBtag = "sim-20161124-2-vc-mu100" #BRUTAL TagCondDB
        """
        #above code replaced by tags dictionary, still under test
        from DV_Tags import get_MC_tag
        
        print decay, DataYear, Mag
        DaVinci().DDDBtag   = get_MC_tag(decay, DataYear, Mag, "DDDB")
        DaVinci().CondDBtag = get_MC_tag(decay, DataYear, Mag, "CONDDB")


