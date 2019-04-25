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
Double_t pw_nualpha_lbeta_lbeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Lepton &beta,
                                const HNL &N) {
  return pw_nualpha_lbeta_lbeta(cfg, alpha, beta, N, 1);
}

Double_t pw_nualpha_lbeta_lbeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Quark &beta,
                                const HNL &N) {
  return pw_nualpha_lbeta_lbeta(cfg, alpha, beta, N, 3);
}


Double_t pw_nualpha_lbeta_lbeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Particle &beta,
                                const HNL &N, Double_t d_NZ) {
  if (not N.mixesWith(alpha))
    return 0;
  if (N.getMass() < 2. * beta.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiCsq, pi;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);

  cfg->getFermiCsq(fermiCsq);
  cfg->getPi(pi);

  mpfr_t denominator, temp, xsq, factor, betamass, HNLmass, NZ, angle;

  mpfr_init2(temp, BITS);
  mpfr_init2(xsq, BITS);
  mpfr_init2(factor, BITS);
  mpfr_init2(betamass, BITS);
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(NZ, BITS);
  mpfr_init2(angle, BITS);
  mpfr_init2(denominator, BITS);

  mpfr_set_d(NZ, d_NZ, MPFR_RNDD);
  mpfr_set_d(betamass, beta.getMass(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_div(xsq, betamass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xsq, xsq, 2, MPFR_RNDD);

  // calculate first factors NZ * GF^2 * M^5 * U^2/(192*pi^3)
  mpfr_pow_ui(factor, HNLmass, 5, MPFR_RNDD);
  mpfr_mul(factor, factor, fermiCsq, MPFR_RNDD);
  mpfr_mul(factor, factor, NZ, MPFR_RNDD);
  mpfr_mul(factor, factor, angle, MPFR_RNDD);
  mpfr_pow_ui(denominator, pi, 3, MPFR_RNDD);
  mpfr_mul_ui(denominator, denominator, 192, MPFR_RNDD);
  mpfr_div(factor, factor, denominator, MPFR_RNDD);
  // end calculation first factors

  // pre-calculate square root of 1-4*x^2
  mpfr_t sq1m4x2;
  mpfr_init2(sq1m4x2, BITS);
  mpfr_mul_ui(sq1m4x2, xsq, 4, MPFR_RNDD);
  mpfr_ui_sub(sq1m4x2, 1, sq1m4x2, MPFR_RNDD);
  mpfr_sqrt(sq1m4x2, sq1m4x2, MPFR_RNDD);
  // end pre-calculation

  // calculate L(x) (logarithm function)
  mpfr_t L;
  mpfr_init2(L, BITS);
  mpfr_mul_ui(L, xsq, 3, MPFR_RNDD);
  mpfr_ui_sub(L, 1, L, MPFR_RNDD);
  mpfr_ui_sub(temp, 1, xsq, MPFR_RNDD);
  mpfr_mul(temp, temp, sq1m4x2, MPFR_RNDD);
  mpfr_sub(L, L, temp, MPFR_RNDD);
  mpfr_add_ui(temp, sq1m4x2, 1, MPFR_RNDD);
  mpfr_mul(denominator, xsq, temp, MPFR_RNDD);
  mpfr_div(L, L, denominator, MPFR_RNDD);
  mpfr_log(L, L, MPFR_RNDD);
  // end calculation L(x)

  mpfr_t weinberg;
  mpfr_init2(weinberg, BITS);
  mpfr_set_d(weinberg, 0.2223, MPFR_RNDD);

  mpfr_t c1, c2, c1_factor, c2_factor;
  mpfr_init2(c1, BITS);
  mpfr_init2(c2, BITS);
  mpfr_init2(c1_factor, BITS);
  mpfr_init2(c2_factor, BITS);

  if (alpha == beta) {
    mpfr_pow_ui(c1, weinberg, 2, MPFR_RNDD);
    mpfr_mul_ui(c1, c1, 8, MPFR_RNDD);
    mpfr_mul_ui(temp, weinberg, 4, MPFR_RNDD);
    mpfr_add(c1, c1, temp, MPFR_RNDD);
    mpfr_add_ui(c1, c1, 1, MPFR_RNDD);
    mpfr_div_ui(c1, c1, 4, MPFR_RNDD);

    mpfr_mul_ui(c2, weinberg, 2, MPFR_RNDD);
    mpfr_add_ui(c2, c2, 1, MPFR_RNDD);
    mpfr_mul(c2, weinberg, c2, MPFR_RNDD);
    mpfr_div_ui(c2, c2, 2, MPFR_RNDD);
  } else {
    mpfr_pow_ui(c1, weinberg, 2, MPFR_RNDD);
    mpfr_mul_ui(c1, c1, 8, MPFR_RNDD);
    mpfr_mul_ui(temp, weinberg, 4, MPFR_RNDD);
    mpfr_ui_sub(temp, 1, temp, MPFR_RNDD);
    mpfr_add(c1, c1, temp, MPFR_RNDD);
    mpfr_div_ui(c1, c1, 4, MPFR_RNDD);

    mpfr_mul_ui(c2, weinberg, 2, MPFR_RNDD);
    mpfr_sub_ui(c2, c2, 1, MPFR_RNDD);
    mpfr_mul(c2, weinberg, c2, MPFR_RNDD);
    mpfr_div_ui(c2, c2, 2, MPFR_RNDD);
  }

  mpfr_t temp2;
  mpfr_init2(temp2, BITS);

  mpfr_mul_ui(c1_factor, xsq, 14, MPFR_RNDD);
  mpfr_ui_sub(c1_factor, 1, c1_factor, MPFR_RNDD);
  mpfr_pow_ui(temp, xsq, 2, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 2, MPFR_RNDD);
  mpfr_sub(c1_factor, c1_factor, temp, MPFR_RNDD);
  mpfr_pow_ui(temp, xsq, 3, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 12, MPFR_RNDD);
  mpfr_sub(c1_factor, c1_factor, temp, MPFR_RNDD);
  mpfr_mul(c1_factor, c1_factor, sq1m4x2, MPFR_RNDD);
  mpfr_pow_ui(temp, xsq, 2, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 12, MPFR_RNDD);

  mpfr_pow_ui(temp2, xsq, 2, MPFR_RNDD);
  mpfr_sub_ui(temp2, temp2, 1, MPFR_RNDD);
  mpfr_mul(temp, temp, temp2, MPFR_RNDD);
  mpfr_mul(temp, temp, L, MPFR_RNDD);
  mpfr_add(c1_factor, c1_factor, temp, MPFR_RNDD);

  mpfr_pow_ui(c2_factor, xsq, 2, MPFR_RNDD);
  mpfr_mul_ui(c2_factor, c2_factor, 12, MPFR_RNDD);
  mpfr_mul_ui(temp, xsq, 10, MPFR_RNDD);
  mpfr_sub(c2_factor, temp, c2_factor, MPFR_RNDD);
  mpfr_add_ui(c2_factor, c2_factor, 2, MPFR_RNDD);
  mpfr_mul(c2_factor, xsq, c2_factor, MPFR_RNDD);
  mpfr_mul(c2_factor, c2_factor, sq1m4x2, MPFR_RNDD);
  mpfr_pow_ui(temp2, xsq, 2, MPFR_RNDD);
  mpfr_mul_ui(temp2, temp2, 2, MPFR_RNDD);
  mpfr_mul_ui(temp, xsq, 2, MPFR_RNDD);
  mpfr_ui_sub(temp, 1, temp, MPFR_RNDD);
  mpfr_add(temp, temp, temp2, MPFR_RNDD);
  mpfr_mul(temp, temp, L, MPFR_RNDD);
  mpfr_pow_ui(temp2, xsq, 2, MPFR_RNDD);
  mpfr_mul_ui(temp2, temp2, 6, MPFR_RNDD);
  mpfr_mul(temp, temp, temp2, MPFR_RNDD);
  mpfr_add(c2_factor, c2_factor, temp, MPFR_RNDD);

  mpfr_t result;
  mpfr_init2(result, BITS);
  mpfr_mul(temp, c2, c2_factor, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 4, MPFR_RNDD);
  mpfr_mul(temp2, c1, c1_factor, MPFR_RNDD);
  mpfr_add(result, temp, temp2, MPFR_RNDD);
  mpfr_mul(result, factor, result, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);

  mpfr_clears(fermiCsq, pi, result, denominator, temp, xsq, factor,
              betamass, HNLmass, NZ, angle, sq1m4x2, L, weinberg, c1, c2,
              c1_factor, c2_factor, temp2, (mpfr_ptr)0);
  return rval;
}

Double_t pw_lalpha_lbeta_nubeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Lepton &beta,
                                const HNL &N) {
  Particle gamma = Particle(); // this initializes an empty particle

  return pw_lalpha_lbeta_nubeta(cfg, alpha, beta, gamma, N);
}

Double_t pw_lalpha_lbeta_nubeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Quark &beta, const Quark &gamma,
                                const HNL &N) {
  bool betaIsUp = false;
  bool gammaIsUp = false;
  Quark_Type bqt = beta.getQuarkType();
  Quark_Type cqt = gamma.getQuarkType();

  if(bqt == Quark_Type::up or bqt == Quark_Type::charm or bqt == Quark_Type::top) betaIsUp = true;
  if(cqt == Quark_Type::up or cqt == Quark_Type::charm or cqt == Quark_Type::top) gammaIsUp = true;

  if(not betaIsUp or gammaIsUp) return 0; // we need beta = up-type and gamma=down-type

  Double_t NC = 3; // number of colors
  Double_t d_NW = NC * cfg->getVUDsq(beta, gamma);

  return pw_lalpha_lbeta_nubeta(cfg, alpha, beta, gamma, N, d_NW);
}

