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
#include <dirent.h>



/*************************************************************************************************/

vector<string> GetSubdirs_(size_t y,string magnet){
	vector<string> path_y;
	string year = to_string(y);
	cout << "year : " << year <<endl;

	//string path("/panfs/nanut/Dst2D0pi_mumu/TP4/Tuples/Data_pipi/"+year+"/");
	string path("/panfs/nanut/Dst2D0pi_mumu/Specialisation_Sonia/Tuples/Data_"+year+"/");
  
	const char *cstr = path.c_str();
	struct dirent *de;
	DIR *dr = opendir(cstr);
	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
	{ 
		printf("Could not open current directory" ); 
		//break; 
	}
	string n;
	while ((de = readdir(dr)) != NULL){
		 n=(de->d_name);
		//if(n!="." and n!=".."){
		if(n.substr(0,2)==magnet){
			path_y.push_back(n); std::cout<<"n"<<n<<std::endl; 
			//std::cout << "path_y" << n << std::endl;
		}	
	}

	closedir(dr);
	
	return path_y; 
}

TCanvas * PlotsYears(TString tuple = "D0pipiTuple", TString varname="D0_M", int min=1760, int max=1960){
	TCanvas *c = new TCanvas("c","canvas",800,600);
	TString tree(tuple+"/DecayTree");
       
	std::vector <vector<string>> path_MD(2);
	std::vector <vector<string>> path_MU(2);
	// Remplir path
	for (size_t y(0); y<2; y++){
		std::vector<string> path_y_MD=GetSubdirs_(y+2016,"MD");
		std::vector<string> path_y_MU=GetSubdirs_(y+2016,"MU");
		
		for (size_t j(0); j<path_y_MD.size(); j++)path_MD[y].push_back(path_y_MD[j]);
		for (size_t j(0); j<path_y_MU.size(); j++)path_MU[y].push_back(path_y_MU[j]);
		//std::cout<<"path_y["<<j+2016<<"] : "<<path_y[j];}

	}
	TChain T16_MD(tree); TChain T17_MD(tree);
	TChain T16_MU(tree); TChain T17_MU(tree);
	TChain All(tree);
	
	
	for (size_t y(0); y<2; y++){
		unsigned int year = y+2016;
		//std::cout<<"year : "<<year<<std::endl;
		//const string pathmc(path[][]);
		string motherpath("/panfs/nanut/Dst2D0pi_mumu/Specialisation_Sonia/Tuples/Data_"+to_string(year)+"/");
		//std::cout<<"path[y].size("<<path[y].size()<<std::endl;

		for (size_t s(0); s<path_MD[y].size(); s++){
			glob_t glob_MD;
			string path_ = path_MD[y][s];
			path_=motherpath+path_+"/";
			//std::cout << " path_" << path_ << std::endl;
			
			glob( (path_ + "*.root").c_str(), GLOB_NOSORT, NULL, &glob_MD);
			for (size_t i(0); i<glob_MD.gl_pathc; i++){
			
				TString filename(glob_MD.gl_pathv[i]);
				//std::cout << "filename:" << filename << std::endl;
				if (year==2016)T16_MD.Add(filename);
				if (year==2017)T17_MD.Add(filename);
				All.Add(filename);
				//std::cout<<"filename : "<< filename<<std::endl;
				//std::cout<<"Entries : "<<T17_MD.GetEntries()<<std::endl;
				//std::cout<<"glob_.gl_pathv["<<i<<"] = "<<glob_.gl_pathv[i]<<std::endl;
			}			
		}

		for (size_t s(0); s<path_MU[y].size(); s++){
			glob_t glob_MU;
			string path_ = path_MU[y][s];
			path_=motherpath+path_+"/";
			//std::cout << " path_" << path_ << std::endl;
			
			glob( (path_ + "*.root").c_str(), GLOB_NOSORT, NULL, &glob_MU);
			for (size_t i(0); i<glob_MU.gl_pathc; i++){
				TString filename(glob_MU.gl_pathv[i]);
				//std::cout << "filename:" << filename << std::endl;
				if (year==2016)T16_MU.Add(filename);
				if (year==2017){T17_MU.Add(filename); std::cout<<"filename : "<< filename<<std::endl;
				All.Add(filename);
				std::cout<<"Entries : "<<T17_MU.GetEntries()<<std::endl;}
				
				//std::cout<<"glob_.gl_pathv["<<i<<"] = "<<glob_.gl_pathv[i]<<std::endl;
			}			
		}

		

		
	}

	
	c->cd();
       
       	//gStyle->SetOptStat(0);
	/**	
	TH1D * h16D = new TH1D("h16D","",300,min, max);TH1D * h17D = new TH1D("h17D","",300,min, max);
	TH1D * h16U = new TH1D("h16U","",300,min, max);TH1D * h17U = new TH1D("h17U","",300,min, max);
	h16D->SetLineColor(2); h17D->SetLineColor(3);
	h16U->SetLineColor(4); h17U->SetLineColor(6);
	**/
	TH1D * h = new TH1D("h","",300,min, max);
	std::cout<<"\nbefore drawn \n\n";	
	All.Draw(varname+">>h",TCut(""),"hist");
	std::cout<<"\ndrawn \n\n";	
	//h15->SetLineWidth(2); h16->SetLineWidth(2); h17->SetLineWidth(2);
	
	/**
	//T16.Draw(varname+">>h16",TCut("1.*1./"+varname),"SAME");
	T16_MU.Draw(varname+">>h16U",TCut(""),"hist");
	T17_MU.Draw(varname+">>h17U",TCut(""),"SAMEhist");	
	T16_MD.Draw(varname+">>h16D",TCut(""),"SAMEhist");
	T17_MD.Draw(varname+">>h17D",TCut(""),"SAMEhist");
	
	//h16D->Scale(1/h16D->Integral("width")); h17D->Scale(1/h17D->Integral("width"));
	//h16U->Scale(1/h16U->Integral("width")); h17U->Scale(1/h17U->Integral("width"));
   	h16D->GetXaxis()->SetTitle(varname); h16D->GetYaxis()->SetTitle("Number of events");

	auto legend = new TLegend(0.5, 0.7, 0.9, 0.9);
	legend->AddEntry(h16D, "Data MD 2016", "lp");
	legend->AddEntry(h17D, "Data MD 2017", "lp");
	legend->AddEntry(h16U, "Data MU 2016", "lp");
	legend->AddEntry(h17U, "Data MU 2017", "lp");
	legend->Draw();	
	c->SaveAs("years_"+tuple+"_"+varname+".pdf");
	c->SaveAs("years_"+tuple+"_"+varname+".root");
	
	
	h16D->Scale(1/h16D->Integral("width")); h17D->Scale(1/h17D->Integral("width"));
	h16U->Scale(1/h16U->Integral("width")); h17U->Scale(1/h17U->Integral("width"));	
	TCanvas *c1 = new TCanvas("c1","canvas",800,600);
	c1->cd();
	T16_MU.Draw(varname+">>h16U",TCut(""),"hist");
	T17_MU.Draw(varname+">>h17U",TCut(""),"SAMEhist");	
	T16_MD.Draw(varname+">>h16D",TCut(""),"SAMEhist");
	T17_MD.Draw(varname+">>h17D",TCut(""),"SAMEhist");
	legend->Draw();	
	c1->SaveAs("years_"+tuple+"_"+varname+"norm.pdf");
	c1->SaveAs("years_"+tuple+"_"+varname+"norm.root");
	**/
	return c;
}

