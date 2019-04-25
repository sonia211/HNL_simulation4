from Gaudi.Configuration       import *
from GaudiKernel.SystemOfUnits import *
from Configurables import LoKi__Hybrid__TupleTool

def getLoKiToolsDictionary():

    reldict = {'RELINFO':{}}
    myvars = {
        #add RelInfoConeVariables
        'cone' : {'vars' : ['CONEANGLE','CONEMULT','CONEPTASYM'],
                  'locations' : ['TrackIsoInfoH1','TrackIsoInfoH2','TrackIsoInfoL1','TrackIsoInfoL2'] },
        #add RelInfoTrackIsolationBDT
        'isoBDT' : {'vars' : ['TRKISOBDTFIRSTVALUE','TRKISOBDTSECONDVALUE','TRKISOBDTTHIRDVALUE'],
                    'locations' : ['TrackIsoBDTInfoH1','TrackIsoBDTInfoH2','TrackIsoBDTInfoL1','TrackIsoBDTInfoL2'] } ,
        #add RelInfoConeIsolation
        'coneIso' : {'vars' : ['CC_ANGLE','CC_MULT','CC_PTASYM','CC_SPT','CC_PX','CC_PY','CC_PZ','CC_PXASYM','CC_PYASYM','CC_PZASYM','CC_DELTAETA','CC_DELTAPHI',
                               'NC_ANGLE','NC_MULT','NC_PTASYM','NC_SPT','NC_PX','NC_PY','NC_PZ','NC_PXASYM','NC_PYASYM','NC_PZASYM','NC_DELTAETA','NC_DELTAPHI',
                               'CC_MAXPT_PT','CC_MAXPT_PX','CC_MAXPT_PY','CC_MAXPT_PZ','NC_MAXPT_PT','NC_MAXPT_PX','NC_MAXPT_PY','NC_MAXPT_PZ',
                               'CC_IT','NC_IT','CCNC_IT'],
                    'locations' : ['ConeIsoInfoH1','ConeIsoInfoH2','ConeIsoInfoL1','ConeIsoInfoL2'] },
        #add RelInfoBs2MuMuTrackIsolations
        'Bs2MuMuIso' : {'vars' : ['BSMUMUTRACKPLUSISO', 'BSMUMUTRACKPLUSISOTWO', 'ISOTWOBODYQPLUS', 'ISOTWOBODYMASSISOPLUS', 'ISOTWOBODYCHI2ISOPLUS', 'ISOTWOBODYISO5PLUS', 'ISOTWOBODYISO5PLUS', 'BSMUMUTRACKID', 'BSMUMUTRACKTOPID'],
                    'locations' : ['TrackIsoBs2MMInfoH1', 'TrackIsoBs2MMInfoH2', 'TrackIsoBs2MMInfoL1', 'TrackIsoBs2MMInfoL2'] }
            }

    #'BSMUMUTRACKMINUSISO','BSMUMUTRACKMINUSISO','BSMUMUTRACKCDFISO']
    #'TrackIsoBs2MMInfoH1','TrackIsoBs2MMInfoH2','TrackIsoBs2MMInfoL1','TrackIsoBs2MMInfoL2',
    #'ConeIsoInfoH1','ConeIsoInfoH2','ConeIsoInfoL1','ConeIsoInfoL2',

    for name,vardict in myvars.iteritems() :
        for var in vardict['vars'] :
            for loc in vardict['locations'] :
                reldict['RELINFO'][loc+"_"+var] = {'varName':var,'Location':loc,'Default':-1.}

    #add RelInfoVertexIsolation
    for v in [ 'VTXISONUMVTX', 'VTXISODCHI2ONETRACK', 'VTXISODCHI2MASSONETRACK', 'VTXISODCHI2TWOTRACK', 'VTXISODCHI2MASSTWOTRACK']:
        reldict['RELINFO']['VtxIso_'+v] = {'varName':v,'Location':'VertexIsoInfo','Default':-1.}

    #add RelInfoVertexIsolationBDT
    for v in [ 'VTXISOBDTHARDFIRSTVALUE', 'VTXISOBDTHARDSECONDVALUE', 'VTXISOBDTHARDTHIRDVALUE',]:
        reldict['RELINFO']['VtxIsoBDT_'+v] = {'varName':v,'Location':'VertexIsoBDTInfo','Default':-1.}
    
    return reldict

def getLoKiTool(name,line,isMC=True,restrip_or_mdst=False) :

    lokiDict = getLoKiToolsDictionary()

    LoKi_Tool = LoKi__Hybrid__TupleTool('LoKi_Tool'+name)
    for name, args in lokiDict['RELINFO'].iteritems():
        if isMC : 
            if "NoPID" in line:   lokipath = '/Event/Bu2KLL_NoPID_LongLived.Strip/Phys/'+line+'/'+args['Location']
            elif restrip_or_mdst: lokipath = 'Phys/'+line+'/'+args['Location']
            else:                 lokipath = 'AllStreams/Phys/'+line+'/'+args['Location']

        else : lokipath = 'Phys/'+line+'/'+args['Location']
        LoKi_Tool.Variables[name] = "RELINFO('%s','%s',%f)"%(lokipath,args['varName'],args['Default'])
    return LoKi_Tool


