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

#ifndef CONFIG_H
#define CONFIG_H

#include "Meson.h"
#include "Quark.h"
#include "TMath.h"
#include "TString.h"
#include <gmp.h>
#include <mpfr.h>

class Config {
public:
  Config() {
    name = "default";
    BITS = 400;
    initialize();
  }
  Config(TString n, unsigned int b) {
    name = n;
    BITS = b;
    initialize();
  }

  ~Config(void) { mpfr_clears(fermiC, fermiCsq, pi, SOL, HBAR, (mpfr_ptr)0); }

  TString getName() const { return name; }

  unsigned int getBITS() const { return BITS; }
  void getFermiC(mpfr_t result) const { mpfr_set(result, fermiC, MPFR_RNDD); }
  void getFermiCsq(mpfr_t result) const { mpfr_set(result, fermiCsq, MPFR_RNDD); }
  void getPi(mpfr_t result) const { mpfr_set(result, pi, MPFR_RNDD); }
  void getVUDsq(mpfr_t result, const Meson &m) const {
    mpfr_set_d(result, ckm.at({m.getU(), m.getD()}), MPFR_RNDD);
    mpfr_pow_ui(result, result, 2, MPFR_RNDD);
  }
  Double_t getVUDsq(const Quark &u, const Quark &d) const { return ckm.at({u.getQuarkType(), d.getQuarkType()});}
  Double_t getVUDsq(const Quark_Type &u, const Quark_Type &d) const { return ckm.at({u, d});}
  void getSOL(mpfr_t result) const { mpfr_set(result, SOL, MPFR_RNDD); }
  void getHBAR(mpfr_t result) const { mpfr_set(result, HBAR, MPFR_RNDD); }

private:
  TString name;
  unsigned int BITS;
  mpfr_t fermiC, fermiCsq, pi, SOL, HBAR;

  std::map<std::pair<Quark_Type, Quark_Type>, Double_t> ckm = {
      {{Quark_Type::up, Quark_Type::down}, 0.97427},
      {{Quark_Type::up, Quark_Type::strange}, 0.22534},
      {{Quark_Type::up, Quark_Type::bottom}, 0.00351},
      {{Quark_Type::charm, Quark_Type::down}, 0.22520},
      {{Quark_Type::charm, Quark_Type::strange}, 0.97344},
      {{Quark_Type::charm, Quark_Type::bottom}, 0.0412},
      {{Quark_Type::top, Quark_Type::down}, 0.00867},
      {{Quark_Type::top, Quark_Type::strange}, 0.0404},
      {{Quark_Type::top, Quark_Type::bottom}, 0.999146}};

  void initialize() {
    mpfr_init2(fermiC, BITS);
    mpfr_set_d(fermiC, 1.1663787e-11,
               MPFR_RNDD); //  GF/(hbar c)^3 fermi constant in MeV^-2

    mpfr_init2(fermiCsq, BITS);
    mpfr_pow_ui(fermiCsq, fermiC, 2,
                MPFR_RNDD); // save square of fermiC for easier use

    mpfr_init2(pi, BITS);
    mpfr_set_d(pi, TMath::Pi(), MPFR_RNDD);

    mpfr_init2(SOL, BITS);
    mpfr_set_d(SOL, 299792458, MPFR_RNDD);

    mpfr_init2(HBAR, BITS);
    mpfr_set_d(HBAR, 6.582119514e-16, MPFR_RNDD);
  }
};

#endif
