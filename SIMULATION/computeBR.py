
import sys
sys.path.insert(0, '../FairShip/python')
from hnl import *

import yaml
#HNL decay


with open("./cfg_files/cfg_scan.yml", 'r') as stream:
    try:
        cfg_file = yaml.safe_load(stream)
    except yaml.YAMLError as exc:
        print(exc)


mNvec = cfg_file['mNvec']
U2vec = cfg_file['U2vec']
chn = cfg_file['chn']
chstring = cfg_file['chstring']


with open('./hnldecayBR_ch'+chn+'.dat', 'w') as f1, open('./hnltau0_ch'+chn+'.dat', 'w') as f2:
	for mN in mNvec:
		print "mN ", mN, ", type", type(mN)
		for U2 in U2vec:
			U2 = float(U2)
			print "u2 ", U2, ", type", type(U2)
			b = HNL(mN,[0., U2, 0.],True)
			f1.write("%f " % b.findBranchingRatio(chstring))
			f2.write("%f " % b.computeNLifetime())
		f1.write("\n"); f2.write("\n")
			
        
