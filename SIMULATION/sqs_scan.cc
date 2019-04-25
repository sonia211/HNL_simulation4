// File: tree.cc
// This is a simple test program.
// Modified by Rene Brun and Axcel Naumann to put the Pythia::event 
// into a TTree.
// Copyright (C) 2013 Torbjorn Sjostrand

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
using namespace Pythia8;

int main() {

	// Create Pythia instance and set it up to generate hard QCD processes
	// above pTHat = 20 GeV for pp collisions at 14 TeV.
  
	
	double sqs_min(600.), sqs_max(14000.);
	double sqs;
	int N(25);
	double sqs_step = (sqs_max-sqs_min)/N;
	cout << "sqs_step:"<< sqs_step << endl;
	
	
	// Set up the ROOT TFile and TTree.
	//TFile *file = TFile::Open("./output/sqsScan.root","recreate");
	//Event *event = &pythia.event;
	TCanvas *cN_tau = new TCanvas("cNtau","cNtau",800,600);
	TCanvas *cN_PT = new TCanvas("cN_PT","cNtau",800,600);

	
	TTree *T = new TTree("TsqsScan","mytree");
	TH2D *hscan_N_PT = new TH2D("hscan_N_PT", "hscan_N_PT", N+1, sqs_min, sqs_max, 60, 0., 30.);
	TH2D *hscan_N_tau = new TH2D("hscan_N_tau", "hscan_N_tau", N+1, sqs_min, sqs_max,40, 0., 20.);
	//TH2D *hscan_N_PT= new TH2D("hscan_N_PT", "hscan_N_PT", 300, -100., 100.);
	
	
	double N_PX(0), 	N_PY(0),	N_PZ(0), N_PT(0), N_E(0);
	double N_M(0),	N_MT(0),	N_tau(0);
	Double_t N_Xp(0),	N_Yp(0),	N_Zp(0),  	N_Tp(0), N_Vp(0);
	Double_t N_Xd(0),	N_Yd(0),	N_Zd(0),  	N_Td(0), N_Vd(0);
	Double_t N_Xdiff(0),	N_Ydiff(0),	N_Zdiff(0),  	N_Tdiff(0);
	Double_t N_POL(0),	N_SCALE(0);
	
	
	/*  
	TBranch *b_sqs = Tmo->Branch("sqs",&sqs, "sqs/D");
	
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
	*/

	
	
	for (int n(0); n<=N; ++n){
		
		sqs=sqs_min+n*sqs_step;
		//sqs=2000.;
		
		Pythia pythia;
		// Shorthand for the event record in pythia. LHC settings.
		Event& event = pythia.event;
		ParticleData& particleData = pythia.particleData;
		pythia.readString("Beams:eCM="+std::to_string(sqs));
	  
		// Extract settings to be used in the main program.
		//int nEvent = pythia.mode("Main:numberOfEvents");
		
		int nEvent = 5000;
		int nAbort = pythia.mode("Main:timesAllowErrors");
	  
		//DecayHandler* chainDecayPtr( vector<int>& idProd, vector<int>& motherProd, vector<double>& mProd, vector<Vec4>& pProd, int iDec, const Event& event)  
		//std::vector<int> particles;
		//pythia.setDecayPtr( chainDecayPtr, particles); 
		pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/HNLprop.cmnd");
	  
	  
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
		pythia.init(); 					//take its values from the beam specification stored in the Settings database

	  

		// Interesting amounts
		Double_t mu_P2(0),  mu_PX(0), mu_PY(0), mu_PZ(0), mu_PT(0), mu_E(0);
		Double_t mu_M(0),	mu_tau(0);
		Double_t mu_Xp(0),  mu_Yp(0),  mu_Zp(0),  mu_Tp(0), mu_Vp(0);
		Double_t mu_Xd(0),  mu_Yd(0),  mu_Zd(0),  mu_Td(0), mu_Vd(0);
	  
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
				
				
				if (idAbs==14 and status < 0){ // decaying HNL
					
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
					
					hscan_N_PT->Fill(sqs,N_PT);
					hscan_N_tau->Fill(sqs,N_PT);
			
				}// id 14 and status negative
				//Tmo->Fill();
			}//loop on event (i)

		}// loop on events
	
	}// loop on sqs
	
	cN_tau->cd();
	hscan_N_tau->Draw("colz");
	 hscan_N_tau->Write();
	cN_tau->SaveAs("./output/scan_sqs_Ntau.root");
	
	cN_PT->cd();
	hscan_N_PT->Draw("colz"); hscan_N_PT->Write();
	cN_PT->SaveAs("./output/scan_sqs_NPT.root");
	
	delete cN_tau; delete cN_PT;
	return 0;
}

