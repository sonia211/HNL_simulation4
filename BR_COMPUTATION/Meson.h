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

#ifndef MESON_H
#define MESON_H
#include "Particle.h"
#include "TString.h"
#include <map>

enum class MesonType { Unknown, pseudoscalar, vector };
enum class Charge { Unknown, charged, neutral };
enum class Quark_Type { Unknown, up, down, charm, strange, top, bottom };

class Meson : public Particle {
public:
  Meson() : Particle() {
    decayConstant = 0;
    charge = Charge::Unknown;
    type = MesonType::Unknown;
    U = Quark_Type::Unknown;
    D = Quark_Type::Unknown;
  }
  Meson(Int_t p, Double_t m, Double_t c, MesonType t, Charge q,
        Quark_Type u = Quark_Type::Unknown, Quark_Type d = Quark_Type::Unknown)
      : Particle(p, m) {
    decayConstant = c;
    charge = q;
    type = t;
    U = u;
    D = d;
  }
  Meson(const Meson &obj) : Particle(obj) {
    decayConstant = obj.getDecayConstant();
    vals = obj.getValueMap();
    charge = obj.getCharge();
    type = obj.getMesonType();
    U = obj.getU();
    D = obj.getD();
  }

  Meson &operator=(const Meson &obj) {
    Particle::operator=(obj);

    decayConstant = obj.getDecayConstant();
    vals = obj.getValueMap();
    charge = obj.getCharge();
    type = obj.getMesonType();
    U = obj.getU();
    D = obj.getD();

    return *this;
  }

  MesonType getMesonType() const { return type; }

  Charge getCharge() const { return charge; }

  Quark_Type getU() const { return U; };

  Quark_Type getD() const { return D; };

  Double_t getDecayConstant() const { return decayConstant; }

  bool hasValue(TString name) const { return vals.count(name) > 0; }

  Double_t getValue(TString name) const { return vals.at(name); }

  void insertValue(TString name, Double_t value) {
    vals.insert(std::pair<TString, Double_t>(name, value));
  }

  std::map<TString, Double_t> getValueMap() const { return vals; }

private:
  Double_t decayConstant;
  std::map<TString, Double_t> vals;
  MesonType type;
  Charge charge;
  Quark_Type U;
  Quark_Type D;
};
#endif
