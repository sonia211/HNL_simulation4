#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
    pythia.readString("ExtraDimensionsLED:monojet = on");
    pythia.readString("ExtraDimensionsLED:n = 4");
    pythia.readString("ExtraDimensionsLED:MD = 4000.");
    pythia.readString("ExtraDimensionsLED:CutOffmode = 3");
    pythia.readString("ExtraDimensionsLED:t = 2");
    pythia.readString("5000039:m0 = 2500.");
    pythia.readString("5000039:mWidth = 1500.");
    pythia.readString("5000039:mMin = 1.");
    pythia.readString("5000039:mMax = 13990.");
    pythia.readString("PhaseSpace:pTHatMin = 700.");
     pythia.readString("PhaseSpace:showViolation = off");
      pythia.readString("TauDecays:mode = 4");
pythia.readString("TauDecays:tauPolarization = 1.");
  /**
  pythia.readString("PhaseSpace:showViolation = off");
  pythia.readString("Beams:eCM = 14000.");
  //pythia.readString("HardQCD:all = on");
  pythia.readString("HardQCD:hardbbbar = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.readString("TauDecays:tauPolarization=1.");
  //pythia.readString("WeakSingleBoson:all = on"); 
  //pythia.readString("WeakBosonExchange:all = on"); 
  pythia.readString("WeakBosonAndParton:all = on"); 
  pythia.readString("PhotonParton:all =on");
  pythia.readString("HadronLevel:all = off.");
	//pythia.readString("TauDecays:tauMother=23");
	//pythia.readString("TauDecays:externalMode=1");
  //pythia.readString("ParticleDecays:sophisticatedTau");
	//pythia.readString("15:pol=-1");
	pythia.readString("TauDecays:mode=1");
	pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm)=on");
	pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gmZ)=on");
	pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");
	
	
	//pythia.readString("23:onIfAny = -15 15");
	//pythia.readString("24:onIfAny = -15 16");
	pythia.readString("23:oneChannel = 1 1. 2 -15 15");
	pythia.readString("24:oneChannel = 1 1. 2 -15 16");
	pythia.readString("15:mayDecay=on");
	pythia.readString("15:oneChannel= 1 1. 1521 13 -211");
	pythia.readString("Next:numberShowEvent=10");
	
    pythia.readString("521:oneChannel = 1 1. 2 15 16 111");
    **/
    // pythia.readString("")
    pythia.readString("Beams:eCM = 14000.");
  pythia.init();
 // Hist mult("charged multiplicity", 100, -0.5, 799.5);
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 400; ++iEvent) {
    if (!pythia.next()) continue;
    // Find number of all final charged particles and fill histogram.
    
    std::vector<vector<int>> daughters{};
    std::vector<vector<int>> mothers{};
    
    cout<< "\n\n########### EVENT " << iEvent << " #############" << endl;
    
    for (int i = 0; i < pythia.event.size(); ++i){
		//if (pythia.event[i].idAbs() == 15 and pythia.event[i].status() < 0 and ){
		//if (pythia.event[i].pol() != 9.0 ){
		//if (pythia.event[i].idAbs() == 15 and pythia.event[i].pol() != 9.0 ){
		if (pythia.event[i].idAbs() == 15){
			//cout<<"pol of tau " << pythia.event[i].pol() << endl;
			cout<<"id " << pythia.event[i].id() << endl;
			cout<<"pol " << pythia.event[i].pol() << endl;
			//cout<<"daughters " << pythia.event[i].daughter1() << endl;
			daughters.push_back({pythia.event[i].daughter1(), pythia.event[i].daughter2(), i});
			mothers.push_back({pythia.event[i].mother1(), pythia.event[i].mother2(), i});
			
			//Pyhtia8::iEvent
		}
   }
   
   
	for (int k(0); k<daughters.size(); ++k){
		int di=daughters[k][0]; int df=daughters[k][1]; int i = daughters[k][2];
		cout<< "\n DAUGHTERS \nSubprocess " << i << endl;
		cout<< "Number of daughters " << df-di +1 << endl;
		
		for (int d=di; d<=df; d++){
				if (pythia.event[d].pol() != 9.0 ){
				//if (1){
					cout<<"daughter " << d-di << ", id:" << pythia.event[d].id() << ", pol: " << pythia.event[d].pol() << endl;
				}
		}
   
   }
   
   for (int k(0); k<mothers.size(); ++k){
		int mi=mothers[k][0]; int mf=mothers[k][1]; int i = mothers[k][2];
		cout<< "\nMOTHERS\nSubprocess "<< i << endl;
		cout<<"mother 1 id " << pythia.event[mi].id();
		if (pythia.event[mi].pol() != 9.0 ) cout << ", pol: " << pythia.event[mi].pol() << endl;
		//if (1) cout << ", pol: " << pythia.event[mi].pol() << endl;
		cout<<"mother 2 " << pythia.event[mf].id() << endl;
		if (pythia.event[mf].pol() != 9.0 ) cout << ", pol: " << pythia.event[mf].pol() << endl;
		//if (1) cout << ", pol: " << pythia.event[mf].pol() << endl;
   }
   
   
   
  // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
 // cout << mult;
  return 0;
}
