// File: tree.cc
// This is a simple test program.
// Modified by Rene Brun and Axcel Naumann to put the Pythia::event 
// into a TTree.
// Copyright (C) 2013 Torbjorn Sjostrand

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
#include "ReadablePart.cc"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"

using namespace Pythia8;

int main() {

	// Create Pythia instance and set it up to generate hard QCD processes
	// above pTHat = 20 GeV for pp collisions at 14 TeV.
  
	/*
	double sqs_min(400), sqs_max(8000.);
	int N(2);
	double sqs_step(sqs_max-sqs_min)/N;
	*/
	
	//for (int n(0); n<
	Pythia pythia;
  
	// Shorthand for the event record in pythia. LHC settings.
	Event& event = pythia.event;
	ParticleData& particleData = pythia.particleData;
	
	
	
	
	pythia.readString("Beams:eCM =14000.");
  
	// Extract settings to be used in the main program.
	//int nEvent = pythia.mode("Main:numberOfEvents");
	
	int nEvent = 2000;
	int nAbort = pythia.mode("Main:timesAllowErrors");
  
	//DecayHandler* chainDecayPtr( vector<int>& idProd, vector<int>& motherProd, vector<double>& mProd, vector<Vec4>& pProd, int iDec, const Event& event)  
	//std::vector<int> particles;
	//pythia.setDecayPtr( chainDecayPtr, particles); 
	pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/HNLprop_C.cmnd");
  
  
	/***  Processes selection  ***/
	pythia.readString("HardQCD:all = on");
	pythia.readString("HardQCD:hardbbbar=on");
	pythia.readString("WeakSingleBoson:all=on");
	pythia.readString("WeakSingleBoson:ffbar2W = on");
  
 
	pythia.readString("WeakBosonExchange:all=on");
	pythia.readString("WeakBosonAndParton:all=on");
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	
	pythia.readString("LeftRightSymmmetry:all=on");
  
	//pythia.readString("TwoFermions2W2TwoFermion=on");
	pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");
	//pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	

	// Conditions on daughters  
	pythia.readString("PhaseSpace:pTHatMin = 20.");
  
	// Initialisation
	// pythia.readString("Init:showAllParticleData=on");
	pythia.readString("Next:numberShowEvent=10");
	//double tau0max = 
	

	pythia.init(); 					//take its values from the beam specification stored in the Settings database

  

	// Interesting amounts
	
	Double_t B_P2(0),  B_PX(0), B_PY(0), B_PZ(0), B_PT(0), B_E(0);
	Double_t B_M(0),	B_tau(0);
	Double_t B_Xp(0),  B_Yp(0),  B_Zp(0),  B_Tp(0), B_Vp(0);
	Double_t B_Xd(0),  B_Yd(0),  B_Zd(0),  B_Td(0), B_Vd(0);
	
	Double_t mu1_P2(0),  mu1_PX(0), mu1_PY(0), mu1_PZ(0), mu1_PT(0), mu1_E(0);
	Double_t mu1_M(0),	mu1_tau(0);
	Double_t mu1_Xp(0),  mu1_Yp(0),  mu1_Zp(0),  mu1_Tp(0), mu1_Vp(0);
	Double_t mu1_Xd(0),  mu1_Yd(0),  mu1_Zd(0),  mu1_Td(0), mu1_Vd(0);
	
	Double_t mu2_P2(0),  mu2_PX(0), mu2_PY(0), mu2_PZ(0), mu2_PT(0), mu2_E(0);
	Double_t mu2_M(0),	mu2_tau(0);
	Double_t mu2_Xp(0),  mu2_Yp(0),  mu2_Zp(0),  mu2_Tp(0), mu2_Vp(0);
	Double_t mu2_Xd(0),  mu2_Yd(0),  mu2_Zd(0),  mu2_Td(0), mu2_Vd(0);
  
	Double_t pi_P2(0),  pi_PX(0), pi_PY(0), pi_PZ(0), pi_PT(0), pi_E(0);
	Double_t pi_M(0),	pi_tau(0);
	Double_t pi_Xp(0),  pi_Yp(0),  pi_Zp(0),  pi_Tp(0), pi_Vp(0);
	Double_t pi_Xd(0),  pi_Yd(0),  pi_Zd(0),  pi_Td(0), pi_Vd(0);
  
	Double_t N_P2(0),	N_PX(0), 	N_PY(0),	N_PZ(0), N_PT(0), N_E(0);
	Double_t N_M(0),	N_MT(0),	N_tau(0);
	Double_t N_Xp(0),	N_Yp(0),	N_Zp(0),  	N_Tp(0), N_Vp(0);
	Double_t N_Xd(0),	N_Yd(0),	N_Zd(0),  	N_Td(0), N_Vd(0);
	Double_t N_Xdiff(0),	N_Ydiff(0),	N_Zdiff(0),  	N_Tdiff(0);
	Double_t N_POL(0),	N_SCALE(0);
	
	Double_t nNP(0), nND(0), rN(0);
	
  
	

	/** Set up the ROOT TFile and TTree, TBranch.  **/
	TFile *file = TFile::Open("./pytree.root","recreate");
	//Event *event = &pythia.event;
	TTree *Tmo = new TTree("Tmother","mytree");
	TTree *Tda = new TTree("Tdaughters","mytree");
  
	//T->Branch("event",&event);
	//TBranch b_mu2_P2("mu2_P2",&mu2_P2);
	
	
	TBranch *b_B_PX = Tda->Branch("B_PX",&B_PX, "B_PX/D");
	TBranch *b_B_PY = Tda->Branch("B_PY",&B_PY, "B_PY/D");
	TBranch *b_B_PZ = Tda->Branch("B_PZ",&B_PZ, "B_PZ/D");
	TBranch *b_B_PT = Tda->Branch("B_PT",&B_PT, "B_PT/D");
	TBranch *b_B_E  = Tda->Branch("B_E",&B_E,   "B_E/D");
	TBranch *b_B_M= Tda->Branch("B_M",&B_M, "B_M/D");
	
	TBranch *b_B_tau= Tda->Branch("B_tau",&B_tau, "B_tau/D");
	TBranch *b_B_Xp = Tda->Branch("B_Xp",&B_Xp, "B_Xp/D");
	TBranch *b_B_Yp = Tda->Branch("B_Yp",&B_Yp, "B_Yp/D");
	TBranch *b_B_Zp = Tda->Branch("B_Zp",&B_Zp, "B_Zp/D");
	TBranch *b_B_Tp = Tda->Branch("B_Tp",&B_Tp, "B_Tp/D");

	TBranch *b_B_Xd = Tda->Branch("B_Xd",&B_Xd, "B_Xd/D");
	TBranch *b_B_Yd = Tda->Branch("B_Yd",&B_Yd, "B_Yd/D");
	TBranch *b_B_Zd = Tda->Branch("B_Zd",&B_Zd, "B_Zd/D");
	TBranch *b_B_Td = Tda->Branch("B_Td",&B_Td, "B_Td s/D");
	
	
	
	TBranch *b_mu1_PX = Tda->Branch("mu1_PX",&mu1_PX, "mu1_PX/D");
	TBranch *b_mu1_PY = Tda->Branch("mu1_PY",&mu1_PY, "mu1_PY/D");
	TBranch *b_mu1_PZ = Tda->Branch("mu1_PZ",&mu1_PZ, "mu1_PZ/D");
	TBranch *b_mu1_PT = Tda->Branch("mu1_PT",&mu1_PT, "mu1_PT/D");
	TBranch *b_mu1_E  = Tda->Branch("mu1_E",&mu1_E,   "mu1_E/D");
	TBranch *b_mu1_M= Tda->Branch("mu1_M",&mu1_M, "mu1_M/D");
	
	TBranch *b_mu1_tau= Tda->Branch("mu1_tau",&mu1_tau, "mu1_tau/D");
	TBranch *b_mu1_Xp = Tda->Branch("mu1_Xp",&mu1_Xp, "mu1_Xp/D");
	TBranch *b_mu1_Yp = Tda->Branch("mu1_Yp",&mu1_Yp, "mu1_Yp/D");
	TBranch *b_mu1_Zp = Tda->Branch("mu1_Zp",&mu1_Zp, "mu1_Zp/D");
	TBranch *b_mu1_Tp = Tda->Branch("mu1_Tp",&mu1_Tp, "mu1_Tp/D");

	TBranch *b_mu1_Xd = Tda->Branch("mu1_Xd",&mu1_Xd, "mu1_Xd/D");
	TBranch *b_mu1_Yd = Tda->Branch("mu1_Yd",&mu1_Yd, "mu1_Yd/D");
	TBranch *b_mu1_Zd = Tda->Branch("mu1_Zd",&mu1_Zd, "mu1_Zd/D");
	TBranch *b_mu1_Td = Tda->Branch("mu1_Td",&mu1_Td, "mu1_Td s/D");
	
	
	
	TBranch *b_mu2_PX = Tda->Branch("mu2_PX",&mu2_PX, "mu2_PX/D");
	TBranch *b_mu2_PY = Tda->Branch("mu2_PY",&mu2_PY, "mu2_PY/D");
	TBranch *b_mu2_PZ = Tda->Branch("mu2_PZ",&mu2_PZ, "mu2_PZ/D");
	TBranch *b_mu2_PT = Tda->Branch("mu2_PT",&mu2_PT, "mu2_PT/D");
	TBranch *b_mu2_E  = Tda->Branch("mu2_E",&mu2_E,   "mu2_E/D");
	TBranch *b_mu2_M= Tda->Branch("mu2_M",&mu2_M, "mu2_M/D");

	TBranch *b_mu2_tau= Tda->Branch("mu2_tau",&mu2_tau, "mu2_tau/D");
	TBranch *b_mu2_Xp = Tda->Branch("mu2_Xp",&mu2_Xp, "mu2_Xp/D");
	TBranch *b_mu2_Yp = Tda->Branch("mu2_Yp",&mu2_Yp, "mu2_Yp/D");
	TBranch *b_mu2_Zp = Tda->Branch("mu2_Zp",&mu2_Zp, "mu2_Zp/D");
	TBranch *b_mu2_Tp = Tda->Branch("mu2_Tp",&mu2_Tp, "mu2_Tp/D");

	TBranch *b_mu2_Xd = Tda->Branch("mu2_Xd",&mu2_Xd, "mu2_Xd/D");
	TBranch *b_mu2_Yd = Tda->Branch("mu2_Yd",&mu2_Yd, "mu2_Yd/D");
	TBranch *b_mu2_Zd = Tda->Branch("mu2_Zd",&mu2_Zd, "mu2_Zd/D");
	TBranch *b_mu2_Td = Tda->Branch("mu2_Td",&mu2_Td, "mu2_Td s/D");


	//pi
	TBranch *b_pi_PX = Tda->Branch("pi_PX",&pi_PX, "pi_PX/D");
	TBranch *b_pi_PY = Tda->Branch("pi_PY",&pi_PY, "pi_PY/D");
	TBranch *b_pi_PZ = Tda->Branch("pi_PZ",&pi_PZ, "pi_PZ/D");
	TBranch *b_pi_PT = Tda->Branch("pi_PT",&pi_PT, "pi_PT/D");
	TBranch *b_pi_E= Tda->Branch("pi_E",&pi_E, "pi_E/D");
	TBranch *b_pi_M= Tda->Branch("pi_M",&pi_M, "pi_M/D");

	TBranch *b_pi_tau= Tda->Branch("pi_tau",&pi_tau, "pi_tau/D");
	TBranch *b_pi_Xp = Tda->Branch("pi_Xp",&pi_Xp, "pi_Xp/D");
	TBranch *b_pi_Yp = Tda->Branch("pi_Yp",&pi_Yp, "pi_Yp/D");
	TBranch *b_pi_Zp = Tda->Branch("pi_Zp",&pi_Zp, "pi_Zp/D");
	TBranch *b_pi_Tp = Tda->Branch("pi_Tp",&pi_Tp, "pi_Tp/D");

	TBranch *b_pi_Xd = Tda->Branch("pi_Xd",&pi_Xd, "pi_Xd/D");
	TBranch *b_pi_Yd = Tda->Branch("pi_Yd",&pi_Yd, "pi_Yd/D");
	TBranch *b_pi_Zd = Tda->Branch("pi_Zd",&pi_Zd, "pi_Zd/D");
	TBranch *b_pi_Td = Tda->Branch("pi_Td",&pi_Td, "pi_Td s/D");

	//Branch b_N_P2("N_P2",&N_P2);
	TBranch *b_N_PX = Tmo->Branch("N_PX",&N_PX, "N_PX/D");
	TBranch *b_N_PY = Tmo->Branch("N_PY",&N_PY, "N_PY/D");
	TBranch *b_N_PZ = Tmo->Branch("N_PZ",&N_PZ, "N_PZ/D");
	TBranch *b_N_PT = Tmo->Branch("N_PT",&N_PT, "N_PT/D");
	TBranch *b_N_E= Tmo->Branch("N_E",&N_E, "N_E/D");
	TBranch *b_N_M= Tmo->Branch("N_M",&N_M, "N_M/D");
	TBranch *b_N_MT= Tmo->Branch("N_MT",&N_MT, "N_MT/D");
	TBranch *b_N_POL= Tmo->Branch("N_POL",&N_POL, "N_POL/D");
	TBranch *b_N_SCALE= Tmo->Branch("N_SCALE",&N_SCALE, "N_SCALE/D");

	TBranch *b_N_tau= Tmo->Branch("N_tau",&N_tau, "N_tau/D");
	TBranch *b_N_Xp = Tmo->Branch("N_Xp",&N_Xp, "N_Xp/D");
	TBranch *b_N_Yp = Tmo->Branch("N_Yp",&N_Yp, "N_Yp/D");
	TBranch *b_N_Zp = Tmo->Branch("N_Zp",&N_Zp, "N_Zp/D");
	TBranch *b_N_Tp = Tmo->Branch("N_Tp",&N_Tp, "N_Tp/D");

	TBranch *b_N_Xd = Tmo->Branch("N_Xd",&N_Xd, "N_Xd/D");
	TBranch *b_N_Yd = Tmo->Branch("N_Yd",&N_Yd, "N_Yd/D");
	TBranch *b_N_Zd = Tmo->Branch("N_Zd",&N_Zd, "N_Zd/D");
	TBranch *b_N_Td = Tmo->Branch("N_Td",&N_Td, "N_Td s/D");
 
	TBranch *b_N_Xdiff = Tmo->Branch("N_Xdiff",&N_Xd, "N_Xdiff/D");
	TBranch *b_N_Ydiff = Tmo->Branch("N_Ydiff",&N_Yd, "N_Ydiff/D");
	TBranch *b_N_Zdiff = Tmo->Branch("N_Zdiff",&N_Zd, "N_Zdiff/D");
	TBranch *b_N_Tdiff = Tmo->Branch("N_Tdiff",&N_Td, "N_Tdiff/D");
	
	TBranch *b_nNP = Tmo->Branch("nNP",&nNP, "nNP/D");
	TBranch *b_nND = Tmo->Branch("nND",&nND, "nND/D");
	TBranch *b_rN = Tmo->Branch("rN",&rN, "rN/D");
	
	
	
 
  
	int iAbort = 0;
	int d1, d2;
	int cnt=0;
	std::vector<int> daughters{};

	
	for (int iEvent = 0; iEvent < nEvent; ++iEvent) {

		//Generate events. Quit if many failures.
		// Generate events. Quit if many failures.
		if (!pythia.next()) {
			if (++iAbort < nAbort) continue;
			cout << " Event generation aborted prematurely, owing to error!\n";
			break;
		}
		// Loop over all particles and analyze the final-state ones.
		for (int i = 0; i < pythia.event.size(); ++i){
			//if (pythia.event[i].isFinal()) {
			int idAbs = pythia.event[i].idAbs(); int status = pythia.event[i].status();
			
			/*
			if ((idAbs==511 or idAbs==521) and status > 0) cout << "Produced B0 or B+-, EVENT: "<<iEvent<<"   nlist:" << i << endl;
			if ((idAbs==511 or idAbs==521) and status < 0) cout << "Decaying B0 or B+-, EVENT: "<<iEvent<<"   nlist:" << i << endl;
			
			if ((idAbs==411 or idAbs==421) and status > 0) cout << "Produced D0 or D+-, EVENT: "<<iEvent<<"   nlist:" << i << endl;
			if ((idAbs==411 or idAbs==421) and status < 0) cout << "Decaying D0 or D+-, EVENT: "<<iEvent<<"   nlist:" << i << endl;
			
			if ((idAbs==24 or idAbs==23) and status > 0) cout << "Produced Z or W+-, i:" << i << endl;
			if ((idAbs==24 or idAbs==23) and status < 0) cout << "Decaying Z or W+-, i:" << i << endl;
			
			if ((idAbs==25) and status > 0) cout << "Produced Higgs, i:" << i << endl;
			if ((idAbs==25) and status < 0) cout << "Decaying Higgs, i:" << i << endl;
			
			if ((idAbs==111 or idAbs==211) and status > 0) cout << "Produced pi0 or pi+-, i:" << i << endl;
			if ((idAbs==111 or idAbs==211) and status < 0) cout << "Decaying pi0 or pi+-, i:" << i << endl;
			
			if ((idAbs==13) and status > 0) cout << "Produced mu-+, i:" << i << endl;
			if ((idAbs==13) and status < 0) cout << "Decaying mu-+, i:" << i << endl;
			
			if ((idAbs==11) and status > 0) cout << "Produced e-+, i:" << i << endl;
			if ((idAbs==11) and status < 0) cout << "Decaying e-+, i:" << i << endl;
			*/
			
		
			
			if (idAbs==15 and status < 0){ // decaying HNL
				
			
				// Interestinf quantities
				double EI = pythia.event[i].e();
				double MI = pythia.event[i].m();
				double MTI = pythia.event[i].mT();
				//double P2I = pythia.event[i].p2(
				double PXI = pythia.event[i].px();
				double PYI = pythia.event[i].py();
				double PZI = pythia.event[i].pz();
				double PTI = pythia.event[i].pT();
				double TAUI = pythia.event[i].tau();
			  
				double XpI = pythia.event[i].xProd();
				double YpI = pythia.event[i].yProd();
				double ZpI = pythia.event[i].zProd();
				double TpI = pythia.event[i].tProd();
				
				double XdI = pythia.event[i].xDec();
				double YdI = pythia.event[i].yDec();
				double ZdI = pythia.event[i].zDec();
				double TdI = pythia.event[i].tDec();
				
				double POLI = pythia.event[i].pol();
				double SCALEI = pythia.event[i].scale();
				
				
				// Branch filling
				N_E=EI; 	//N_P2=P2I; 	
				N_M=MI; 	//N_P2=P2I; 	
				N_PT=PTI;
				N_PX=PXI; 	N_PY=PYI; 	N_PZ=PZI;
				
				N_tau=TAUI; 
				N_Xp=XpI; 	N_Yp=YpI; 	N_Zp=ZpI;	N_Tp=TpI;
				N_Xd=XdI; 	N_Yd=YdI; 	N_Zd=ZdI;	N_Td=TdI;
				
				N_Xdiff=XdI-XpI; 	N_Ydiff=YdI-YpI; 	N_Zdiff=ZdI-ZpI;	N_Tdiff=TdI-TpI;
				
				N_POL=POLI; N_SCALE=SCALEI;
				// Daughters filling 
				
				d1=pythia.event[i].daughter1(); 
				d2=pythia.event[i].daughter2();

		
			}// id 1 and status negative
			
			Tmo->Fill();
		}//loop on event (i)
		
		
		if(d1>0 and d2>0 and d1<d2){
			//cout<<"daughter 1: " << d1 << "  daughter2: " << d2 << endl; 
			daughters.push_back(d1);
			daughters.push_back(d2);
			
		}
		//} //is final
		
		
		//Daughters
		if(daughters.size()==0 and cnt==0){cout << "size 0!" << endl; cnt++;}
		else if(daughters.size()>0 and cnt==0){cout << "size non0!" << endl; cnt++;}
		for (int j=0; j < daughters.size(); ++j) {
			int d=daughters[j];
			//cout << "j: "<< j<<endl;
			//cout << "d: "<< d<<endl;
			int idAbs = pythia.event[d].idAbs();
			double EI = pythia.event[d].e();
			double MI = pythia.event[d].m();
			//double P2I = pythia.event[d].p2(
			double PXI = pythia.event[d].px();
			double PYI = pythia.event[d].py();
			double PZI = pythia.event[d].pz();
			double PTI = pythia.event[d].pT();
			double TAUI = pythia.event[d].tau();
				  
			double XpI = pythia.event[d].xProd();
			double YpI = pythia.event[d].yProd();
			double ZpI = pythia.event[d].zProd();
			double TpI = pythia.event[d].tProd();
					
			double XdI = pythia.event[d].xDec();
			double YdI = pythia.event[d].yDec();
			double ZdI = pythia.event[d].zDec();
			double TdI = pythia.event[d].tDec();
			
			if(idAbs == 211){
				pi_E=EI; 	//pi_P2=P2I; 	
				pi_M=MI; 	//pi_P2=P2I; 	
				pi_PT=PTI;
				pi_PX=PXI; 	pi_PY=PYI; 	pi_PZ=PZI;
			
				pi_tau=TAUI; 
				pi_Xp=XpI; 	pi_Yp=YpI; 	pi_Zp=ZpI;	pi_Tp=TpI;
				pi_Xd=XdI; 	pi_Yd=YdI; 	pi_Zd=ZdI;	pi_Td=TdI;
		  }
			else if(idAbs == 13){
				mu2_E=EI; 	//mu2_P2=P2I; 	
				mu2_M=MI; 	//mu2_P2=P2I; 	
				mu2_PT=PTI;
				mu2_PX=PXI; 	mu2_PY=PYI; 	mu2_PZ=PZI;
			
				mu2_tau=TAUI; 
				mu2_Xp=XpI; 	mu2_Yp=YpI; 	mu2_Zp=ZpI;	mu2_Tp=TpI;
				mu2_Xd=XdI; 	mu2_Yd=YdI; 	mu2_Zd=ZdI;	mu2_Td=TdI;
			}
			
			
		
		Tda->Fill();
		}  	
	}//loop on all events
	
	// Statistics on event generation.
	pythia.stat();

	//  Write tree.
	Tda->Print(); Tmo->Print();
	Tda->Write(); Tmo->Write();
	delete Tmo; delete Tda;
	delete file;

	// Done.
	return 0;
}
