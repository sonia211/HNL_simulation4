from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *
from collections import defaultdict

def set_branches(full_descriptor,names) :
    descriptors = full_descriptor.split('||') #split the parts in OR and treat them separately
    branches = defaultdict(list)
    for descriptor in descriptors:
        descriptor = descriptor.replace("^","")
        branches[names[0]].append("(^"+descriptor+")") #no caret for the mother
        cleandesc = descriptor.replace("->"," ").replace("\ )"," ")\
                    .replace("( "," ").replace("[ "," ")\
                    .replace(" ]"," ").replace("==>"," ")
        daughters = cleandesc.split()[1:]
        pos = 0
        for ni,n in enumerate(names[1:]) :
            
            pos = descriptor.find(daughters[ni],pos)
            branches[n].append(''.join(list(descriptor[:pos] + "^" + descriptor[pos:])))
            pos += 1

    branches_full = {}
    for n in names : #now we can join back the n parts that were in OR
        branches_full[n] = " || ".join(branches[n])
    return branches_full

def ReStrip_old(MyLines,version,streams) :

    StrippingVersion = "stripping"+version
    from Configurables import EventNodeKiller
    from Configurables import ProcStatusCheck
    from StrippingArchive.Utils import buildStreams
    from StrippingArchive import strippingArchive
    from StrippingConf.Configuration import StrippingStream
    from StrippingConf.Configuration import StrippingConf
    from StrippingSettings.Utils import strippingConfiguration
    NodeKiller       = EventNodeKiller( "StripKiller" )
    NodeKiller.Nodes = [ "/Event/AllStreams","/Event/Strip" ]
    Streams = buildStreams( stripping = strippingConfiguration( StrippingVersion ),
                        archive   = strippingArchive( StrippingVersion ) )
    MyStream = StrippingStream( "MyStream" )
    for Stream in Streams:
        for Line in Stream.lines:
            if Line.name() in MyLines:
                MyStream.appendLines( [ Line ] )

    ReStripping = StrippingConf( Streams           = [ MyStream ],
                                 MaxCandidates     = 2000,
                                 AcceptBadEvents   = False,
                                 BadEventSelection = ProcStatusCheck(),
                                 TESPrefix         = 'Strip',
                                 ActiveMDSTStream  = True,
                                 MicroDSTStreams   = streams,
                                 HDRLocation       = "SomeNonExistingLocation" )
    
    return ReStripping, [ NodeKiller, ReStripping.sequence() ]
    
    
def ReStrip(mylines,confnames,streams) :

    from Configurables import EventNodeKiller, ProcStatusCheck
    from StrippingArchive.Utils import buildStreams
    from StrippingArchive import strippingArchive
    from StrippingConf.Configuration import StrippingStream
    from StrippingConf.Configuration import StrippingConf
    from StrippingSettings.Utils import strippingConfiguration

    NodeKiller       = EventNodeKiller( "StripKiller" )
    NodeKiller.Nodes = [ "/Event/AllStreams","/Event/Strip" ]

    from StrippingSelections import buildersConf
    from StrippingSelections.Utils import lineBuilder, buildStreamsFromBuilder

    confs = buildersConf()
    
    mystream = StrippingStream( "MyStream" )
    for name in confnames:
        strip_streams = buildStreamsFromBuilder(confs,name)
        for stream in strip_streams :
            for line in stream.lines:
                if line.name() in mylines:
                    print "Adding ", line.name(), "for restripping"
                    mystream.appendLines( [ line ] )

    restrip = StrippingConf( Streams = [ mystream ],
                    MaxCandidates = 2000,
                    AcceptBadEvents = False,
                    BadEventSelection = ProcStatusCheck(),
                    TESPrefix = 'Strip',
                    ActiveMDSTStream = True,
                    #Verbose = True,
                    MicroDSTStreams = streams )

    return restrip, [ NodeKiller, restrip.sequence() ]


