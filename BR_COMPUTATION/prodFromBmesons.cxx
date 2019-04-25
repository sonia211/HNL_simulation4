#include "partialWidths.h"
#include "Config.h"
#include "HNL.h"
#include "Lepton.h"
#include "Logger.h"
#include "Meson.h"
#include "auxfunctions.h"
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

#include <chrono>
#include <thread>


// ------- Tool functions
Double_t kallen(Double_t a, Double_t b, Double_t c) {
	//std::cout<<"kallen " << pow(a,2) + pow(b,2) + pow(c,2) - 2*(a*b + b*c + c*a) << std::endl;
	
	return pow(a,2) + pow(b,2) + pow(c,2) - 2*(a*b + b*c + c*a);
}

Double_t Gamma(Double_t eta, Double_t yhp, Double_t yl, Double_t yN) {
	//std::cout<<"Gamma " << sqrt(kallen(1, pow(yhp, 2), eta)) * sqrt(kallen(eta, pow(yN, 2), pow(yl, 2))) << std::endl;
	if (kallen(1, pow(yhp, 2), eta) < 0) std::cout << " _____kallen(1, pow(yhp, 2), eta) < 0_____" << std::endl;
	if (kallen(eta, pow(yN, 2), pow(yl, 2)) < 0){
		 std::cout << " _____kallen(eta, pow(yN, 2), pow(yl, 2)) < 0_____" << std::endl;
		 std::cout << " eta " << eta << std::endl;
		 std::cout << " yhp " << yhp << std::endl;
		 std::cout << " yl " << yl << std::endl;
		 std::cout << " yN " << yN << std::endl;
	 }
	return sqrt(abs(kallen(1, pow(yhp, 2), eta))) * sqrt(abs(kallen(eta, pow(yN, 2), pow(yl, 2))));
	//return kallen(1, pow(yhp, 2), eta) * kallen(eta, pow(yN, 2), pow(yl, 2));
}

Double_t Gminus(Double_t eta, Double_t yhp, Double_t yl, Double_t yN) {
	//std::cout<<"Gamma " << sqrt(kallen(1, pow(yhp, 2), eta)) * sqrt(kallen(eta, pow(yN, 2), pow(yl, 2))) << std::endl;
	return eta*(pow(yN, 2) +  pow(yl, 2)) - pow((pow(yN, 2) -  pow(yl, 2)),2) ;
}


// ------ Meson form factors
Double_t compute_fplus(Double_t q2) {
	return 1;
}

Double_t compute_fzero(Double_t q2) {
	return 1;
}

// ++++++++++++++++ COMPUTATIONS FUNCTIONS +++++++++++++++++++++++++++++

