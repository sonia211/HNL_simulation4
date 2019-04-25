//  cHNLdecay  --  calculate decay widths of Heavy Neutral Leptons
//  Copyright (C) 2018 - Fabian A.J. Thiele, <fabian.thiele@posteo.de>
//
//  This file is part of cHNLdecay.
//
//  cHNLdecay is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  cHNLdecay is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TObjString.h"

#include "HNL.h"
#include "Lepton.h"
#include "Meson.h"
#include "Quark.h"

#include "Config.h"
#include "Logger.h"
#include "ParticleCatalogue.h"
#include "auxfunctions.h"
#include "partialWidths.h"
#include "prodFromBmesons.h"
#include "plots.h"
#include <fstream>
#include <iostream>
#include <getopt.h>
#include <gmp.h>
#include <iomanip>
#include <iostream>
#include <mpfr.h>
#include <stdlib.h>
#include <yaml-cpp/yaml.h>



Level gLOGLEVEL;
int main(int argc, char **argv) {
	auto cfg = std::make_shared<Config>(); // set BITS and initialize constants

	// read yml file containing values of the scan
	YAML::Node lconf = YAML::LoadFile("../cfg_files/cfg_scan.yml");

	// how to read data
	std::vector<double> mNvec = lconf["mNvec"].as<std::vector<double>>();
	std::vector<double> U2vec = lconf["U2vec"].as<std::vector<double>>();
	
	std::cout << "mNvec size " << mNvec.size() << std::endl; 
	//YAML::Node config = YAML::LoadFile("sample.yaml");
	// initialize the variables that define our HNL
	Double_t mN = 0;
	Double_t U2 = 0;
	std::vector<Lepton> mixes_with;
	bool majorana = true;

	// variables used for searching for angle / parsing file for angles
	bool isLoad = false;
	TString loadPath;
	Double_t ctau = 0;
	//std::cout << " debug 1 " << std::endl; 

	// sensible default for loglevel
	gLOGLEVEL = Level::INFO;

	ParticleCatalogue pc;

	std::vector<Lepton> all_leptons = pc.getAllLeptons();
	std::vector<Meson> mesons = pc.getAllMesons();
	
	//std::cout << " debug 2 " << std::endl; 
				//select particles 
	Double_t muonMass = 105.6583715;      // MeV
	Double_t electronMass = 0.5109989461; // MeV
	Double_t tauMass = 1776.82;           // MeV

	Lepton el = Lepton(11, electronMass);
	Lepton mu = Lepton(13, muonMass);
	Lepton tau = Lepton(15, tauMass);

	//Meson pi = pc.pi;
	Meson pi = Meson(211, 139.57018, 130.2, MesonType::pseudoscalar,
			Charge::charged, Quark_Type::up, Quark_Type::down);
	
	Meson D0 = Meson(411, 1869.62, 212, MesonType::pseudoscalar, Charge::neutral,
                    Quark_Type::charm, Quark_Type::up);
	
	Meson pi0 = Meson(111, 139.57018, 130.2, MesonType::pseudoscalar, Charge::neutral,
					Quark_Type::up, Quark_Type::up);
	// B mesons
	Meson B0 = Meson(211, 5279.61, 130, MesonType::pseudoscalar, Charge::neutral,
		   Quark_Type::down, Quark_Type::bottom);
	
	
	Meson B = Meson(521, 5279.29, 187, MesonType::pseudoscalar, Charge::charged,
			Quark_Type::up, Quark_Type::bottom);
	
	//Meson Bs = Meson(531, 5366.79, 228, MesonType::pseudoscalar, Charge::neutral,
	  //      Quark_Type::strange, Quark_Type::bottom);

	Meson Bc = Meson(541, 6275.1, 434, MesonType::pseudoscalar, Charge::charged,
			 Quark_Type::charm, Quark_Type::bottom);            
	
	
	//Meson B0 = Meson(511, 5279.29, 130.2, MesonType::pseudoscalar,
	  //       Charge::neutral, 
	

	mixes_with={mu};
            
            

	//std::ofstream ofile_pi_mu; ofile_pi_mu.open("../br_pi_mu.dat");
	//std::ofstream ofile_pi_el; ofile_pi_el.open("../br_pi_el.dat");
	std::ofstream ofile_prod_B0; ofile_prod_B0.open("../br_prod_B0.dat");
	std::ofstream ofile_prod_B;  ofile_prod_B.open("../br_prod_B.dat");
	std::ofstream ofile_prod_Bs; ofile_prod_Bs.open("../br_prod_Bs.dat");
	std::ofstream ofile_prod_Bc; ofile_prod_Bc.open("../br_prod_Bc.dat");
		
	// this is the HNL we configure via command line options. If it mixes with
	// multiple generations it can only assume mixing angle ratios 1:1:..:1
	
	for (int a(0); a<mNvec.size(); ++a){ // loop on masses
		mN=mNvec[a]*1000.;		// from GeV to MeV
		
		
		
		for (int b(0); b<U2vec.size(); ++b){ // loop on lifetimes
			U2=U2vec[b];
			std::cout << "mN: " << mN << std::endl;
			std::cout << "U2: " << U2 << std::endl;
			HNL N = HNL("HNL", mN, U2, mixes_with);
			N.setMajorana(majorana);
		
			
			
			Double_t pw_pi_mu = pw_charged_pseudoscalar_mesons(cfg, mu, pi, N);
			Double_t pw_pi_el = pw_charged_pseudoscalar_mesons(cfg, el, pi, N);
			
			//myfile << "Writing this to a file.\n";
			
			//std::cout << "pw_pi_mu: " << pw_pi_mu << " " << std::endl;	
			
			//ofile_pi_mu << pw_pi_mu << " " ;
			//ofile_pi_el << pw_pi_el << " " ;
	
	
			// Declare and compute all partial widths
			
			std::vector<std::vector<Double_t>> VCKM{{0.97427, 0.22534, 0.00351}, 
											{0.22520, 0.97344, 0.04120}, 
											{0.00867, 0.04040, 0.999146}};
			
			Double_t pw_prod_B0, pw_prod_B, pw_prod_Bs, pw_prod_Bc;
			
			std::cout << "B0 prod computation " << std::endl;
			pw_prod_B0=pow(VCKM[0][2],2)*pw_prodFromBmeson(cfg, N, mu, B0, pi);
			std::cout << "B prod computation " << std::endl;
			pw_prod_B=pow(VCKM[0][2],2)*pw_prodFromBmeson(cfg, N, mu, B, pi0);
			//pw_prod_Bs=pw_prodFromBmeson(cfg, N, mu, Bs, pi);
			std::cout << "Bc prod computation " << std::endl;
			pw_prod_Bc=pow(VCKM[0][2],2)*pw_prodFromBmeson(cfg, N, mu, Bc, D0);
			
			
			// Write in files
			
			ofile_prod_B0 << pw_prod_B0 << " " ;
			ofile_prod_B  << pw_prod_B  << " " ;
			//ofile_prod_Bs << pw_prod_Bs << " " ;
			ofile_prod_Bc << pw_prod_Bc << " " ;
			
			
		}// loop on masses
		//ofile_pi_mu << "\n";
		//ofile_pi_el << "\n";
		
		ofile_prod_B0 << "\n";
		ofile_prod_B  << "\n";
		//ofile_prod_Bs << "\n";
		ofile_prod_Bc << "\n";
	
	
	
	}// loop on lifetimes
	
		

	return EXIT_SUCCESS;
}
