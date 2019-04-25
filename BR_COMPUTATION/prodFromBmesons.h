#ifndef PRODFROMBMESONS_H
#define PRODFROMBMESONS_H
#include "HNL.h"
#include "Lepton.h"
#include "Meson.h"
#include "auxfunctions.h"
#include <vector>

Double_t kallen(Double_t a, Double_t b, Double_t c);
Double_t Gamma(Double_t eta, Double_t yhp, Double_t yl, Double_t yN);
Double_t Gminus(Double_t eta, Double_t yhp, Double_t yl, Double_t yN);
Double_t compute_fplus(Double_t q2);
Double_t compute_fzero(Double_t q2);

Double_t compute_fP1(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_);
Double_t compute_fP2(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_);
Double_t compute_fP3(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, Double_t eta_);

Double_t integral_fP(Double_t a, Double_t b, Double_t nsteps, std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp, int fct);

Double_t pw_prodFromBmeson(std::shared_ptr<Config> cfg, HNL N, Lepton l, Meson meson, Meson mesonp);

#endif