Double_t compute_fP1(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_) {
	
		unsigned int BITS = cfg->getBITS();
	
	Double_t ml = l.getMass(); 
	Double_t mh_ = meson.getMass(); Double_t mhp = mesonp.getMass();
	Quark_Type u = meson.getU(); Quark_Type d = meson.getD();
	
	
	
	
	// Get quarks flavours to apply corresponding V_CKM
	
	Double_t mN = N.getMass();
	Double_t U2 = N.getAngle();
	
	Double_t q2_ = eta_ * pow(mh_,2);
	mpfr_t yhp, yl, yN, mh, q2, eta;
	// initialisation
	mpfr_init2(yhp, BITS); 
	mpfr_init2(yl, BITS); 
	mpfr_init2(yN, BITS);
	mpfr_init2(mh, BITS);
	mpfr_init2(q2, BITS);
	mpfr_init2(eta, BITS);
	
	// set values
	mpfr_set_d(yhp, mhp, MPFR_RNDD);
	mpfr_set_d(yl, ml, MPFR_RNDD);
	mpfr_set_d(yN, mN, MPFR_RNDD);
	mpfr_set_d(mh, mh_, MPFR_RNDD);
	mpfr_set_d(q2, q2_, MPFR_RNDD);
	mpfr_set_d(eta, eta_, MPFR_RNDD);
	
	mpfr_div(yhp, yhp, mh, MPFR_RNDD);
	mpfr_div(yl, yl, mh, MPFR_RNDD);
	mpfr_div(yN, yN, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD); // eta = q2 / mh2
	
	// Compute form factor for input q2
	mpfr_t fplus2;
	mpfr_init2(fplus2, BITS); 
	mpfr_set_d(fplus2, compute_fplus(q2_), MPFR_RNDD);
	mpfr_pow_ui(fplus2, fplus2, 2, MPFR_RNDD);
	
	//Compute Gamma3 term
	mpfr_t Gamma3;
	mpfr_init2(Gamma3, BITS); 
	Double_t Gamma_ = Gamma(mpfr_get_d(eta, MPFR_RNDD), mpfr_get_d(yhp, MPFR_RNDD), mpfr_get_d(yl, MPFR_RNDD), mpfr_get_d(yN, MPFR_RNDD));
	mpfr_set_d(Gamma3, Gamma_, MPFR_RNDD);
	mpfr_pow_ui(Gamma3, Gamma3, 3, MPFR_RNDD);
		//std::cout<<"__fPq : Gama3_" << pow(Gamma_,3) <<std::endl; 
	
	//Compute the whoe function, then divide it by eta 3
	mpfr_t eta3; 
	mpfr_init2(eta3, BITS); 
	mpfr_pow_ui(eta3, eta, 3, MPFR_RNDD);
	
	//std::cout << "eta: " << q2_/pow(mh_,2) << std::endl;
	//std::cout << "_eta3: " << pow(q2_/pow(mh_,2),3) << std::endl;
	//std::cout << "eta3: " << mpfr_get_d(eta3,MPFR_RNDD) << std::endl;
	
	
	//std::cout << "eta3: " << mpfr_get_d(eta3,MPFR_RNDD) << std::endl;
	
	mpfr_t res; 
	mpfr_init2(res, BITS); 
	
	//std::cout << "Gamma3: " << mpfr_get_d(Gamma3,MPFR_RNDD) << std::endl;
	//std::cout << "fplus2: " << mpfr_get_d(fplus2,MPFR_RNDD) << std::endl;
	//std::cout << "3*eta3: " << mpfr_get_d(eta3,MPFR_RNDD) << std::endl;
	
	mpfr_mul(res, fplus2, Gamma3, MPFR_RNDD);
	
	//std::cout << "res 1: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	mpfr_div(res, res, eta3, MPFR_RNDD); //////////////////////////////////
	mpfr_div_ui(res, res, 3, MPFR_RNDD);
	
	//std::cout << "res 2: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	//mpfr_div(res, res, 3., MPFR_RNDD);
	
	return mpfr_get_d(res, MPFR_RNDD);
									
}

