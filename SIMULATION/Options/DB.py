strip_db = { 
         '11':'21r1p1',
         '12':'21r0p1',
         '15':'24r0p1',
         '16':'28'    ,
         '17':'29r2',
         }


DV_db = {'11':'gandreas_v39r1p1_hop',
         '12':'gandreas_v39r1p1_hop',
         '15':'v42r6p1',
         '16':'v42r6p1',
         '11_Filtered':'gandreas_v39r1p1_hop',
         '12_Filtered':'gandreas_v39r1p1_hop', 
         '15_Filtered':'v42r6p1', 
         '16_Filtered':'v42r7p1', 
         '17':'v42r6p1',}
 


decays_db = {

    'Lb_Lemu' : 
        {
            'descriptor' : '([[Lambda_b0]os ==> ^e+ ^mu- ^(Lambda0 ==> ^p+ ^pi-)]CC) || ([[Lambda_b0]os ==> ^e- ^mu+ ^(Lambda0 ==> ^p+ ^pi-)]CC)',
            #some events get inevitably lost due to the Lambda0 interacting with the detector before being able to decay. see https://groups.cern.ch/group/lhcb-davinci/Lists/Archive/DispForm.aspx?ID=19670
            'descriptor_noLdec' : '([[Lambda_b0]os ==> ^e+ ^mu- ^Lambda0]CC) || ([[Lambda_b0]os ==> ^e- ^mu+ ^Lambda0]CC)',
            #for MC actually the two CC are not necessary since e-mu+ is not generated, so it would be sufficient to have: '(Lambda_b0 ==> ^e+ ^mu- ^Lambda0) || (Lambda_b~0 ==> ^e+ ^mu- ^Lambda~0)'. Same goes for other decays here. But better be safe than sorry.
            'MC_samples':['11_Filtered','12_Filtered','15_Filtered','16_Filtered'],
            'DST':{'11_Filtered':True,'12_Filtered':True,'15_Filtered':True,'16_Filtered':True},
            'conddb':{'11_Filtered':'sim-20160614-1-vc-{0}100','12_Filtered':'sim-20160321-2-vc-{0}100',
                      '15_Filtered':'sim-20161124-vc-md100','16_Filtered':'sim-20170721-2-vc-md100'},
            'dddb':{'11_Filtered':'dddb-20160318-1','12_Filtered':'dddb-20150928','12':'dddb-20130929',
                      '15_Filtered':'dddb-20170721-3','16_Filtered':'dddb-20170721-3'},


        },
    'Lb_LemuSS' : 
        {
            'descriptor' : '([Lambda_b0 ==> ^e+ ^mu+ ^(Lambda0 ==> ^p+ ^pi-)]CC) || ([Lambda_b0 ==> ^e- ^mu- ^(Lambda0 ==> ^p+ ^pi-)]CC)',
            'descriptor_noLdec' : '([Lambda_b0 ==> ^e+ ^mu+ ^Lambda0]CC) || ([Lambda_b0 ==> ^e- ^mu- ^Lambda0]CC)',
            'MC_samples':[]
        },
    'Lb_JpsiL_ee' : 
        {
            'descriptor' : '[Lambda_b0 -> ^(J/psi(1S) ==> ^e+ ^e-) ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0 -> ^(J/psi(1S) ==> ^e+ ^e-) ^Lambda0]CC',
            'MC_samples':['11_Filtered','12_Filtered','15_Filtered','16_Filtered'],
            'DST':{'11_Filtered':True,'12_Filtered':True,'15_Filtered':True,'16_Filtered':True},
            'conddb':{'11_Filtered':'sim-20160614-1-vc-{0}100','12_Filtered':'sim-20160321-2-vc-{0}100',
                      '15_Filtered':'sim-20161124-vc-md100','16_Filtered':'sim-20170721-2-vc-md100'},
            'dddb':{'11_Filtered':'dddb-20160318-1','12_Filtered':'dddb-20150928','12':'dddb-20130929',
                      '15_Filtered':'dddb-20170721-3','16_Filtered':'dddb-20170721-3'},


        },
    'Lb_JpsiL_mm' : 
        {
            'descriptor' : '[Lambda_b0 -> ^(J/psi(1S) ==> ^mu+ ^mu-) ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0 -> ^(J/psi(1S) ==> ^mu+ ^mu-) ^Lambda0]CC',
            'MC_samples':['11','12','15','16_Filtered','16_S28'],
            'DST':{'11':True,'12':True,'15':False,'16_Filtered':True,'16_S26':False,'16_S28':True},
            'conddb':{'11':'sim-20160614-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16_S28':'sim-20161124-2-vc-{0}100','16_Filtered':'sim-20161124-2-vc-{0}100'},
            'dddb':{'11':'dddb-20160318-1','12':'dddb-20150928','15':'dddb-20150724','16_S28':'dddb-20150724','16_Filtered':'dddb-20150724'}

        },
    'Lb_Psi2SL_mm' : 
        {
            'descriptor' : '[Lambda_b0 -> ^(psi(2S) ==> ^mu+ ^mu-) ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0]cc -> ^(psi(2S) ==> ^mu+ ^mu-) ^Lambda0',
            'MC_samples':['11','12'],
            'DST':{'11':True,'12':True},
            'conddb':{'11':'sim-20160614-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20160318-1','12':'dddb-20150928','15':'dddb-20150724','16':'dddb-20150724',}

        },
    'Lb_Psi2SL_JpsiPiPi_mm' : 
        {
            'descriptor' : '[Lambda_b0 -> ^(psi(2S) ==> (^J/psi(1S) ==> ^mu+ ^mu-) ^pi+ ^pi- ) ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0 -> ^(psi(2S) ==> ^mu+ ^mu-) ^Lambda0]CC',
            'MC_samples':['12'],
            'DST':{'12':True},
        },

    'Lb_Lee' : 
        {
            'descriptor' : '[Lambda_b0 ==>  ^e+ ^e- ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0 ==> ^e+ ^e- ^Lambda0]CC',
            'MC_samples':['11_Filtered','12','12_Filtered','15_Filtered','16_Filtered'],
            'DST':{'11_Filtered':True,'12':True,'12_Filtered':True,'15_Filtered':True,'16_Filtered':True},
            'conddb':{'11_Filtered':'sim-20160614-1-vc-{0}100','12_Filtered':'sim-20160321-2-vc-{0}100','12':'sim-20130522-1-vc-{0}100',
                      '15_Filtered':'sim-20161124-vc-md100','16_Filtered':'sim-20170721-2-vc-md100'},
            'dddb':{'11_Filtered':'dddb-20160318-1','12_Filtered':'dddb-20150928','12':'dddb-20130929',
                      '15_Filtered':'dddb-20170721-3','16_Filtered':'dddb-20170721-3'},



        },
    'Lb_Lmm' : 
        {
            'descriptor' : '[Lambda_b0 ==> ^mu+ ^mu- ^(Lambda0 ==> ^p+ ^pi-)]CC',
            'descriptor_noLdec' : '[Lambda_b0 ==> ^mu+ ^mu- ^Lambda0]CC',
            'MC_samples':['11','12','15','16'],
            'DST':{'11':True,'12':True,'15':False,'16':False},
            'conddb':{'11':'sim-20160614-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20160318-1','12':'dddb-20150928','15':'dddb-20150724','16':'dddb-20150724',}

        },
    'Bd_JpsiKs_ee' : 
        {
            'descriptor' : '[B0 -> ^(J/psi(1S) ==> ^e+ ^e-) ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0 -> ^(J/psi(1S) ==> ^e+ ^e-) ^KS0]CC',
            'MC_samples':['12','15','16'],
            'DST':{'11':True,'12':True,'15':False,'16':False},
            'conddb':{'11':'sim-20130522-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20130929','12':'dddb-20150928','15':'dddb-20150724','16':'dddb-20150724',},


        },
    'Bd_JpsiKs_mm' : 
        {
            'descriptor' : '[B0 -> ^(J/psi(1S) ==> ^mu+ ^mu-) ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0 -> ^(J/psi(1S) ==> ^mu+ ^mu-) ^KS0]CC',
            'MC_samples':['11','12','15','16'],
            'DST':{'11':True,'12':True,'15':True,'16':True},
            'conddb':{'11':'sim-20160614-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20160318-1','12':'dddb-20150928','15':'dddb-20150724','16':'dddb-20150724',}

        },
    'Bd_Psi2SKs_mm' : 
        {
            'descriptor' : '[B0 -> ^(psi(2S) ==> ^mu+ ^mu-) ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0 -> ^(psi(2S) ==> ^mu+ ^mu-) ^KS0]CC',
            'MC_samples':['11','12','15','16'],
            'DST':{'11':True,'12':True,'15':False,'16':False}, 
            'conddb':{'11':'sim-20130522-1-vc-{0}100','12':'sim-20160321-2-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20130929','12':'dddb-20150928','15':'dddb-20150724','16':'dddb-20150724',}

        },
    'Bd_Psi2SKs_JpsiPiPi_mm' : 
        {
            'descriptor' : '[B0 -> ^(psi(2S) ==> (^J/psi(1S) ==> ^mu+ ^mu-) ^pi+ ^pi- ) ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0 -> ^(psi(2S) ==> ^mu+ ^mu-) ^KS0]CC',
            'MC_samples':['11','12'],
            'DST':{'11':True,'12':True},
        },

    'Bd_Ksee' : 
        {
            'descriptor' : '[B0  ==> ^e+ ^e- ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0  ==> ^e+ ^e- ^KS0]CC',
            'MC_samples':['12','16'],
            'DST':{'12':True,'16':True},
            'conddb':{'11':'sim-20130522-1-vc-{0}100','12':'sim-20130522-1-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20130929','12':'dddb-20130929','15':'dddb-20150724','16':'dddb-20150724',}

        },
    'Bd_Ksmm' : 
        {
            'descriptor' : '[B0 ==> ^mu+ ^mu- ^(KS0 ==> ^pi+ ^pi-)]CC',
            'descriptor_noLdec' : '[B0 ==> ^mu+ ^mu- ^KS0]CC',
            'MC_samples':['12'],
            'DST':{'12':True},
            'conddb':{'11':'sim-20130522-1-vc-{0}100','12':'sim-20130522-1-vc-{0}100','15':'sim-20161124-vc-{0}100','16':'sim-20161124-2-vc-{0}100',},
            'dddb':{'11':'dddb-20130929','12':'dddb-20130929','15':'dddb-20150724','16':'dddb-20150724',}

        }

}
