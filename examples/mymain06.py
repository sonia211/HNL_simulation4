#!/usr/bin/python
### Inspired from the main34.py Pythia8 tutorial script written by Phillip Ilten.
import sys
cfg = open('Makefile.inc')
lib = '../lib'
for line in cfg:
    if line.startswith('PREFIX_LIB='): lib = line[11:-1]; break
sys.path.insert(0, lib)

import pythia8
import ROOT
import math
import numpy as np
from skhep.math.vectors import LorentzVector

d
			
def generate(nEvents):
	
	pythia = pythia8.Pythia()

	pythia.readString("Top:all = on")
#	pythia.readString("PhaseSpace:pTHatMin = 20")
	pythia.readString("TimeShower:pTmaxMatch = 0") #Kinematic limit
	pythia.readString("SpaceShower:pTmaxMatch = 0") #Kinematic limit
	pythia.readString("SpaceShower:pTdampMatch = 1") #Apply damping
	pythia.readString("TimeShower:pTdampMatch = 1") #Apply damping
	pythia.readString("SpaceShower:rapidityOrder = off") #pT ordering!
	pythia.readString("SpaceShower:phiIntAsym = off") #Pythia asymmetric showering bug
	pythia.readString("ParticleDecays:allowPhotonRadiation = on")
	pythia.readString("Random:setSeed = on")
	pythia.readString("Random:seed = 0")
	pythia.init()
		
	############################################ Branches for TTree ############################################
	
	
	
	f = ROOT.TFile( 'ttbar_emu.root', 'RECREATE' )
	tree = ROOT.TTree( 'DecayTree', 'Just A Tree')
		
	branches_to_create = "mu_plus_P, mu_plus_PX, mu_plus_PY, mu_plus_PZ, mu_plus_PE, mu_plus_PT, mu_plus_ORIGIN_X, mu_plus_ORIGIN_Y, mu_plus_ORIGIN_Z, mu_plus_ETA, mu_plus_theta, mu_plus_Q".split(", ")
	
	branches_to_create += "e_minus_P, e_minus_PX, e_minus_PY, e_minus_PZ, e_minus_PE, e_minus_PT, e_minus_ORIGIN_X, e_minus_ORIGIN_Y, e_minus_ORIGIN_Z, e_minus_ETA, e_minus_theta, e_minus_Q".split(", ")
	
	branches_to_create += ["emu_M", "DeltaR", "eventnumber", "mu_mother_ID", "e_mother_ID", "mu_plus_from", "e_minus_from"]
	
	branches = {}
	
	for b in branches_to_create:
		branches[b] = np.zeros(1, dtype=np.float64)
		tree.Branch( b, branches[b], str(b)+"/D" )
	
	############################################################################################################
	
	n = 0

	while n < nEvents:
		
		if not pythia.next(): continue
		
		### store muons, electrons
		muons = []
		electrons = []
		for prt in pythia.event:
			if prt.idAbs() == 13:
				muons.append(prt)
			elif prt.idAbs() == 11:
				electrons.append(prt)
						
		candidates = get_candidate(pythia, muons, electrons)
		
		if candidates == None:
			continue
			
#		print("muons: ", len(candidates[0]))
#		print("electrons: ", len(candidates[1]), "\n")
		
		if len(candidates[0]) > 1:
			print("Multiple Candidates")
			
		muons = candidates[0]
		electrons = candidates[1]
		
		for m in muons:
			for e in electrons:
				
				b    = pythia.event[5]
				bbar = pythia.event[6]
				
				b_daughters     = b.daughterListRecursive()
				bbar_daughters = bbar.daughterListRecursive()
							
				branches["eventnumber"][0] = n
								
				branches["mu_plus_P"][0] = m.p().pAbs()
				branches["mu_plus_PX"][0] = m.p().px()
				branches["mu_plus_PY"][0] = m.p().py()
				branches["mu_plus_PZ"][0] = m.p().pz()
				branches["mu_plus_PE"][0] = m.p().e()
				branches["mu_plus_PT"][0] = m.p().pT()
				branches["mu_plus_ORIGIN_X"][0] = m.xProd()
				branches["mu_plus_ORIGIN_Y"][0] = m.yProd()
				branches["mu_plus_ORIGIN_Z"][0] = m.zProd()
				branches["mu_plus_ETA"][0] = m.eta()
				branches["mu_plus_theta"][0] = m.theta()
				branches["mu_plus_Q"][0] = m.charge()
				
				mu_mother = pythia.event[m.mother1()]
				branches["mu_mother_ID"][0] = mu_mother.id()
				
				if m.index() in b_daughters:
					branches["mu_plus_from"][0] = 1
				elif m.index() in bbar_daughters:
					branches["mu_plus_from"][0] = -1
				else:
					branches["mu_plus_from"][0] = 0
						
				branches["e_minus_P"][0] = e.p().pAbs()
				branches["e_minus_PX"][0] = e.p().px()
				branches["e_minus_PY"][0] = e.p().py()
				branches["e_minus_PZ"][0] = e.p().pz()
				branches["e_minus_PE"][0] = e.p().e()
				branches["e_minus_PT"][0] = e.p().pT()
				branches["e_minus_ORIGIN_X"][0] = e.xProd()
				branches["e_minus_ORIGIN_Y"][0] = e.yProd()
				branches["e_minus_ORIGIN_Z"][0] = e.zProd()
				branches["e_minus_ETA"][0] = e.eta()
				branches["e_minus_theta"][0] = e.theta()
				branches["e_minus_Q"][0] = e.charge()
				
				e_mother = pythia.event[e.mother1()]
				branches["e_mother_ID"][0] = e_mother.id()
				
				if e.index() in b_daughters:
					branches["e_minus_from"][0] = 1
				elif e.index() in bbar_daughters:
					branches["e_minus_from"][0] = -1
				else:
					branches["e_minus_from"][0] = 0
						
				p4mu = LorentzVector()
				p4mu.setpxpypze(m.p().px(), m.p().py(), m.p().pz(), m.p().e())
				
				p4e = LorentzVector()
				p4e. setpxpypze(e.p().px(), e.p().py(), e.p().pz(), e.p().e())
				
				p4emu = p4e + p4mu
				
				branches["emu_M"][0] = p4emu.m
				
				branches["DeltaR"][0] = p4e.deltar(p4mu)
			
		n += 1
		print_accepted_events(n,nEvents/100)
		
		tree.Fill()
	
	pythia.stat()
	f.Write()
	f.Close()

			
if __name__=='__main__':
	
	generate(2000)
			
		

