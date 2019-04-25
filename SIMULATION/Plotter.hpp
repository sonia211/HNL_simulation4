#ifndef PLOTTER_H
#define PLOTTER_H

//#include <Plotter.hpp>
#include <fstream>
#include <iomanip>
#include <TChain.h>
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
//#include "boost/filesystem.hpp"
//namespace fs = boost::filesystem;
//using namespace std::tr2::sys;

#include <sys/types.h>

TCanvas * PlotTree(TString FILENAME, TString TREE, TString VARNAME, TString XNAME, TString YNAME, Double_t MIN=0., Double_t MAX=10000., bool logmode = false){
	
	TFile *F = new TFile(FILENAME, "open");
	TTree *T = new TTree();
	F->GetObject(TREE, T);
	
	TString OUTDIR("/home/bouchiba/PDM/pythia8240/rootexamples/output/");
	
	//TFile *OUTF   = new TFile(OUTDIR+VARNAME+"_plot.root", "recreate");
	TCanvas *c = new TCanvas("c"+VARNAME,VARNAME,800,600);
	c->cd();
	//Int_t nbins = (int)(MAX-MIN)*2;
	Int_t nbins = 100;
	TH1D* hist = new TH1D("h", "h", nbins, MIN, MAX);
	T->Draw(VARNAME+">>h");
	
	c->SaveAs(OUTDIR+VARNAME+"_plot.root");
	
	return c;
}


TCanvas * PlotFitTree(TString FILENAME, TString TREE, TString VARNAME, TString XNAME, TString YNAME, Double_t MIN=0., Double_t MAX=10000., bool logmode = false){
	
	TFile *F = new TFile(FILENAME, "open");
	TTree *T = new TTree();
	F->GetObject(TREE, T);
	
	TString OUTDIR("/home/bouchiba/PDM/pythia8240/rootexamples/output/");
	
	//TFile *OUTF   = new TFile(OUTDIR+VARNAME+"_plot.root", "recreate");
	TCanvas *c = new TCanvas("c"+VARNAME,VARNAME,800,600);
	c->cd();
	//Int_t nbins = (int)(MAX-MIN)*2;
	Int_t nbins = 100;
	TH1D* hist = new TH1D("h", "h", nbins, MIN, MAX);
	T->Draw(VARNAME+">>h");
	
	// ROOFIT PROCESS
	
	c->SaveAs(OUTDIR+VARNAME+"_plot.root");
	
	return c;
}






#endif