Double_t pw_lalpha_lbeta_nubeta(std::shared_ptr<Config> cfg,
                                const Lepton &alpha, const Particle &beta, const Particle &gamma,
                                const HNL &N, Double_t d_NW) {

  if (not N.mixesWith(alpha))
    return 0;
  if (alpha == beta)
    return 0;
  if (N.getMass() < alpha.getMass() + beta.getMass() + gamma.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiCsq, pi;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getPi(pi);

  mpfr_t NW, angle, HNLmass;
  mpfr_init2(NW, BITS);
  mpfr_init2(angle, BITS);
  mpfr_init2(HNLmass, BITS);

  mpfr_set_d(NW, d_NW, MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);

  Double_t xl = alpha.getMass() / N.getMass();
  Double_t xu = beta.getMass() / N.getMass();
  Double_t xd = gamma.getMass() / N.getMass();

  mpfr_t I;
  mpfr_init2(I, BITS);
  mpfr_set_d(I, I_xu_xd_xl(xu, xd, xl), MPFR_RNDD);

  // temporary vars and result value
  mpfr_t result, temp;
  mpfr_init2(result, BITS);
  mpfr_init2(temp, BITS);

  mpfr_pow_ui(temp, pi, 3, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 192, MPFR_RNDD);
  mpfr_pow_ui(result, HNLmass, 5, MPFR_RNDD);
  mpfr_mul(result, result, fermiCsq, MPFR_RNDD);
  mpfr_mul(result, result, NW, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_mul(result, result, I, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);
  mpfr_clears(fermiCsq, pi, I, NW, angle, HNLmass, result, temp,
              (mpfr_ptr)0);

  return rval;
}

Double_t pw_nualpha_nubeta_nubeta(std::shared_ptr<Config> cfg,
                                  const Lepton &alpha, const Lepton &beta,
                                  const HNL &N) {
  if (not N.mixesWith(alpha))
    return 0;

  /*
   * We just need to load configuration for precision bits and
   * nature constants
   */
  mpfr_t fermiCsq, pi;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getPi(pi);
  // end of loading configuration

  // initialize and set vars to M_N, U^2
  mpfr_t HNLmass, angle;
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(angle, BITS);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);

  unsigned int equal = 1;
  if (alpha == beta) {
    equal++; // increase by one to get the right factor (1+delta_{alpha,beta})
  }

  mpfr_t result, temp;
  mpfr_init2(result, BITS);
  mpfr_init2(temp, BITS);

  mpfr_pow_ui(result, HNLmass, 5, MPFR_RNDD);
  mpfr_mul(result, fermiCsq, result, MPFR_RNDD);
  mpfr_mul_ui(result, result, equal, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_pow_ui(temp, pi, 3, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 768, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);

  mpfr_clears(fermiCsq, pi, HNLmass, angle, result, temp, (mpfr_ptr)0);
  return rval;
}

Double_t pw_neutral_pseudoscalar_mesons(std::shared_ptr<Config> cfg,
                                        const Lepton &alpha, const Meson &m,
                                        const HNL &N) {
  if (not N.mixesWith(alpha))
    return 0;
  if (N.getMass() < m.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiC, fermiCsq, pi;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiC, BITS);
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getFermiC(fermiC);
  cfg->getPi(pi);

  // initialize high precision variables
  mpfr_t xhsq, fhsq;
  mpfr_t mesonMass, HNLmass, angle;
  mpfr_init2(xhsq, BITS);
  mpfr_init2(fhsq, BITS);
  mpfr_init2(mesonMass, BITS);
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(angle, BITS);

  // set high precision variables to values
  mpfr_set_d(mesonMass, m.getMass(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(fhsq, m.getDecayConstant(), MPFR_RNDD);
  mpfr_pow_ui(fhsq, fhsq, 2, MPFR_RNDD);
  mpfr_div(xhsq, mesonMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xhsq, xhsq, 2, MPFR_RNDD);

  // create result and temp variables
  mpfr_t result, temp;
  mpfr_init2(temp, BITS);
  mpfr_init2(result, BITS);

  mpfr_mul(result, fermiCsq, fhsq, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_pow_ui(temp, HNLmass, 3, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);
  mpfr_mul_ui(temp, pi, 32, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);

  mpfr_ui_sub(temp, 1, xhsq, MPFR_RNDD);
  mpfr_pow_ui(temp, temp, 2, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);
  mpfr_clears(fermiC, fermiCsq, pi, xhsq, fhsq, mesonMass, HNLmass, angle,
              result, temp, (mpfr_ptr)0);

  return rval;
}

Double_t pw_charged_pseudoscalar_mesons(std::shared_ptr<Config> cfg,
                                        const Lepton &alpha, const Meson &m,
                                        const HNL &N) {
  if (not N.mixesWith(alpha))
    return 0;
  if (N.getMass() < alpha.getMass() + m.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiC, fermiCsq, pi, VUDsq;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiC, BITS);
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  mpfr_init2(VUDsq, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getFermiC(fermiC);
  cfg->getPi(pi);
  cfg->getVUDsq(VUDsq, m);

  // initialize high precision variables
  mpfr_t xhsq, xlsq, fh;
  mpfr_t mesonMass, alphaMass, HNLmass, angle;
  mpfr_init2(xhsq, BITS);
  mpfr_init2(xlsq, BITS);
  mpfr_init2(fh, BITS);
  mpfr_init2(mesonMass, BITS);
  mpfr_init2(alphaMass, BITS);
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(angle, BITS);

  // set high precision variables to values
  mpfr_set_d(mesonMass, m.getMass(), MPFR_RNDD);
  mpfr_set_d(alphaMass, alpha.getMass(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(fh, m.getDecayConstant(), MPFR_RNDD);
  mpfr_div(xlsq, alphaMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xlsq, xlsq, 2, MPFR_RNDD);
  mpfr_div(xhsq, mesonMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xhsq, xhsq, 2, MPFR_RNDD);

  // create result and temp variables
  mpfr_t result, temp, temp2;
  mpfr_init2(temp, BITS);
  mpfr_init2(temp2, BITS);
  mpfr_init2(result, BITS);

  // pw computation, eq.(B.31)
  mpfr_pow_ui(temp, fh, 2, MPFR_RNDD);
  mpfr_mul(result, fermiCsq, temp, MPFR_RNDD);
  mpfr_mul(result, result, VUDsq, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_pow_ui(temp, HNLmass, 3, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);
  mpfr_mul_ui(temp, pi, 16, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);

  mpfr_ui_sub(temp, 1, xlsq, MPFR_RNDD);
  mpfr_pow_ui(temp, temp, 2, MPFR_RNDD);

  mpfr_add_ui(temp2, xlsq, 1, MPFR_RNDD);
  mpfr_mul(temp2, temp2, xhsq, MPFR_RNDD);
  mpfr_sub(temp, temp, temp2, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);

  mpfr_t one;
  mpfr_init2(one, BITS);
  mpfr_set_d(one, 1, MPFR_RNDD);

  kaellen(cfg, temp, one, xhsq, xlsq);
  mpfr_sqrt(temp, temp, MPFR_RNDD);

  mpfr_mul(result, result, temp, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);
  mpfr_clears(fermiC, fermiCsq, pi, VUDsq, xhsq, xlsq, fh, mesonMass, alphaMass,
              HNLmass, angle, result, temp, temp2, one, (mpfr_ptr)0);

  return rval;
}

Double_t pw_charged_vector_mesons(std::shared_ptr<Config> cfg,
                                  const Lepton &alpha, const Meson &m,
                                  const HNL &N) {
  if (not N.mixesWith(alpha))
    return 0;
  if (N.getMass() < alpha.getMass() + m.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiC, fermiCsq, pi, VUDsq;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiC, BITS);
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  mpfr_init2(VUDsq, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getFermiC(fermiC);
  cfg->getPi(pi);
  cfg->getVUDsq(VUDsq, m);

  // initialize high precision variables
  mpfr_t xhsq, xlsq, ghsq;
  mpfr_t mesonMass, alphaMass, HNLmass, angle;
  mpfr_init2(xhsq, BITS);
  mpfr_init2(xlsq, BITS);
  mpfr_init2(ghsq, BITS);
  mpfr_init2(mesonMass, BITS);
  mpfr_init2(alphaMass, BITS);
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(angle, BITS);

  // set high precision variables to values
  mpfr_set_d(mesonMass, m.getMass(), MPFR_RNDD);
  mpfr_set_d(alphaMass, alpha.getMass(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(ghsq, m.getDecayConstant(), MPFR_RNDD);
  mpfr_pow_ui(ghsq, ghsq, 2, MPFR_RNDD);
  mpfr_div(xlsq, alphaMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xlsq, xlsq, 2, MPFR_RNDD);
  mpfr_div(xhsq, mesonMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xhsq, xhsq, 2, MPFR_RNDD);

  // create result and temp variables
  mpfr_t result, temp, temp2;
  mpfr_init2(temp, BITS);
  mpfr_init2(temp2, BITS);
  mpfr_init2(result, BITS);

  mpfr_mul(result, fermiCsq, ghsq, MPFR_RNDD);
  mpfr_mul(result, result, VUDsq, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_pow_ui(temp, HNLmass, 3, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);
  mpfr_mul_ui(temp, pi, 16, MPFR_RNDD);
  mpfr_pow_ui(temp2, mesonMass, 2, MPFR_RNDD);
  mpfr_mul(temp, temp, temp2, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);

  mpfr_ui_sub(temp, 1, xlsq, MPFR_RNDD);
  mpfr_pow_ui(temp, temp, 2, MPFR_RNDD);

  mpfr_add_ui(temp2, xlsq, 1, MPFR_RNDD);
  mpfr_mul(temp2, temp2, xhsq, MPFR_RNDD);
  mpfr_add(temp, temp, temp2, MPFR_RNDD);
  mpfr_pow_ui(temp2, xhsq, 2, MPFR_RNDD);
  mpfr_mul_ui(temp2, temp2, 2, MPFR_RNDD);
  mpfr_sub(temp2, temp, temp2, MPFR_RNDD);

  mpfr_t one;
  mpfr_init2(one, BITS);
  mpfr_set_d(one, 1, MPFR_RNDD);

  kaellen(cfg, temp, one, xhsq, xlsq);
  mpfr_sqrt(temp, temp, MPFR_RNDD);
  mpfr_mul(temp, temp, temp2, MPFR_RNDD);
  LOG_DEBUG("value of after factor: " << mpfr_get_d(temp, MPFR_RNDD));
  LOG_DEBUG("value of Gamma0: " << mpfr_get_d(result, MPFR_RNDD));

  mpfr_mul(result, result, temp, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);
  mpfr_clears(fermiC, fermiCsq, pi, VUDsq, one, result, temp, temp2, xhsq, xlsq,
              ghsq, mesonMass, alphaMass, HNLmass, angle, (mpfr_ptr)0);

  return rval;
}

Double_t pw_neutral_vector_mesons(std::shared_ptr<Config> cfg,
                                  const Lepton &alpha, const Meson &m,
                                  const HNL &N) {
  if (not N.mixesWith(alpha))
    return 0;
  if (not m.hasValue("kh"))
    throw std::runtime_error("Neutral mesons need to have dimensionless kh "
                             "factor stored as 'kh' value.");
  if (N.getMass() < m.getMass())
    return 0; // this means we don't have enough mass in the HNL to produce
              // decay product on-shell

  mpfr_t fermiC, fermiCsq, pi;
  unsigned int BITS = cfg->getBITS();
  mpfr_init2(fermiC, BITS);
  mpfr_init2(fermiCsq, BITS);
  mpfr_init2(pi, BITS);
  cfg->getFermiCsq(fermiCsq);
  cfg->getFermiC(fermiC);
  cfg->getPi(pi);

  // initialize high precision variables
  mpfr_t xhsq, ghsq, khsq;
  mpfr_t mesonMass, HNLmass, angle;
  mpfr_init2(xhsq, BITS);
  mpfr_init2(ghsq, BITS);
  mpfr_init2(khsq, BITS);
  mpfr_init2(mesonMass, BITS);
  mpfr_init2(HNLmass, BITS);
  mpfr_init2(angle, BITS);

  // set high precision variables to values
  mpfr_set_d(mesonMass, m.getMass(), MPFR_RNDD);
  mpfr_set_d(HNLmass, N.getMass(), MPFR_RNDD);
  mpfr_set_d(angle, N.getAngle(), MPFR_RNDD);
  mpfr_set_d(ghsq, m.getDecayConstant(), MPFR_RNDD);
  mpfr_pow_ui(ghsq, ghsq, 2, MPFR_RNDD);
  mpfr_set_d(khsq, m.getValue("kh"), MPFR_RNDD);
  mpfr_pow_ui(khsq, khsq, 2, MPFR_RNDD);
  mpfr_div(xhsq, mesonMass, HNLmass, MPFR_RNDD);
  mpfr_pow_ui(xhsq, xhsq, 2, MPFR_RNDD);

  // create result and temp variables
  mpfr_t result, temp;
  mpfr_init2(temp, BITS);
  mpfr_init2(result, BITS);

  mpfr_mul(result, fermiCsq, ghsq, MPFR_RNDD);
  mpfr_mul(result, result, khsq, MPFR_RNDD);
  mpfr_mul(result, result, angle, MPFR_RNDD);
  mpfr_pow_ui(temp, HNLmass, 3, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);
  mpfr_pow_ui(temp, mesonMass, 2, MPFR_RNDD);
  mpfr_mul(temp, temp, pi, MPFR_RNDD);
  mpfr_mul_ui(temp, temp, 32, MPFR_RNDD);
  mpfr_div(result, result, temp, MPFR_RNDD);

  mpfr_mul_ui(temp, xhsq, 2, MPFR_RNDD);
  mpfr_add_ui(temp, temp, 1, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);

  mpfr_ui_sub(temp, 1, xhsq, MPFR_RNDD);
  mpfr_pow_ui(temp, temp, 2, MPFR_RNDD);
  mpfr_mul(result, result, temp, MPFR_RNDD);

  Double_t rval = mpfr_get_d(result, MPFR_RNDD);
  mpfr_clears(fermiC, fermiCsq, pi, result, temp, xhsq, ghsq, khsq, mesonMass,
              HNLmass, angle, (mpfr_ptr)0);

  return rval;
}


