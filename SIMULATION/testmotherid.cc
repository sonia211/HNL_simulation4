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
#include "TGraph2D.h"
#include "TAxis.h"
#include "TMath.h"

using namespace Pythia8;

/**
 void BinLogY(TH2*h)
{

   TAxis *axis = h->GetYaxis();
   int bins = axis->GetNbins();

   Axis_t from = axis->GetYmin();
   Axis_t to = axis->GetYmax();
   Axis_t width = (to - from) / bins;
   Axis_t *new_bins = new Axis_t[bins + 1];

   for (int i = 0; i <= bins; i++) {
     new_bins[i] = TMath::Power(10, from + i * width);

   }
   axis->Set(bins, new_bins);
   delete new_bins;
}
* **/

int main() {

	
	
	/** GENERAL PARAMETERS **/
	int nEvent = 500;
	
	// Values of the scan
	//vector<double> tau0vec = {1., 2., 5., 10., 20., 50., 100.}; 	// in ps, logarithmique
	//vector<double> mNvec = {0.244,0.5, 1.5, 2.5, 3.5, 4.5, 5.5};  // in GeV, linear
	
	vector<Double_t> mNvec = {2.5};
	vector<Double_t> tau0vec = {10., 20.};
	vector<Double_t> tau0powervec = {0., 3.};
	
	// Histograms / TGraph to fill
	
	TCanvas *cnNP = new TCanvas("cnNP","cnNP",800,600);
	TCanvas *cnND = new TCanvas("cnND","cnND",800,600);
	TCanvas *crN = new TCanvas("crN","crN",800,600);

	TH2D *hscan_nNP = new TH2D("hscan_nNP", "hscan_nNP", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	TH2D *hscan_nND = new TH2D("hscan_nND", "hscan_nND", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	TGraph2D *g = new TGraph2D();
	
	
	// Tools variables 
	int nNP(0), nND(0);
	double rN(0.);
	Double_t mN(0);
	Double_t tau0(0);
	int cnt(0);
	
	
	
	// Begin the scan. Double loop on mNvec and tau0vec 
	for (int a(0); a<mNvec.size(); ++a){ // loop on masses
		mN=mNvec[a];
		
		cout << "mN: " << mN << endl;
		
		for (int b(0); b<tau0vec.size(); ++b){ // loop on lifetimes
			tau0=tau0vec[b];
			//cout << "cnt: " << cnt << endl;
			
			
			cout << "tau0: " << tau0 << endl;
			
			/** Begin simulation **/
			
			Pythia pythia;
			// Shorthand for the event record in pythia. LHC settings.
			Event& event = pythia.event;
			ParticleData& particleData = pythia.particleData;
			pythia.readString("Beams:eCM=14000.");
		  
			// Extract settings to be used in the main program.
			//int nEvent = pythia.mode("Main:numberOfEvents");
			
			
			int nAbort = pythia.mode("Main:timesAllowErrors");
		  
			//DecayHandler* chainDecayPtr( vector<int>& idProd, vector<int>& motherProd, vector<double>& mProd, vector<Vec4>& pProd, int iDec, const Event& event)  
			//std::vector<int> particles;
			//pythia.setDecayPtr( chainDecayPtr, particles); 
			
			cout << "std::to_string(mN) " << std::to_string(mN);
			cout << "std::to_string(3e-01*tau0)" << std::to_string(3e-01*tau0);
			
			string HNLstr = "9900014:new = nu_Rmu nu_Rmu 2 0 0 "+std::to_string(mN)+" 0. 0. 0. "+std::to_string(3e-01*tau0);
			pythia.readString(HNLstr);
			pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/HNLprop_scan.cmnd");
		  
		  
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

		  
		 
		  
			int iAbort = 0;
			int d1, d2;
			//int cnt=0;
			std::vector<vector<int>> daughters{};
			std::vector<int> mothers{};
			for (int iEvent = 0; iEvent < nEvent; ++iEvent) {

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
					
					if (idAbs==511 or idAbs==521 and status < 0){ // decaying cB or B0
						
						daughters.push_back({pythia.event[i].daughter1(), pythia.event[i].daughter2()});
						
						//nNP++; 
						//hscan_nNP->Fill(mN,tau0,nNP);
						//cout << "nNP: " << nNP << endl;
					}
					else if (idAbs==9900014 and status < 0){ // decaying hNL
						
						mothers.push_back(pythia.event[i].mother1());
						nND++; 
						hscan_nND->Fill(mN,tau0);
						//cout << "nND: " << nND << endl;
					}
					
				
				}//loop on event (i)
				
				
				for (int k(0); k<daughters.size(); ++k){
					std::vector<int> dcouple = daughters[k];
					int d1=dcouple[0]; int d2=dcouple[1];
					for (int d(d1); d<d2; ++d){
						int d_id=pythia.event[d].id();
						
						if(d_id == 9900014) {
						nNP++;
						hscan_nNP->Fill(mN,tau0);
						}
					}
				}
				
				
				for (int k(0); k<mothers.size(); ++k){
					cout<<"mother id" << pythia.event[mothers[k]].id()<<endl;
				}
				
				
				
				// pour that event, cont the number of HNL daughters
			
				
			}// loop on events
			
			cout << "rN :" << rN << endl;
			cout << "cnt :" << cnt << endl;
			rN = (double)nND/(double)nNP;	
			g->SetPoint(cnt, mN, tau0, rN);
			cnt=cnt+1;
			
			//hscan_rN->Fill(mN,tau0,rN);
		}// loop on tau0vec
	}// loop on mNvec
	
	//SetBinY(hscan_nNP);
	cnNP->cd();
	hscan_nNP->Draw("colz");
	
	
	
	//hscan_nNP->Write();
	cnNP->SaveAs("./output/scan_nNP.root");
	
	//SetBinY(hscan_nND);
	cnND->cd();
	hscan_nND->Draw("colz");
	//hscan_nND->Write();
	cnND->SaveAs("./output/scan_nND.root");
	
	crN->cd();
	g->GetXaxis()->SetTitle("m#_{N} [GeV]");
	g->GetYaxis()->SetTitle("#tau_{0} [ps]");
	g->GetZaxis()->SetTitle("#n(b #rightarrow N #rightarrow #mu #pi) / n(b #rightarrow N)");
	g->Draw("surf1");
	
	
	//hscan_rN->Write();
	crN->SaveAs("./output/scan_rN.root");
	
	
	delete cnNP; delete cnND; delete crN;
	return 0;
}

