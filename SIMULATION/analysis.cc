#include "Pythia8/Pythia.h"
//#include "ReadablePart.cc"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"

#include <fstream>
#include <iomanip>
#include <TChain.h>
#include <TList.h>
#include <cmath>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>
#include "TApplication.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <climits>
#include <stdio.h>
#include <TAxis.h>
#include <TROOT.h>
#include <stdio.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <TSystem.h>
//#include "Event.hpp"
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLine.h>
#include <algorithm>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <glob.h>
#include <TCut.h>
#include <vector>

#include <TLorentzVector.h>
#include <TVector3.h>


using namespace Pythia8;

double pi=3.141592;

int main() {
	
	int HNL_id;
	cout << "HNL id (15,25): ";
	cin >> HNL_id;
	
	TString HNL_id_s = std::to_string(HNL_id);
	
	
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
	
	TString FILENAME;
	if(HNL_id==15) FILENAME = "./pytree_"+HNL_id_s+"_cB"+cBflag_s+"_"+no3mesonflag_s+"_4_REF_last.root";
	if(HNL_id==25) FILENAME = "./pytree_25_cB0_0_0_REF_last.root";
	
	//TString FILENAME = "./pytree_25.root";
	
	
	cout << "___m1" << endl;
	TString T1s = "Tgrandmother";
	TString T2s = "Tmother";
	TString T3s = "Tdaughters";
	
	TFile *F = new TFile(FILENAME, "UPDATE");
	TTree *T = new TTree(); TTree *T2 = new TTree(); TTree *T3 = new TTree();
	F->GetObject(T1s, T); F->GetObject(T2s, T2); F->GetObject(T3s, T3);
	//T = (TTree*)F->Get(T1s); T2 = (TTree*)F->Get(T2s); T3 = (TTree*)F->Get(T3s);
	cout << "___m12" << endl;
	//auto T1_ = T1->CloneTree(); auto T2_ = T2->CloneTree(); auto T3_ = T3->CloneTree();
	
	//TList *l = new TList;
	//l->Add(T1); l->Add(T2); l->Add(T3);
	//TTree *T = TTree::MergeTrees(l);
	
	T->AddFriend(T2); T->AddFriend(T3);
	
	//cout << "___m13" << endl;
	
	//TFile *Ofile = TFile::Open("./output/anatree.root","recreate");
	//T->SetName("T");
	//T->Write();
	

	
	
	
	//TString OUTDIR("/home/bouchiba/PDM/pythia8240/rootexamples/output/");
	
	//TFile *OUTF   = new TFile(OUTDIR+VARNAME+"_plot.root", "recreate");
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	c1->cd();
	//Int_t nbins = (int)(MAX-MIN)*2;
	Int_t nbins = 100;
	TH2D* hist = new TH2D("h", "h", nbins, 0., 20., nbins, 0., 15.);
	T->Draw("mu1_PT:mu2_PT>>h","","colz");
	//>>h");
	
	c1->SaveAs("./analplot_"+HNL_id_s+"_nomeson"+std::to_string(no3mesonflag)+"/mumu_plot.root");
	
	
	/**
	Double_t m = v.Mag();       // get magnitude (=rho=Sqrt(x*x+y*y+z*z)))
	Double_t m2 = v.Mag2();     // get magnitude squared
	Double_t t = v.Theta();     // get polar angle
	Double_t ct = v.CosTheta(); // get cos of theta
	Double_t p = v.Phi();       // get azimuth angle
	Double_t pp = v.Perp();     // get transverse component
	Double_t pp2= v.Perp2();    // get transvers component squared

	It is also possible to get the transverse component with respect to another vector:
	Double_t ppv1 = v.Perp(v1);
	Double_t pp2v1 = v.Perp2(v1);

	The pseudo-rapidity ( eta=-ln (tan (theta/2)) ) can be obtained by Eta() or PseudoRapidity():
	Double_t eta = v.PseudoRapidity();
	**/
	
	
	/** Boost in B CM frame **/
	//TLorentzVector D0_P(D0_PX, D0_PY, D0_PZ, D0_PE);
	//TLorentzVector lab1_P(lab1_PX, lab1_PY, lab1_PZ, lab1_PE);
	//TVector3 D0_P_Boost = D0_P.BoostVector();
	//lab1_P.Boost(-D0_P_Boost);
	//TVector3 lab1_P_Boost = lab1_P.BoostVector();
	
	TCanvas *c2 = new TCanvas("c2","c",800,600);
	TH2D* h2 = new TH2D("h2", "h2", 91, -180., 180., 91, -180., 180.);
	
	TCanvas *c3 = new TCanvas("c3","c",800,600);
	TH2D* h3 = new TH2D("h3", "h3", 50, 0., 3., 50, 0., 3.);
	
	TCanvas *c4 = new TCanvas("c4","c",800,600);
	TH2D* h4 = new TH2D("h4", "h4", 50, 0., 180., 50, 0., 180.);
	
	
	TCanvas *c5 = new TCanvas("c5","c",800,600);
	TH1D* h5 = new TH1D("h5", "h5", 50, 0., 6.);
	
	TCanvas *c6 = new TCanvas("c6","c",800,600);
	TH2D* h6 = new TH2D("h6", "", 50, 0., 180., 50, 0., 180.);
	
	TCanvas *c7 = new TCanvas("c7","c",800,600);
	TH2D* h7 = new TH2D("h7", "h5", 50, 0., 180., 50, 0., 180.);
	
	TCanvas *c8 = new TCanvas("c8","c",800,600);
	TH1D* h81 = new TH1D("h81", "81", 100, 0., 180.);
	TH1D* h82 = new TH1D("h82", "82", 100, 0., 180.);
	TH1D* h83 = new TH1D("h83", "83", 100, 0., 180.);
	
	TCanvas *c9 = new TCanvas("c9","c",800,600);
	TH1D* h9 = new TH1D("h9", "", 100, 0., 180.);
	
	TCanvas *c10 = new TCanvas("c10","c",800,600);
	TH2D* h10 = new TH2D("h10", "Correlation PT(N) and angle(mu1mu2)", 50,0., 15., 50, 100., 102);
	
	cout << "___1" << endl;
	
	Double_t B_PX, B_PY, B_PZ, B_E;
	Double_t N_PX, N_PY, N_PZ, N_E, N_PT;
	Double_t pi_PX, pi_PY, pi_PZ, pi_E;
	Double_t meson_PX, meson_PY, meson_PZ, meson_E;
	Double_t mu1_PX, mu1_PY, mu1_PZ, mu1_E;
	Double_t mu2_PX, mu2_PY, mu2_PZ, mu2_E;
	
	Double_t mReco;
	
	for(int cnt=0; cnt<T->GetEntries(); cnt++){
		
		cout << "___2:" << cnt << endl;
		T->GetEntry(cnt);
		
		T->SetBranchAddress("B_PX",&B_PX);
		T->SetBranchAddress("B_PY",&B_PY);
		T->SetBranchAddress("B_PZ",&B_PZ);
		T->SetBranchAddress("B_E",&B_E);
		
		T->SetBranchAddress("N_PX",&N_PX);
		T->SetBranchAddress("N_PY",&N_PY);
		T->SetBranchAddress("N_PZ",&N_PZ);
		T->SetBranchAddress("N_E",&N_E);
		T->SetBranchAddress("N_PT",&N_PT);
		
		T->SetBranchAddress("mu1_PX",&mu1_PX);
		T->SetBranchAddress("mu1_PY",&mu1_PY);
		T->SetBranchAddress("mu1_PZ",&mu1_PZ);
		T->SetBranchAddress("mu1_E",&mu1_E);
		
		T->SetBranchAddress("meson_PX",&meson_PX);
		T->SetBranchAddress("meson_PY",&meson_PY);
		T->SetBranchAddress("meson_PZ",&meson_PZ);
		T->SetBranchAddress("meson_E",&meson_E);
		
		// -----------------------------------------
		
		T->SetBranchAddress("pi_PX",&pi_PX);
		T->SetBranchAddress("pi_PY",&pi_PY);
		T->SetBranchAddress("pi_PZ",&pi_PZ);
		T->SetBranchAddress("pi_E",&pi_E);
		
		T->SetBranchAddress("mu2_PX",&mu2_PX);
		T->SetBranchAddress("mu2_PY",&mu2_PY);
		T->SetBranchAddress("mu2_PZ",&mu2_PZ);
		T->SetBranchAddress("mu2_E",&mu2_E);

		TLorentzVector B_P(B_PX, B_PY, B_PZ, B_E);
		TLorentzVector N_P(N_PX, N_PY, N_PZ, N_E);
		TLorentzVector pi_P(pi_PX, pi_PY, pi_PZ, pi_E);
		TLorentzVector meson_P(meson_PX, meson_PY, meson_PZ, meson_E);
		TLorentzVector mu1_P(mu1_PX, mu1_PY, mu1_PZ, mu1_E);
		TLorentzVector mu2_P(mu2_PX, mu2_PY, mu2_PZ, mu2_E);


		// Recontructed mass of B
		TLorentzVector tot_P = pi_P + mu1_P + mu2_P + meson_P;
		mReco = tot_P.Mag();
		//mReco = sqrt(mReco);
		h5->Fill(mReco);
		
		
		
		

		TVector3 B_P_Boost = B_P.BoostVector();
		//TVector3 N_P_Boost = N_P.BoostVector();
		//N_P.Boost(-B_P_Boost);
		meson_P.Boost(-B_P_Boost);
		mu1_P.Boost(-B_P_Boost);
		mu2_P.Boost(-B_P_Boost);
		//mu2_P.Boost(-N_P_Boost);
		
		h2->Fill(mu1_P.Phi()*180./pi, mu2_P.Phi()*180./pi);
		h3->Fill(mu1_P.Eta(),mu2_P.Eta());
		h4->Fill(mu1_P.Theta()*180./pi, mu2_P.Theta()*180./pi);
		
		h6->Fill(N_P.Theta()*180./pi, meson_P.Theta()*180./pi);
		h7->Fill(N_P.Theta()*180./pi, mu1_P.Theta()*180./pi);
		
		h81->Fill(N_P.Angle(meson_P.Vect())*180./pi);
		h82->Fill(N_P.Angle(mu1_P.Vect())*180./pi);
		h83->Fill(meson_P.Angle(mu1_P.Vect())*180./pi);
		
		h9->Fill(mu1_P.Angle(mu2_P.Vect())*180./pi);
		
		h10->Fill(N_PT,mu1_P.Angle(mu2_P.Vect())*180./pi);
	
	}
	
	
	
	TString ODIRNAME = "./analplot_"+HNL_id_s+"_cB"+cBflag_s+"_nomeson"+std::to_string(no3mesonflag);
	
	
	c2->cd();
	h2->GetXaxis()->SetTitle("#phi(#mu_{1})");
	h2->GetYaxis()->SetTitle("#phi(#mu_{2})");
	h2->Draw("colz");
	c2->SaveAs(ODIRNAME+"/mu1mu2phi_plot.root");
	
	c3->cd();
	h3->GetXaxis()->SetTitle("#eta(#mu_{1})");
	h3->GetYaxis()->SetTitle("#eta(#mu_{2})");
	h3->Draw("colz");
	c3->SaveAs(ODIRNAME+"/mu1mu2eta_plot.root");
	
	c4->cd();
	h4->GetXaxis()->SetTitle("#theta(#mu_{1})");
	h4->GetYaxis()->SetTitle("#theta(#mu_{2})");
	h4->Draw("colz");
	c4->SaveAs(ODIRNAME+"/mu1mu2theta_plot.root");
	
	c5->cd();
	h5->GetXaxis()->SetTitle("Reco m_{B} [GeV/c^{2}]");
	h5->Draw("colz");
	c5->SaveAs(ODIRNAME+"/mBReco.root");
	
	c6->cd();
	h6->GetXaxis()->SetTitle("#theta(N)");
	h6->GetYaxis()->SetTitle("#theta(meson)");
	h6->Draw("colz");
	c6->SaveAs(ODIRNAME+"/Nmesontheta_plot.root");
	
	c7->cd();
	h7->GetXaxis()->SetTitle("#theta(N)");
	h7->GetYaxis()->SetTitle("#theta(#mu_{1})");
	h7->Draw("colz");
	c7->SaveAs(ODIRNAME+"/Nmu1theta_plot.root");
	
	
	c8->cd();
	h81->GetXaxis()->SetTitle("Angle between vectors");
	h81->SetLineColor(kBlack);  h81->SetFillColor(kBlack);  //h81->SetFillStyle(3354);
	h82->SetLineColor(kBlue); h82->SetFillColor(kBlue);  h82->SetFillStyle(3325);
	h83->SetLineColor(kRed);h83->SetFillColor(kRed);  h83->SetFillStyle(3354);
	h81->Draw("HIST"); 		
	h82->Draw("HISTSAME");	
	h83->Draw("HISTSAME");	
	
	
	 auto legend = new TLegend(0.1,0.7,0.48,0.9);
     //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
	
	legend->AddEntry(h81,"N and meson","L");
	legend->AddEntry(h82,"N and #mu_{1}","L");
	legend->AddEntry(h83,"meson and #mu_{1}","L");
	
	
	legend->Draw();
   
	c8->SaveAs(ODIRNAME+"/mothersthetas_plot.root");
	
	
	c9->cd();
	h9->GetXaxis()->SetTitle("Angle between vectors");
	h9->Draw("HIST"); 		
	c9->SaveAs(ODIRNAME+"/muonsangle_plot.root");
	//TVector3 lab1_P_Boost = lab1_P.BoostVector();
	
	c10->cd();
	h10->GetXaxis()->SetTitle("Angle between vectors");
	h10->Draw("COLZ"); 		
	c10->SaveAs(ODIRNAME+"/NPT_muonsangle_corr.root");
	
	
	
	
	

}
	