Double_t compute_fP2(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_) {
	
	unsigned int BITS = cfg->getBITS();
	
	Double_t ml = l.getMass(); 
	Double_t mh_ = meson.getMass(); Double_t mhp = mesonp.getMass();
	Quark_Type U = meson.getU(); Quark_Type D = meson.getD();
	
	// Get quarks flavours to apply corresponding V_CKM
	
	Double_t mN = N.getMass();
	Double_t U2 = N.getAngle();
	
	Double_t q2_ = eta_ * pow(mh_,2);
	
	mpfr_t yhp, yl, yN, mh, q2, eta;
	// initialisation
	mpfr_init2(yhp, BITS); 
	mpfr_init2(yl, BITS); 
	mpfr_init2(yN, BITS);
	mpfr_init2(mh, BITS);
	mpfr_init2(q2, BITS);
	mpfr_init2(eta, BITS);
	
	// set values
	mpfr_set_d(yhp, mhp, MPFR_RNDD);
	mpfr_set_d(yl, ml, MPFR_RNDD);
	mpfr_set_d(yN, mN, MPFR_RNDD);
	mpfr_set_d(mh, mh_, MPFR_RNDD);
	mpfr_set_d(q2, q2_, MPFR_RNDD);
	mpfr_set_d(eta, eta_, MPFR_RNDD);
	
	mpfr_div(yhp, yhp, mh, MPFR_RNDD);
	mpfr_div(yl, yl, mh, MPFR_RNDD);
	mpfr_div(yN, yN, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD); // eta = q2 / mh2
	
	// Compute form factor for input q2
	mpfr_t fplus2;
	mpfr_init2(fplus2, BITS); 
	mpfr_set_d(fplus2, compute_fplus(q2_), MPFR_RNDD);
	mpfr_pow_ui(fplus2, fplus2, 2, MPFR_RNDD);
	
	//Compute Gamma term
	mpfr_t Gamma_m;
	mpfr_init2(Gamma_m, BITS); 
	Double_t Gamma_ = Gamma(mpfr_get_d(eta, MPFR_RNDD), mpfr_get_d(yhp, MPFR_RNDD), mpfr_get_d(yl, MPFR_RNDD), mpfr_get_d(yN, MPFR_RNDD));
	mpfr_set_d(Gamma_m, Gamma_, MPFR_RNDD);
		//std::cout<<"__fP2 : Gama_" << Gamma_ <<std::endl; 
	//Compute Gminus term
	mpfr_t Gminus_m;
	mpfr_init2(Gminus_m, BITS); 
	Double_t Gminus_ = Gminus(mpfr_get_d(eta, MPFR_RNDD), mpfr_get_d(yhp, MPFR_RNDD), mpfr_get_d(yl, MPFR_RNDD), mpfr_get_d(yN, MPFR_RNDD));
	mpfr_set_d(Gminus_m, Gminus_, MPFR_RNDD);
		//std::cout<<"__fP2 : Gminus_" << Gminus_ <<std::endl;
	
	//Compute kallen(1,yhp2,eta) term
	mpfr_t kallen_m;
	mpfr_init2(kallen_m, BITS); 
	Double_t kallen_ = kallen(1., pow(mpfr_get_d(yhp, MPFR_RNDD),2), mpfr_get_d(eta, MPFR_RNDD));
	mpfr_set_d(kallen_m, kallen_, MPFR_RNDD);
		//std::cout<<"__fP2 : kallen_" << kallen_ <<std::endl; 
	
	//Compute the whole function, then divide it by 2*eta3
	mpfr_t eta3; 
	mpfr_init2(eta3, BITS); 
	mpfr_pow_ui(eta3, eta, 3, MPFR_RNDD);
	
	
	
	//std::cout << "eta3: " << mpfr_get_d(eta3,MPFR_RNDD) << std::endl;
	
	mpfr_t res; 
	mpfr_init2(res, BITS); 
	
	
	mpfr_mul(res, fplus2, Gamma_m, MPFR_RNDD);
		//std::cout << "res 1: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	mpfr_mul(res, res, Gminus_m, MPFR_RNDD);
		//std::cout << "res 2: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	mpfr_mul(res, res, kallen_m, MPFR_RNDD);
	
		//std::cout << "res 3: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	mpfr_div(res, res, eta3, MPFR_RNDD); /////////////////////////////
	mpfr_div_ui(res, res, 2, MPFR_RNDD);
	
		//std::cout << "res 4: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	//mpfr_div(res, res, 3., MPFR_RNDD);
	
	return mpfr_get_d(res, MPFR_RNDD);
									
}