TCanvas * PlotsYearsMC(TString tuple = "D0pipiTuple", TString varname="D0_M", int min=1760, int max=1960){
	TCanvas *c = new TCanvas("c","canvas",800,600);
	TString tree(tuple+"/DecayTree");
       
	string pathmc("/panfs/nanut/Dst2D0pi_mumu/Specialisation_Sonia/Tuples/MC_mumu/");
	glob_t glob_r_mc; 
	glob( (pathmc + "MD_all/*.root").c_str(), GLOB_NOSORT, NULL, &glob_r_mc);
	TChain TMC(tree);
	for (size_t i(0); i<glob_r_mc.gl_pathc; i++){
		TString filename(glob_r_mc.gl_pathv[i]);	
		TMC.Add(filename);
		//std::cout<<"glob_r_mc.gl_pathv["<<i<<"] = "<<glob_r_mc.gl_pathv[i]<<std::endl;	
	}
	glob( (pathmc + "MU_all/*.root").c_str(), GLOB_NOSORT, NULL, &glob_r_mc);
	//TChain TMC(tree);
	for (size_t i(0); i<glob_r_mc.gl_pathc; i++){
		TString filename(glob_r_mc.gl_pathv[i]);	
		TMC.Add(filename);
		//std::cout<<"glob_r_mc.gl_pathv["<<i<<"] = "<<glob_r_mc.gl_pathv[i]<<std::endl;	
	}
	
	
	TH1D * h = new TH1D("h","",300,min, max);TH1D * h2 = new TH1D("h2","",300,min, max);
	std::cout<<"\nbefore drawn \n\n";	
	//TMC.Draw(varname+">>h",TCut(""),"hist");
	TMC.Draw(varname+">>h2",TCut("Dst_BKGCAT==0 || Dst_BKGCAT==50"),"hist");
	std::cout<<"\ndrawn \n\n";	
	//h15->SetLineWidth(2); h16->SetLineWidth(2); h17->SetLineWidth(2);
	
	/**
	//T16.Draw(varname+">>h16",TCut("1.*1./"+varname),"SAME");
	T16_MU.Draw(varname+">>h16U",TCut(""),"hist");
	T17_MU.Draw(varname+">>h17U",TCut(""),"SAMEhist");	
	T16_MD.Draw(varname+">>h16D",TCut(""),"SAMEhist");
	T17_MD.Draw(varname+">>h17D",TCut(""),"SAMEhist");
	
	//h16D->Scale(1/h16D->Integral("width")); h17D->Scale(1/h17D->Integral("width"));
	//h16U->Scale(1/h16U->Integral("width")); h17U->Scale(1/h17U->Integral("width"));
   	h16D->GetXaxis()->SetTitle(varname); h16D->GetYaxis()->SetTitle("Number of events");

	auto legend = new TLegend(0.5, 0.7, 0.9, 0.9);
	legend->AddEntry(h16D, "Data MD 2016", "lp");
	legend->AddEntry(h17D, "Data MD 2017", "lp");
	legend->AddEntry(h16U, "Data MU 2016", "lp");
	legend->AddEntry(h17U, "Data MU 2017", "lp");
	legend->Draw();	
	c->SaveAs("years_"+tuple+"_"+varname+".pdf");
	c->SaveAs("years_"+tuple+"_"+varname+".root");
	
	
	h16D->Scale(1/h16D->Integral("width")); h17D->Scale(1/h17D->Integral("width"));
	h16U->Scale(1/h16U->Integral("width")); h17U->Scale(1/h17U->Integral("width"));	
	TCanvas *c1 = new TCanvas("c1","canvas",800,600);
	c1->cd();
	T16_MU.Draw(varname+">>h16U",TCut(""),"hist");
	T17_MU.Draw(varname+">>h17U",TCut(""),"SAMEhist");	
	T16_MD.Draw(varname+">>h16D",TCut(""),"SAMEhist");
	T17_MD.Draw(varname+">>h17D",TCut(""),"SAMEhist");
	legend->Draw();	
	c1->SaveAs("years_"+tuple+"_"+varname+"norm.pdf");
	c1->SaveAs("years_"+tuple+"_"+varname+"norm.root");
	**/
	return c;
}








