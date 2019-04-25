// File: tree.cc
// This is a simple test program.
// Modified by Rene Brun and Axcel Naumann to put the Pythia::event 
// into a TTree.
// Copyright (C) 2013 Torbjorn Sjostrand

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
//#include "ReadablePart.cc"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TPad.h"
#include "TAxis.h"
#include "TMath.h"
#include <algorithm>
using namespace Pythia8;



//int HNL_id = 15;
//int HNL_id = 25;

int main() {

	int HNL_id;
	cout << "HNL id (15,25): ";
	cin >> HNL_id;
	
	int tauMode=88;
	TString tauMode_s;
	string tauMode_s2;
	if(HNL_id==15){
		cout << "tauMode :  ";
		cin >> tauMode;
		tauMode_s = std::to_string(tauMode);
		tauMode_s2 = std::to_string(tauMode);
	}
	
	TString HNL_id_s = std::to_string(HNL_id);
	string HNL_id_s2 = std::to_string(HNL_id);
	
	int nEvent;
	cout << "nEvent :  ";
	cin >> nEvent;
	
	bool scanflag;
	cout << "Scan flag: ";
	cin >> scanflag;
	
	bool cBflag;
	cout << "Charged B ? :  ";
	cin >> cBflag;
	TString cBflag_s = std::to_string(cBflag);
	string cBflag_s2 = std::to_string(cBflag);
	
	
	bool no3mesonflag;
	if(cBflag){
		cout << "Switch off 3rd meson? :  ";
		cin >> no3mesonflag;
	}
	else no3mesonflag=0;
	TString no3mesonflag_s = std::to_string(no3mesonflag);
	
	
		/** GENERAL PARAMETERS **/
	//int nEvent = 200;
	
	// Values of the scan
	vector<double> tau0vec; 	
	vector<double> mNvec; 
	
	if (!scanflag){
			tau0vec = {0.01}; 	// in ps, logarithmique
			mNvec = {2.0};  // in GeV, linear
	}
	else {
		tau0vec = {1., 2., 5., 10., 20., 50., 100.}; 	// in ps, logarithmique
		mNvec = {0.244,0.5, 1., 1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 5.5, 6.0};  // in GeV, linear
	}
	
	//vector<Double_t> mNvec = {2.0};
	//vector<Double_t> tau0vec = {10.};
	vector<Double_t> tau0powervec = {0., 3.};
	
	// Histograms / TGraph to fill
	
	TCanvas *cnNP = new TCanvas("cnNP","cnNP",800,600);
	TCanvas *cnND = new TCanvas("cnND","cnND",800,600);
	
	TCanvas *cnBP = new TCanvas("cnBP","cnBP",800,600);
	
	TCanvas *crN1 = new TCanvas("crN1","crN1",800,600);
	TCanvas *crN2 = new TCanvas("crN2","crN2",800,600);
	TCanvas *crN1f = new TCanvas("crN1f","crN1f",800,600);
	TCanvas *crN2f = new TCanvas("crN2f","crN2f",800,600);
	

	TH2D *hscan_nNP = new TH2D("hscan_nNP", "hscan_nNP", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	TH2D *hscan_nND1 = new TH2D("hscan_nND1", "hscan_nND1", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	
	TH1D *hscan_nBP = new TH1D("nNB", "Produced B-mesons (scaled)", 50, 510., 544.);
	
	TGraph2D *g1 = new TGraph2D();
	TGraph2D *g2 = new TGraph2D();
	TGraph2D *g1f = new TGraph2D();
	TGraph2D *g2f = new TGraph2D();
	
	// Projections
	TGraph *g1fprojx = new TGraph();
	TGraph *g1fprojy = new TGraph();
	
	TGraph *g2fprojx = new TGraph();
	TGraph *g2fprojy = new TGraph();
	
	
	
	// Tools variables 
	int nNP(0), nND1(0), nND2(0);
	double rN1(0.), rN2(0.);
	Double_t mN(0.);
	Double_t tau0(0.);
	int cnt(0);
	
	
	// List of B mesons
	//vector<int> Bids={	511, 521, 10511, 10521, 513, 
	//					523, 10513, 10523, 20513, 20523,
	//					515, 525, 531, 10531, 533, 10533,
	//					20533, 535, 541, 10541, 543, 10543,
	//					20543, 545};
	vector<TString> Bids={	"B^{0}", "B^{+} / B^{-}", "B_{s}", "B_{c}" }; 
	
	
	
	// Create Pythia instance and set it up to generate hard QCD processes
	// above pTHat = 20 GeV for pp collisions at 14 TeV.
  
	/*
	double sqs_min(400), sqs_max(8000.);
	int N(2);
	double sqs_step(sqs_max-sqs_min)/N;
	*/
	
	for (int a(0); a<mNvec.size(); ++a){ // loop on masses
		mN=mNvec[a];
		
		cout << "mN: " << mN << endl;
		
		for (int b(0); b<tau0vec.size(); ++b){ // loop on lifetimes
			tau0=tau0vec[b];
	
	//for (int n(0); n<
			Pythia pythia;
		  
			// Shorthand for the event record in pythia. LHC settings.
			Event& event = pythia.event;
			ParticleData& particleData = pythia.particleData;
			
			
			
			
			pythia.readString("Beams:eCM =14000.");
			pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm)=on");
			pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gmZ)=on");
			pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");
		  
			// Extract settings to be used in the main program.
			//int nEvent = pythia.mode("Main:numberOfEvents");
			
			int nAbort = pythia.mode("Main:timesAllowErrors");
			
			
			// HNL properties
			if(HNL_id == 15){
				cout << "std::to_string(mN) " << std::to_string(mN) << endl;
				cout << "std::to_string(3e-01*tau0)" << std::to_string(3e-01*tau0) << endl;
				//string HNLstr = "15:new= nu_Rmu nu_Rmu 2 0 0 2. 0. 0. 0. 8.0e-03";
				//pythia.readString("ParticleDecays:sophisticatedTau=2");
			//	pythia.readString("15:sophisticatedTau=2");
				//pythia.readString("15:tauPolarization=-1");
				pythia.readString("TauDecays:tauPolarization=1.");
				//pythia.readString("15:pol=-1");
				pythia.readString("TauDecays:mode="+tauMode_s2);
				//pythia.readString("15:mode="+tauMode_s2);
				string HNLstr = "15:new = nu_Rmu nu_Rmu 2 0 0 "+std::to_string(mN)+" 0. 0. 0. "+std::to_string(3e-01*tau0);
				pythia.readString(HNLstr);
				pythia.readString("15:mayDecay=on");
				pythia.readString("15:oneChannel= 1 1. 1521 -13 -211");
				
				pythia.readString("24:oneChannel = 1 1. 23 -13 15");
				pythia.readString("24:addChannel = 1 1. 23 1 -2");
				
			}
			if(HNL_id == 25){
				string HNLstr = "25:new = nu_Rmu nu_Rmu 1 0 0 "+std::to_string(mN)+" 0. 0. 0. "+std::to_string(3e-01*tau0);
				pythia.readString(HNLstr);
				pythia.readString("25:mayDecay=on");
				pythia.readString("25:oneChannel 1 1. 1 -13 -211");
				
				pythia.readString("24:oneChannel = 1 1. 23 -13 15");
				pythia.readString("24:addChannel = 1 1. 23 1 -2");
				
			}
			
			
			
			// B decay properties
			if(cBflag){	// charged B, 521 and 541
				pythia.readString("511:onMode = off");
				pythia.readString("531:onMode = off");
				
				if(!no3mesonflag) pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/cB_wmeson_HNL"+HNL_id_s2+".cmnd");
				else{
					 pythia.readString("521:oneChannel = 1 1. 22 "+HNL_id_s2+" -13 ");
					 pythia.readString("541:oneChannel = 1 1. 22 "+HNL_id_s2+" -13 ");
				 }
			}
			
			else if(!cBflag){ //neutral B, 511 and 531
				pythia.readString("521:onMode = off");
				pythia.readString("541:onMode = off");
				
				pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/nB_wmeson_HNL"+HNL_id_s2+".cmnd");
				
			}
			
			
			
			
			
			
			/***  Processes selection  ***/
			//pythia.readString("HardQCD:all = on");
			pythia.readString("HardQCD:hardbbbar=on");
			//pythia.readString("WeakSingleBoson:all=on");
			//pythia.readString("WeakSingleBoson:ffbar2W = on");
		  
		 
			//pythia.readString("WeakBosonExchange:all=on");
			//pythia.readString("WeakBosonAndParton:all=on");
			//pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	
			pythia.readString("LeftRightSymmmetry:all=on");
		  
			//pythia.readString("TwoFermions2W2TwoFermion=on");
			//pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");
			//pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	

			// Conditions on daughters  
			pythia.readString("PhaseSpace:pTHatMin = 20.");
		  
			// Initialisation
			// pythia.readString("Init:showAllParticleData=on");
			pythia.readString("Next:numberShowEvent=10");
			//double tau0max = 
			

			pythia.init(); 					//take its values from the beam specification stored in the Settings database

		  

			// Interesting amounts

			
			std::vector<int> B_d_id;		//softer of the two B
			std::vector<int> hB_d_id = {111, 113, 221, 223, 331, -421, -423, -425,-10421,-10423,-20423};	//heavier of the two B
			
			if(cBflag and !no3mesonflag){
				B_d_id = {111, 113, 221, 223, 331, -421, -423, -425};	//B+
				hB_d_id = {421, 423, 441, 443, 511, 513, 533};			//Bc+
			}
			else if(!cBflag and !no3mesonflag){
				B_d_id = {-211, -213, -411, -413, -415};				//B0
				hB_d_id = {-321, -323, -431, -433, -435};				//Bs0
			}
			
			
			//if(!scanflag){
				Double_t B_P2(0),  B_PX(0), B_PY(0), B_PZ(0), B_PT(0), B_E(0);
				Double_t B_M(0),	B_tau(0);
				Double_t B_Xp(0),  B_Yp(0),  B_Zp(0),  B_Tp(0), B_Vp(0);
				Double_t B_Xd(0),  B_Yd(0),  B_Zd(0),  B_Td(0), B_Vd(0);
				Double_t B_Xdiff(0),	B_Ydiff(0),	B_Zdiff(0),  	B_Tdiff(0);
				Double_t B_POL(0),	B_SCALE(0);
				
				Double_t mu1_P2(0),  mu1_PX(0), mu1_PY(0), mu1_PZ(0), mu1_PT(0), mu1_E(0);
				Double_t mu1_M(0),	mu1_tau(0);
				Double_t mu1_Xp(0),  mu1_Yp(0),  mu1_Zp(0),  mu1_Tp(0), mu1_Vp(0);
				Double_t mu1_POL(0), mu1_SCALE(0);
				
				Double_t meson_P2(0),  meson_PX(0), meson_PY(0), meson_PZ(0), meson_PT(0), meson_E(0);
				Double_t meson_M(0),	meson_tau(0);
				Double_t meson_Xp(0),  meson_Yp(0),  meson_Zp(0),  meson_Tp(0), meson_Vp(0);
				Double_t meson_POL(0), meson_SCALE(0);
				
				Double_t mu2_P2(0), mu2_PX(0), mu2_PY(0), mu2_PZ(0), mu2_PT(0), mu2_E(0);
				Double_t mu2_M(0),	mu2_MT(0),	mu2_tau(0);
				Double_t mu2_Xp(0),  mu2_Yp(0),  mu2_Zp(0),  mu2_Tp(0), mu2_Vp(0);
				Double_t mu2_POL(0), mu2_SCALE(0);
			  
				Double_t pi_P2(0),  pi_PX(0), 	pi_PY(0), pi_PZ(0), pi_PT(0), pi_E(0);
				Double_t pi_M(0),	pi_MT(0),	pi_tau(0);
				Double_t pi_Xp(0),  pi_Yp(0),	pi_Zp(0),  pi_Tp(0), pi_Vp(0);
				Double_t pi_Xd(0),  pi_Yd(0),	pi_Zd(0),  pi_Td(0), pi_Vd(0);
				Double_t pi_POL(0),	pi_SCALE(0);
				
				
				Double_t N_P2(0),	N_PX(0), 	N_PY(0),	N_PZ(0), N_PT(0), N_E(0);
				Double_t N_M(0),	N_MT(0),	N_tau(0);
				Double_t N_Xp(0),	N_Yp(0),	N_Zp(0),  	N_Tp(0), N_Vp(0);
				Double_t N_Xd(0),	N_Yd(0),	N_Zd(0),  	N_Td(0), N_Vd(0);
				Double_t N_Xdiff(0),	N_Ydiff(0),	N_Zdiff(0),  	N_Tdiff(0);
				Double_t N_POL(0),	N_SCALE(0);
				
				Double_t nNP(0), nND(0), rN(0);
				
			  
				

				/** Set up the ROOT TFile and TTree, TBranch.  **/
				
				TFile *file = TFile::Open("./pytree_"+HNL_id_s+"_cB"+cBflag_s+"_"+no3mesonflag_s+"_"+tauMode_s+".root","recreate");
				//Event *event = &pythia.event;
				TTree *Tgmo = new TTree("Tgrandmother","mytree");
				TTree *Tmo = new TTree("Tmother","mytree");
				TTree *Tda = new TTree("Tdaughters","mytree");
			  
				//T->Branch("event",&event);
				//TBranch b_mu2_P2("mu2_P2",&mu2_P2);
				
				
				TBranch *b_B_PX = Tgmo->Branch("B_PX",&B_PX, "B_PX/D");
				TBranch *b_B_PY = Tgmo->Branch("B_PY",&B_PY, "B_PY/D");
				TBranch *b_B_PZ = Tgmo->Branch("B_PZ",&B_PZ, "B_PZ/D");
				TBranch *b_B_PT = Tgmo->Branch("B_PT",&B_PT, "B_PT/D");
				TBranch *b_B_E  = Tgmo->Branch("B_E",&B_E,   "B_E/D");
				TBranch *b_B_M= Tgmo->Branch("B_M",&B_M, "B_M/D");
				
				TBranch *b_B_tau= Tgmo->Branch("B_tau",&B_tau, "B_tau/D");
				TBranch *b_B_Xp = Tgmo->Branch("B_Xp",&B_Xp, "B_Xp/D");
				TBranch *b_B_Yp = Tgmo->Branch("B_Yp",&B_Yp, "B_Yp/D");
				TBranch *b_B_Zp = Tgmo->Branch("B_Zp",&B_Zp, "B_Zp/D");
				TBranch *b_B_Tp = Tgmo->Branch("B_Tp",&B_Tp, "B_Tp/D");

				TBranch *b_B_Xd = Tgmo->Branch("B_Xd",&B_Xd, "B_Xd/D");
				TBranch *b_B_Yd = Tgmo->Branch("B_Yd",&B_Yd, "B_Yd/D");
				TBranch *b_B_Zd = Tgmo->Branch("B_Zd",&B_Zd, "B_Zd/D");
				TBranch *b_B_Td = Tgmo->Branch("B_Td",&B_Td, "B_Td s/D");
				
				TBranch *b_B_POL= Tgmo->Branch("B_POL",&B_POL, "B_POL/D");
				TBranch *b_B_SCALE= Tgmo->Branch("B_SCALE",&B_SCALE, "B_SCALE/D");
				
				
				
				
				TBranch *b_meson_PX = Tmo->Branch("meson_PX",&meson_PX, "meson_PX/D");
				TBranch *b_meson_PY = Tmo->Branch("meson_PY",&meson_PY, "meson_PY/D");
				TBranch *b_meson_PZ = Tmo->Branch("meson_PZ",&meson_PZ, "meson_PZ/D");
				TBranch *b_meson_PT = Tmo->Branch("meson_PT",&meson_PT, "meson_PT/D");
				TBranch *b_meson_E  = Tmo->Branch("meson_E",&meson_E,   "meson_E/D");
				TBranch *b_meson_M= Tmo->Branch("meson_M",&meson_M, "meson_M/D");
				
				TBranch *b_meson_tau= Tmo->Branch("meson_tau",&meson_tau, "meson_tau/D");
				TBranch *b_meson_Xp = Tmo->Branch("meson_Xp",&meson_Xp, "meson_Xp/D");
				TBranch *b_meson_Yp = Tmo->Branch("meson_Yp",&meson_Yp, "meson_Yp/D");
				TBranch *b_meson_Zp = Tmo->Branch("meson_Zp",&meson_Zp, "meson_Zp/D");
				TBranch *b_meson_Tp = Tmo->Branch("meson_Tp",&meson_Tp, "meson_Tp/D");

				TBranch *b_meson_POL= Tmo->Branch("meson_POL",&meson_POL, "meson_POL/D");
				TBranch *b_meson_SCALE= Tmo->Branch("meson_SCALE",&meson_SCALE, "meson_SCALE/D");
				
				
				
				TBranch *b_mu1_PX = Tmo->Branch("mu1_PX",&mu1_PX, "mu1_PX/D");
				TBranch *b_mu1_PY = Tmo->Branch("mu1_PY",&mu1_PY, "mu1_PY/D");
				TBranch *b_mu1_PZ = Tmo->Branch("mu1_PZ",&mu1_PZ, "mu1_PZ/D");
				TBranch *b_mu1_PT = Tmo->Branch("mu1_PT",&mu1_PT, "mu1_PT/D");
				TBranch *b_mu1_E  = Tmo->Branch("mu1_E",&mu1_E,   "mu1_E/D");
				TBranch *b_mu1_M= Tmo->Branch("mu1_M",&mu1_M, "mu1_M/D");
				
				TBranch *b_mu1_tau= Tmo->Branch("mu1_tau",&mu1_tau, "mu1_tau/D");
				TBranch *b_mu1_Xp = Tmo->Branch("mu1_Xp",&mu1_Xp, "mu1_Xp/D");
				TBranch *b_mu1_Yp = Tmo->Branch("mu1_Yp",&mu1_Yp, "mu1_Yp/D");
				TBranch *b_mu1_Zp = Tmo->Branch("mu1_Zp",&mu1_Zp, "mu1_Zp/D");
				TBranch *b_mu1_Tp = Tmo->Branch("mu1_Tp",&mu1_Tp, "mu1_Tp/D");

				TBranch *b_mu1_POL= Tmo->Branch("mu1_POL",&mu1_POL, "mu1_POL/D");
				TBranch *b_mu1_SCALE= Tmo->Branch("mu1_SCALE",&mu1_SCALE, "mu1_SCALE/D");
				//TBranch *b_mu1_Xd = Tmo->Branch("mu1_Xd",&mu1_Xd, "mu1_Xd/D");
				//TBranch *b_mu1_Yd = Tmo->Branch("mu1_Yd",&mu1_Yd, "mu1_Yd/D");
				//TBranch *b_mu1_Zd = Tmo->Branch("mu1_Zd",&mu1_Zd, "mu1_Zd/D");
				//TBranch *b_mu1_Td = Tmo->Branch("mu1_Td",&mu1_Td, "mu1_Td s/D");
				
				
				
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
				
				TBranch *b_mu2_POL= Tda->Branch("mu2_POL",&mu2_POL, "mu2_POL/D");
				TBranch *b_mu2_SCALE= Tda->Branch("mu2_SCALE",&mu2_SCALE, "mu2_SCALE/D");
				//TBranch *b_mu2_Xd = Tda->Branch("mu2_Xd",&mu2_Xd, "mu2_Xd/D");
				//TBranch *b_mu2_Yd = Tda->Branch("mu2_Yd",&mu2_Yd, "mu2_Yd/D");
				//TBranch *b_mu2_Zd = Tda->Branch("mu2_Zd",&mu2_Zd, "mu2_Zd/D");
				//TBranch *b_mu2_Td = Tda->Branch("mu2_Td",&mu2_Td, "mu2_Td s/D");


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

				TBranch *b_pi_POL= Tda->Branch("pi_POL",&pi_POL, "pi_POL/D");
				TBranch *b_pi_SCALE= Tda->Branch("pi_SCALE",&pi_SCALE, "pi_SCALE/D");
				//TBranch *b_pi_Xd = Tda->Branch("pi_Xd",&pi_Xd, "pi_Xd/D");
				//TBranch *b_pi_Yd = Tda->Branch("pi_Yd",&pi_Yd, "pi_Yd/D");
				//TBranch *b_pi_Zd = Tda->Branch("pi_Zd",&pi_Zd, "pi_Zd/D");
				//TBranch *b_pi_Td = Tda->Branch("pi_Td",&pi_Td, "pi_Td s/D");

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
			
			//}// if not a scan
			
			
			
		 
		  
			int iAbort = 0;
			int d1, d2;
			int cnt=0;
			std::vector<int> daughters{};

			
			for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
				
				
				//if event odd and tau
				//if(iEvent % 2 ==0)pythia.readString("TauDecays:tauPolarization=1.");
				// if event even
				//if(iEvent % 2 !=0)
				//Generate events. Quit if many failures.
				// Generate events. Quit if many failures.
				if (!pythia.next()) {
					if (++iAbort < nAbort) continue;
					cout << " Event generation aborted prematurely, owing to error!\n";
					break;
				}
				
				std::vector<vector<int>> Bdaughters{};
				std::vector<vector<int>> Ndaughters{};
				
				// Loop over all particles and analyze the final-state ones.
				for (int i = 0; i < pythia.event.size(); ++i){
					//if (pythia.event[i].isFinal()) {
					int idAbs = pythia.event[i].idAbs(); int status = pythia.event[i].status();
					
					//cout << "idAbs " << idAbs << endl;
					//cout << "status " << status << endl;
					bool Bidcond;
					if(cBflag) Bidcond=idAbs==521 or idAbs==541; //cB : B+(id:521) and B_c+(id:541)
					else if(!cBflag) Bidcond=idAbs==511 or idAbs==531; //nB : B0(id:511) and B_s0(id:531)
					
					if ((Bidcond) and status < 0){ // decaying B 
						//cout << " HALLO SUSY1!" << endl;
						if(!no3mesonflag and pythia.event[i].daughter2()-pythia.event[i].daughter1()==2) Bdaughters.push_back({pythia.event[i].daughter1(), i});
						if(no3mesonflag and pythia.event[i].daughter2()-pythia.event[i].daughter1()==1){
							 Bdaughters.push_back({pythia.event[i].daughter1(), i});
							 //cout << " HALLO SUSY!" << endl;
						 }
					
					
					}// id 1 and status negative
					
				}//loop on event (i)
				
				// Bdaighters: N and mu : become the mothers
				
				//cout<<"Bdaughters.size(): " << Bdaughters.size() << endl;
				
				for (int k(0); k<Bdaughters.size(); ++k){
					std::vector<int> dcouple = Bdaughters[k];
					int d1=dcouple[0]; int d2=d1+1; int d3=d1+2;
					int i =dcouple[1];
					
					int d1_idAbs=pythia.event[d1].idAbs(); int d1_status=pythia.event[d1].status();
					int d2_id=pythia.event[d2].id(); int d2_status=pythia.event[d2].status();
					int d3_id;
					if(!no3mesonflag) d3_id=pythia.event[d3].id();

					bool meson_flag1; bool meson_flag2;
					bool meson_flag;
					bool condition;
					
					if(!no3mesonflag){
						meson_flag1=(std::find(B_d_id.begin(), B_d_id.end(), d3_id) != B_d_id.end());
						meson_flag2=(std::find(hB_d_id.begin(), hB_d_id.end(), d3_id) != hB_d_id.end());
						meson_flag = meson_flag1 or meson_flag2;
						condition= (d1_idAbs == HNL_id) and (d2_id == -13) and meson_flag;
					}
					else if(no3mesonflag){
						condition= (d1_idAbs == HNL_id and d2_id == -13);
						//cout << "condition    " << condition << endl;
						//cout << "d1_idAbs    " << d1_idAbs << endl;
						//cout << "d2_id    " << d2_id << endl;
					}
					
					
					if((condition) and (d1_status<0 and d2_status>0)) { // if the daughter of B is decaying HNL and remaining mu
					
						if(!scanflag){
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
							B_E=EI; 	//B_P2=P2I; 	
							B_M=MI; 	//B_P2=P2I; 	
							B_PT=PTI;
							B_PX=PXI; 	B_PY=PYI; 	B_PZ=PZI;
							
							B_tau=TAUI; 
							B_Xp=XpI; 	B_Yp=YpI; 	B_Zp=ZpI;	B_Tp=TpI;
							B_Xd=XdI; 	B_Yd=YdI; 	B_Zd=ZdI;	B_Td=TdI;
							
							B_Xdiff=XdI-XpI; 	B_Ydiff=YdI-YpI; 	B_Zdiff=ZdI-ZpI;	B_Tdiff=TdI-TpI;
							
							Tgmo->Fill();
						
						
							Ndaughters.push_back({pythia.event[d1].daughter1(), pythia.event[d1].daughter2()});
							
							// Interesting quantities for N
							N_E = pythia.event[d1].e();
							N_M = pythia.event[d1].m();
							N_MT = pythia.event[d1].mT();
							//N_P2 = pythia.event[d1].p2(
							N_PX = pythia.event[d1].px();
							N_PY = pythia.event[d1].py();
							N_PZ = pythia.event[d1].pz();
							N_PT = pythia.event[d1].pT();
							N_tau = pythia.event[d1].tau();
						  
							N_Xp = pythia.event[d1].xProd();
							N_Yp = pythia.event[d1].yProd();
							N_Zp = pythia.event[d1].zProd();
							N_Tp = pythia.event[d1].tProd();
							
							N_Xd = pythia.event[d1].xDec();
							N_Yd = pythia.event[d1].yDec();
							N_Zd = pythia.event[d1].zDec();
							N_Td = pythia.event[d1].tDec();
							
							N_POL = pythia.event[d1].pol();
							N_SCALE = pythia.event[d1].scale();
							
							// Interesting quantities for mu+
							mu1_E = pythia.event[d2].e();
							mu1_M = pythia.event[d2].m();
							//mu1_MT = pythia.event[d2].mT();
							//mu1_P2 = pythia.event[d2].p2(
							mu1_PX = pythia.event[d2].px();
							mu1_PY = pythia.event[d2].py();
							mu1_PZ = pythia.event[d2].pz();
							mu1_PT = pythia.event[d2].pT();
							mu1_tau = pythia.event[d2].tau();
						  
							mu1_Xp = pythia.event[d2].xProd();
							mu1_Yp = pythia.event[d2].yProd();
							mu1_Zp = pythia.event[d2].zProd();
							mu1_Tp = pythia.event[d2].tProd();
							
							//mu1_Xd = pythia.event[d2].xDec();
							//mu1_Yd = pythia.event[d2].yDec();
							//mu1_Zd = pythia.event[d2].zDec();
							//mu1_Td = pythia.event[d2].tDec();
							
							mu1_POL = pythia.event[d2].pol();
							mu1_SCALE = pythia.event[d2].scale();
							
							
							if(!no3mesonflag){
								// Interesting quantities for mu+
								meson_E = pythia.event[d3].e();
								meson_M = pythia.event[d3].m();
								//meson_MT = pythia.event[d3].mT();
								//meson_P2 = pythia.event[d3].p2(
								meson_PX = pythia.event[d3].px();
								meson_PY = pythia.event[d3].py();
								meson_PZ = pythia.event[d3].pz();
								meson_PT = pythia.event[d3].pT();
								meson_tau = pythia.event[d3].tau();
							  
								meson_Xp = pythia.event[d3].xProd();
								meson_Yp = pythia.event[d3].yProd();
								meson_Zp = pythia.event[d3].zProd();
								meson_Tp = pythia.event[d3].tProd();
								
								//meson_Xd = pythia.event[d3].xDec();
								//meson_Yd = pythia.event[d3].yDec();
								//meson_Zd = pythia.event[d3].zDec();
								//meson_Td = pythia.event[d3].tDec();
								
								meson_POL = pythia.event[d3].pol();
								meson_SCALE = pythia.event[d3].scale();
							}		
							Tmo->Fill();
						}// if not scanflag
						
						nNP++; 
						hscan_nNP->Fill(mN,tau0,nNP);
						
						//cout << "daughter1" << pythia.event[d1].daughter1();
						//cout << "daughter2" << pythia.event[d1].daughter2();
					}// decaying HNL
					
					//}
				}// end of mothers selection
				
				
				/** DAUGHTERS SELECTION **/
				
				
				//cout << "Ndaughters.size()" << Ndaughters.size() << endl;
				
				
				for (int k(0); k<Ndaughters.size(); ++k){
					std::vector<int> dcouple = Ndaughters[k];
					int d1=dcouple[0]; int d2=d1+1; //int d3=d1+2;
					
					int d1_id=pythia.event[d1].id(); int d1_status=pythia.event[d1].status();
					int d2_id=pythia.event[d2].id(); int d2_status=pythia.event[d2].status();
					//int d3_id=pythia.event[d3].id();
					//cout<<"d1_id:" << d1_id <<"  d2_id:" << d2_id << endl;
					//cout<<"d1_status:" << d1_status <<"  d2_status:" << d2_status << endl;
					
					
					
					if(d1_id==-13 and d2_id==-211) { // if the daughter of N is mu+ pi-
					
						if(!scanflag){
							// Interesting quantities for N
							mu2_E = pythia.event[d1].e();
							mu2_M = pythia.event[d1].m();
							mu2_MT = pythia.event[d1].mT();
							//mu2_P2 = pythia.event[d1].p2(
							mu2_PX = pythia.event[d1].px();
							mu2_PY = pythia.event[d1].py();
							mu2_PZ = pythia.event[d1].pz();
							mu2_PT = pythia.event[d1].pT();
							mu2_tau = pythia.event[d1].tau();
						  
							mu2_Xp = pythia.event[d1].xProd();
							mu2_Yp = pythia.event[d1].yProd();
							mu2_Zp = pythia.event[d1].zProd();
							mu2_Tp = pythia.event[d1].tProd();
							
							//mu2_Xd = pythia.event[d1].xDec();
							//mu2_Yd = pythia.event[d1].yDec();
							//mu2_Zd = pythia.event[d1].zDec();
							//mu2_Td = pythia.event[d1].tDec();
							
							mu2_POL = pythia.event[d1].pol();
							mu2_SCALE = pythia.event[d1].scale();
							
							// Interesting quantities for mu+
							pi_E = pythia.event[d2].e();
							pi_M = pythia.event[d2].m();
							pi_MT = pythia.event[d2].mT();
							//pi_P2 = pythia.event[d2].p2(
							pi_PX = pythia.event[d2].px();
							pi_PY = pythia.event[d2].py();
							pi_PZ = pythia.event[d2].pz();
							pi_PT = pythia.event[d2].pT();
							pi_tau = pythia.event[d2].tau();
						  
							pi_Xp = pythia.event[d2].xProd();
							pi_Yp = pythia.event[d2].yProd();
							pi_Zp = pythia.event[d2].zProd();
							pi_Tp = pythia.event[d2].tProd();
							
							pi_Xd = pythia.event[d2].xDec();
							pi_Yd = pythia.event[d2].yDec();
							pi_Zd = pythia.event[d2].zDec();
							pi_Td = pythia.event[d2].tDec();
							
							pi_POL = pythia.event[d2].pol();
							pi_SCALE = pythia.event[d2].scale();
							
							Tda->Fill();
						}//if not scan flag
						
						else if(scanflag){
							nND1++;
							cout << "nND1: " << nND1 << endl;
							hscan_nND1->Fill(mN,tau0);
						}
					
					}// mu+ pi- channel
					
					
					//}
				}// end of daughters selection
				
			}//loop on all events
			
			// Statistics on event generation.
			pythia.stat();

			if(!scanflag){
				//  Write tree.
				Tda->Print(); Tmo->Print(); Tgmo->Print();
				Tda->Write(); Tmo->Write(); Tgmo->Write();
				cout << "Tree written !" << endl;
			}
			
			
			else if(scanflag){
				cout << "rN :" << rN1 << endl;
				cout << "cnt :" << cnt << endl;
				rN1 = (double)nND1/(double)nNP;	
				rN2 = (double)nND2/(double)nNP;	
				
				g1->SetPoint(cnt, mN, tau0, rN1);
				g1f->SetPoint(cnt, mN, tau0, rN1);
				g1fprojx->SetPoint(cnt, mN, rN1);
				g1fprojy->SetPoint(cnt, tau0, rN1);
				
				g2->SetPoint(cnt, mN, tau0, rN2);
				g2f->SetPoint(cnt, mN, tau0, rN2);
				g2fprojx->SetPoint(cnt, mN, rN2);
				g2fprojy->SetPoint(cnt, tau0, rN2);
				
				cnt=cnt+1;
			}
			
			delete Tgmo; delete Tmo; delete Tda;
			delete file;
			
		}//loop on tau
	}//loop of mN	
		
	if(scanflag){
		//SetBinY(hscan_nNP);
		cnNP->cd();
		hscan_nNP->Draw("colz");
		
		
		
		//hscan_nNP->Write();
		cnNP->SaveAs("./output/scan_nNP_"+HNL_id_s+".root");
		
		//SetBinY(hscan_nND);
		cnND->cd();
		hscan_nND1->Draw("colz");
		//hscan_nND->Write();
		cnND->SaveAs("./output/scan_nND"+HNL_id_s+".root");
		
		
		cnBP->cd();
		hscan_nBP->Draw("BAR");
		//hscan_nND->Write();
		hscan_nBP->GetXaxis()->SetBinLabel(2,Bids[0]);
		hscan_nBP->GetXaxis()->SetBinLabel(17,Bids[1]);
		hscan_nBP->GetXaxis()->SetBinLabel(31,Bids[2]);
		hscan_nBP->GetXaxis()->SetBinLabel(46,Bids[3]);
		
		//hscan_nBP->Scale(1/hscan_nBP->Integral("width"));
		hscan_nBP->SetFillColor(50);
		cnBP->SaveAs("./output/scan_nBP"+HNL_id_s+".root");
		
		crN1->cd();
		g1->SetTitle("b#rightarrow N#rightarrow #mu^{+} #pi^{-} (SS muons); m#_{N} [GeV]; tau_{0} [ps]; #n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		//g1->GetHistogram()->GetXaxis()->SetTitle("m#_{N} [GeV]");
		//g1->GetYaxis()->SetTitle("#tau_{0} [ps]");
		//g1->GetZaxis()->SetTitle("#n(b #rightarrow N #rightarrow #mu #pi) / n(b #rightarrow N)");
		g1->Draw("surf1");
		
		
		/** PROJECTION **/
		crN1f->cd();
		//crN1f->SetTitle("b#rightarrow N#rightarrow #mu^{+} #pi^{-} (SS muons)");
		g1f->SetTitle("b#rightarrow N#rightarrow #mu^{+} #pi^{-} (SS muons); m_{N} [GeV]; #tau_{0} [ps]; n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		//g1f->GetXaxis()->SetTitle("m#_{N} [GeV]");
		//g1f->GetYaxis()->SetTitle("#tau_{0} [ps]");
		//g1f->GetZaxis()->SetTitle("#n(b #rightarrow N #rightarrow #mu #pi) / n(b #rightarrow N)");
		
		// Create the three pads
		TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.6,0.6);
		center_pad->Draw();

		TPad *right_pad = new TPad("right_pad", "right_pad",0.55,0.0,1.0,0.6);
		right_pad->Draw();

		TPad *top_pad = new TPad("top_pad", "top_pad",0.0,0.55,0.6,1.0);
		top_pad->Draw();

		TH1 * projh2X = g1f->Project("x");
		TH1 * projh2Y = g1f->Project("y");

		// Drawing
		center_pad->cd();
		//gStyle->SetPalette(1);
		
		g1f->Draw("COLZ");

		top_pad->cd();
		projh2X->SetFillColor(kBlue+1);
		//projh2X->SetTitle("; m_{N} [GeV]; n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2X->GetXaxis()->SetTitle("m_{N} [GeV]");
		projh2X->GetYaxis()->SetTitle("n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		
		projh2X->Draw("bar");

		right_pad->cd();
		projh2Y->SetFillColor(kBlue-2);
		//g1fprojy->SetTitle("; #tau_{0} [ps]; #n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2Y->GetXaxis()->SetTitle("#tau_{0} [ps]");
		projh2Y->GetYaxis()->SetTitle("n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2Y->Draw("hbar");
	   
		
		crN1f->SaveAs("./output/scan_rN1f_proj_"+HNL_id_s+".root");

		
		
		
		
		crN2->cd();
		g2->GetXaxis()->SetTitle("m#_{N} [GeV]");
		g2->GetYaxis()->SetTitle("#tau_{0} [ps]");
		g2->GetZaxis()->SetTitle("#n(b #rightarrow N #rightarrow #mu #pi) / n(b #rightarrow N)");
		g2->Draw("surf1");
		
		
		
		
		/**** ***/
		
		crN2f->cd();
		g2f->SetTitle("b#rightarrow N#rightarrow #mu^{-} #pi^{+} (OS muons); m_{N} [GeV]; #tau_{0} [ps]; n(b #rightarrow N #rightarrow #mu^{-} #pi^{+}) / n(b #rightarrow N)");
		//g1f->GetXaxis()->SetTitle("m#_{N} [GeV]");
		//g1f->GetYaxis()->SetTitle("#tau_{0} [ps]");
		//g1f->GetZaxis()->SetTitle("#n(b #rightarrow N #rightarrow #mu #pi) / n(b #rightarrow N)");
		
		// Create the three pads
		TPad *center_pad2 = new TPad("center_pad2", "center_pad",0.0,0.0,0.6,0.6);
		center_pad->Draw();

		TPad *right_pad2 = new TPad("right_pad2", "right_pad",0.55,0.0,1.0,0.6);
		right_pad->Draw();

		TPad *top_pad2 = new TPad("top_pad2", "top_pad",0.0,0.55,0.6,1.0);
		top_pad->Draw();

		TH1 * projh2X2 = g2f->Project("x");
		TH1 * projh2Y2 = g2f->Project("y");

		// Drawing
		center_pad2->cd();
		//gStyle->SetPalette(1);
		g2f->Draw("COLZ");

		top_pad2->cd();
		projh2X2->SetFillColor(kBlue+1);
		//g2fprojx->SetTitle("; m_{N} [GeV]; #n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2X2->GetXaxis()->SetTitle("m_{N} [GeV]");
		projh2X2->GetYaxis()->SetTitle("n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2X2->Draw("bar");

		right_pad2->cd();
		projh2Y2->SetFillColor(kBlue-2);
		//g2fprojy->SetTitle("; #tau_{0} [ps]; #n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2Y->GetXaxis()->SetTitle("#tau_{0} [ps]");
		projh2Y->GetYaxis()->SetTitle("n(b #rightarrow N #rightarrow #mu^{+} #pi^{-}) / n(b #rightarrow N)");
		projh2Y2->Draw("hbar");
	   
		
		crN2f->SaveAs("./output/scan_rN2f_proj.root");

		
		//hscan_rN->Write();
		crN1->SaveAs("./output/scan_rN1_"+HNL_id_s+".root");
		crN2->SaveAs("./output/scan_rN2_"+HNL_id_s+".root");
		
		crN1f->SaveAs("./output/scan_rN1f_"+HNL_id_s+".root");
		crN2f->SaveAs("./output/scan_rN2f_"+HNL_id_s+".root");
		
		
		
	}
	delete cnNP; delete cnND; delete crN1; delete crN2; delete crN1f; delete crN2f;

	// Done.
	return 0;
}