Double_t compute_fP3(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_) {
	
	unsigned int BITS = cfg->getBITS();
	
	Double_t ml = l.getMass(); 
	Double_t mh_ = meson.getMass(); Double_t mhp = mesonp.getMass();
	Quark_Type u = meson.getU(); Quark_Type d = meson.getD();
	
	// Get quarks flavours to apply corresponding V_CKM
	
	Double_t mN = N.getMass();
	Double_t U2 = N.getAngle();
	
	Double_t q2_ = eta_ * pow(mh_,2);
	
	mpfr_t yhp, yl, yN, mh, q2, eta;
	// initialisation
	mpfr_init2(yhp, BITS); 
	mpfr_init2(yl, BITS); 
	mpfr_init2(yN, BITS);
	mpfr_init2(mh, BITS);
	mpfr_init2(q2, BITS);
	mpfr_init2(eta, BITS);
	
	// set values
	mpfr_set_d(yhp, mhp, MPFR_RNDD);
	mpfr_set_d(yl, ml, MPFR_RNDD);
	mpfr_set_d(yN, mN, MPFR_RNDD);
	mpfr_set_d(mh, mh_, MPFR_RNDD);
	mpfr_set_d(q2, q2_, MPFR_RNDD);
	mpfr_set_d(eta, eta_, MPFR_RNDD);
	
	mpfr_div(yhp, yhp, mh, MPFR_RNDD);
	mpfr_div(yl, yl, mh, MPFR_RNDD);
	mpfr_div(yN, yN, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD);
	//mpfr_div(eta, eta, mh, MPFR_RNDD); // eta = q2 / mh2
	
	// Compute form factor for input q2
	mpfr_t fplus2;
	mpfr_init2(fplus2, BITS); 
	mpfr_set_d(fplus2, compute_fplus(q2_), MPFR_RNDD);
	mpfr_pow_ui(fplus2, fplus2, 2, MPFR_RNDD);
	
	//Compute Gamma term
	mpfr_t Gamma_m;
	mpfr_init2(Gamma_m, BITS); 
	Double_t Gamma_ = Gamma(mpfr_get_d(eta, MPFR_RNDD), mpfr_get_d(yhp, MPFR_RNDD), mpfr_get_d(yl, MPFR_RNDD), mpfr_get_d(yN, MPFR_RNDD));
	mpfr_set_d(Gamma_m, Gamma_, MPFR_RNDD);
	
	//Compute Gminus term
	mpfr_t Gminus_m;
	mpfr_init2(Gminus_m, BITS); 
	Double_t Gminus_ = Gminus(mpfr_get_d(eta, MPFR_RNDD), mpfr_get_d(yhp, MPFR_RNDD), mpfr_get_d(yl, MPFR_RNDD), mpfr_get_d(yN, MPFR_RNDD));
	mpfr_set_d(Gminus_m, Gminus_, MPFR_RNDD);
		//std::cout<<"__fP3 : Gminus_" << Gminus_ <<std::endl;
	
	//Compute (1-yhp^2)^2 term
	mpfr_t temp;
	mpfr_init2(temp, BITS); 
	mpfr_pow_ui(temp, yhp, 2, MPFR_RNDD);
	mpfr_ui_sub(temp, 1, temp, MPFR_RNDD);
	mpfr_pow_ui(temp, temp, 2, MPFR_RNDD);
	
	//Compute the whole function, then divide it by 2*eta3
	mpfr_t eta3; 
	mpfr_init2(eta3, BITS); 
	mpfr_pow_ui(eta3, eta, 3, MPFR_RNDD);
	
	
	
		//std::cout << "eta3: " << mpfr_get_d(eta3,MPFR_RNDD) << std::endl;
	
	mpfr_t res; 
	mpfr_init2(res, BITS); 
	
	
	mpfr_mul(res, fplus2, Gamma_m, MPFR_RNDD);
		//std::cout << "res 1: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	mpfr_mul(res, res, Gminus_m, MPFR_RNDD);
		//std::cout << "res 2: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	mpfr_mul(res, res, temp, MPFR_RNDD);
	
		//std::cout << "res 3: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	mpfr_div(res, res, eta3, MPFR_RNDD); ///////////////
	mpfr_div_ui(res, res, 2, MPFR_RNDD);
	
		//std::cout << "res 4: " << mpfr_get_d(res,MPFR_RNDD) << std::endl;
	
	//mpfr_div(res, res, 3., MPFR_RNDD);
	
	return mpfr_get_d(res, MPFR_RNDD);
									
}


// +++++++++++++++++ INTEGRATION FUNCTION ++++++++++++++++++++++++++++++

Double_t integral_fP(Double_t a, Double_t b, Double_t nsteps, std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, int fct){
	
	
	unsigned int BITS = cfg->getBITS();
	
	Double_t step = (b-a)/nsteps;
	if(step<0.){
			std::cout << "step: " << step << std::endl;
			std::cout << "mN: " << N.getMass() << std::endl;
		}
	mpfr_t res;
	mpfr_init2(res, BITS); 
	mpfr_set_d(res, 0., MPFR_RNDD);
	
	//std::cout << "step: " << step << std::endl;
	
	//loop on nsteps steps and add integral using trapezoidal computation @each step
	Double_t x1, x2, x3; 
	Double_t fstep_, f1, f2, f3; 
	Double_t eta1, eta2, eta3;
	Double_t mh_ = meson.getMass();
	for(int i(0); i<nsteps; ++i){
		eta1 = a+i*step;
		eta2 = a+(i+0.5)*step;
		eta3 = a+(i+1.)*step;
		
		if(fct==1){
			f1=compute_fP1(cfg, N, l, meson, mesonp, eta1);
			f2=compute_fP1(cfg, N, l, meson, mesonp, eta2);
			f3=compute_fP1(cfg, N, l, meson, mesonp, eta3);
		}
		
		else if(fct==2){
			f1=compute_fP2(cfg, N, l, meson, mesonp, eta1);
			f2=compute_fP2(cfg, N, l, meson, mesonp, eta2);
			f3=compute_fP2(cfg, N, l, meson, mesonp, eta3);
		}
		
		else if(fct==3){
			f1=compute_fP3(cfg, N, l, meson, mesonp, eta1);
			f2=compute_fP3(cfg, N, l, meson, mesonp, eta2);
			f3=compute_fP3(cfg, N, l, meson, mesonp, eta3);
		}
		
		
		fstep_ = 1./6*f1 + 4./6*f2 + 1./6*f3;
		
		
		
		mpfr_t fstep;
		mpfr_init2(fstep, BITS); 
		mpfr_set_d(fstep, fstep_, MPFR_RNDD);
		
		mpfr_add(res, res, fstep, MPFR_RNDD);
	}
	
	return mpfr_get_d(res, MPFR_RNDD);
}


