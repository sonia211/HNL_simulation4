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
	int nEvent = 200;
	
	// Values of the scan
	vector<double> tau0vec = {1., 2., 5., 10., 20., 50., 100.}; 	// in ps, logarithmique
	vector<double> mNvec = {0.244,0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.0};  // in GeV, linear
	
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
	TH2D *hscan_nND = new TH2D("hscan_nND", "hscan_nND", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	
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
			
			string HNLstr = "15:new = nu_Rmu nu_Rmu 2 0 0 "+std::to_string(mN)+" 0. 0. 0. "+std::to_string(3e-01*tau0);
			pythia.readString(HNLstr);
			pythia.readFile("/home/bouchiba/PDM/pythia8240/cmndfiles/HNLprop_scanC.cmnd");
		  
		  
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
			pythia.init(); 					//take its values from the beam specification stored in the Settings database

		  
		 
		  
			int iAbort = 0;
			for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
				
				int d1, d2;
				std::vector<vector<int>> Bdaughters{};
				std::vector<vector<int>> Ndaughters{};
				
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
					
					bool found = (std::find(Bids.begin(), Bids.end(), idAbs) != Bids.end());
					//if (found){
					
					if (idAbs==511 or idAbs==521 or idAbs==531 or idAbs==541)hscan_nBP->Fill(idAbs);
					
					if (idAbs==511 or idAbs==521 and status < 0){ // decaying B+- or B0
						
						Bdaughters.push_back({pythia.event[i].daughter1(), pythia.event[i].daughter2()});
						
						nNP++; 
						hscan_nNP->Fill(mN,tau0,nNP);
						//cout << "nNP: " << nNP << endl;
					}
				
				}//loop on event (i)
				
				
				// Select Produced HNL from user_mothers.
				// Among them, select decaying HNL in user_Nd_channels
				
				for (int k(0); k<Bdaughters.size(); ++k){
					std::vector<int> dcouple = Bdaughters[k];
					int d1=dcouple[0]; int d2=dcouple[1];
					for (int d(d1); d<d2; ++d){
						int d_id=pythia.event[d].id(); int dstatus=pythia.event[d].status();
						if(d_id == 15) { // if the daughter of B is HNL
							//nNP++;
							//hscan_nNP->Fill(mN,tau0);
							
							if (dstatus < 0){
								Ndaughters.push_back({pythia.event[d].daughter1(), pythia.event[d].daughter2()});
								//nND++;
								//hscan_nND->Fill(mN,tau0);
							}
						}
					}
				} // end of part selection process
				
				for (int k(0); k<Ndaughters.size(); ++k){
					std::vector<int> dcouple = Ndaughters[k];
					int d1=dcouple[0]; int d2=dcouple[1];
					int d1_id=pythia.event[d1].id(); int d2_id=pythia.event[d2].id();
					
					if((d1_id==-13 and d2_id==-211) or (d1_id==-211 and d2_id==-13)){
						nND1++;
						cout << "nND1: " << nND1 << endl;
						//hscan_nND1->Fill(mN,tau0);
					}
					
					if((d1_id==13 and d2_id==211) or (d1_id==211 and d2_id==13)){
						nND2++;
						cout << "nND2: " << nND2 << endl;
						//hscan_nND->Fill(mN,tau0);
					}
					
					
					
				} // end of part selection process
				
				
				

				
			}// loop on events
			
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
	
	
	cnBP->cd();
	hscan_nBP->Draw("BAR");
	//hscan_nND->Write();
	hscan_nBP->GetXaxis()->SetBinLabel(2,Bids[0]);
	hscan_nBP->GetXaxis()->SetBinLabel(17,Bids[1]);
	hscan_nBP->GetXaxis()->SetBinLabel(31,Bids[2]);
	hscan_nBP->GetXaxis()->SetBinLabel(46,Bids[3]);
	
	//hscan_nBP->Scale(1/hscan_nBP->Integral("width"));
	hscan_nBP->SetFillColor(50);
	cnBP->SaveAs("./output/scan_nBP.root");
	
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
   
	
	crN1f->SaveAs("./output/scan_rN1f_proj.root");

	
	
	
	
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
	crN1->SaveAs("./output/scan_rN1.root");
	crN2->SaveAs("./output/scan_rN2.root");
	
	crN1f->SaveAs("./output/scan_rN1f.root");
	crN2f->SaveAs("./output/scan_rN2f.root");
	
	
	delete cnNP; delete cnND; delete crN1; delete crN2; delete crN1f; delete crN2f;
	return 0;
}
