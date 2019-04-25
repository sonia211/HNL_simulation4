#include <TROOT.h>
#include "TString.h"

void compile(){
//gROOT->ProcessLine(".L main.cpp++");
//gROOT->ProcessLine(".L PlotYears.cpp++");
gROOT->ProcessLine(".L Plotter.hpp++");

}