// +++++++++++++++++++++++++ PARTIAL WIDTH ++++++++++++++++++++++++++++++

Double_t pw_prodFromBmeson(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp){
	
	mpfr_t fermiC, fermiCsq, pi;
	unsigned int BITS = cfg->getBITS();
	mpfr_init2(fermiC, BITS);
	mpfr_init2(fermiCsq, BITS);
	mpfr_init2(pi, BITS);
	cfg->getFermiC(fermiC);
	cfg->getPi(pi);
	
	/** Get high precision values **/
	Double_t ml = l.getMass(); 
	Double_t mh_ = meson.getMass(); Double_t mhp = mesonp.getMass();
	Double_t mN = N.getMass();
	Double_t U2_ = N.getAngle();
	
	// Compute corresponding V_CKM
	const Quark_Type Din = meson.getD(); const Quark_Type Dout = mesonp.getD();
	
	//Double_t Vud_ = get_VCKM(Din,Dout); 
	//Double_t Vud_ = cfg->getVUDsq(Din, Dout); 
	Double_t Vud_ = 1.;
	//std::cout<<"meson name: " << meson.getName() << std::endl;
	//std::cout<<"mesonp name: " << mesonp.getName() << std::endl;
	std::cout << "VCKM elmt: " << Vud_ << std::endl;
	
	mpfr_t yhp, yl, yN, mh, q2, eta, U2, Vud2;
	// initialisation
	mpfr_init2(yhp, BITS); 
	mpfr_init2(yl, BITS); 
	mpfr_init2(yN, BITS);
	mpfr_init2(mh, BITS);
	//mpfr_init2(q2, BITS);
	//mpfr_init2(eta, BITS);
	mpfr_init2(U2, BITS);
	mpfr_init2(Vud2, BITS);
	
	// set values
	mpfr_set_d(yhp, mhp, MPFR_RNDD);
	mpfr_set_d(yl, ml, MPFR_RNDD);
	mpfr_set_d(yN, mN, MPFR_RNDD);
	mpfr_set_d(mh, mh_, MPFR_RNDD);
	
	//mpfr_set_d(q2, q2_, MPFR_RNDD);
	//mpfr_set_d(eta, q2_, MPFR_RNDD);
	
	mpfr_set_d(U2, U2_, MPFR_RNDD);
	mpfr_set_d(Vud2, Vud_, MPFR_RNDD);
	mpfr_pow_ui(Vud2, Vud2, 2, MPFR_RNDD);
	
	/** Compute factor **/
	mpfr_t factor, tmp;
	mpfr_init2(factor, BITS);
	mpfr_init2(tmp, BITS);
	
	mpfr_pow_ui(factor, fermiC, 2, MPFR_RNDD);
	mpfr_pow_ui(tmp, mh, 5, MPFR_RNDD);
	mpfr_mul(factor, factor, tmp, MPFR_RNDD);
	mpfr_mul(factor, factor, U2, MPFR_RNDD);
	mpfr_mul(factor, factor, Vud2, MPFR_RNDD);
	mpfr_pow_ui(tmp, pi, 3, MPFR_RNDD);
	mpfr_div(factor, factor, tmp, MPFR_RNDD);
	mpfr_div_ui(factor, factor, 64, MPFR_RNDD);
	
	
	/** Compute 3 parts of the integral **/
	
	Double_t IP_(0);
	Double_t bmin = pow(ml/mh_ + mN/mh_,2); Double_t bmax = pow(1-(mhp/mh_),2);
	for(int i(1); i<=3; ++i){
		IP_ += integral_fP(bmin, bmax, 5000, cfg, N, l, meson, mesonp, i);
		std::cout << "INTEGRAL STEP " << i << " : " << IP_ << std::endl;
	}
	
	/** Compute whole PW value **/
	mpfr_t IP;
	mpfr_init2(IP, BITS); 
	mpfr_set_d(IP, IP_, MPFR_RNDD);
	
	mpfr_mul(factor, factor, IP, MPFR_RNDD);
	
	mpfr_clear(Vud2);

	if(mpfr_get_d(factor, MPFR_RNDD)<0.) return 0.;
	else return mpfr_get_d(factor, MPFR_RNDD);
	
}




