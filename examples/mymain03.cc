// Goal = simulate N decay, select mu mu pi decay products and reco mass

#include "Pythia8/Pythia.h"


#include <sys/types.h>
#include <dirent.h>


using namespace Pythia8;

int main() {

  Pythia pythia;
  
  // Shorthand for the event record in pythia. LHC settings.
  Event& event = pythia.event;
  //ParticleData& particleData = pythia.particleData;
  pythia.readString("Beams:eCM = 14000.");
  
  // Extract settings to be used in the main program.
  int nEvent = pythia.mode("Main:numberOfEvents");
  int nAbort = pythia.mode("Main:timesAllowErrors");
 
  // Redef of HNL
  //pythia.readString("id:channel:products =  product1 product2");
  /*
  //pythia.readFile("HNL_prop.cmnd");
	pythia.particleData.particleDataEntryPtr(14)->ParticleDataEntry::setMayDecay(true);  
	pythia.particleData.particleDataEntryPtr(14)->setIsResonance(true);
	pythia.particleData.particleDataEntryPtr(14)->setMWidth(4.);
	cout << "is Res:    " << pythia.particleData.particleDataEntryPtr(14)->isResonance() << " | mWidth of 14: " << pythia.particleData.particleDataEntryPtr(14)->mWidth() << endl;
	cout << "Res Width: " << pythia.particleData.resWidthOpen(14, 60.) << endl;
	cout << "Res init:  " << particleData.getIsInit() << endl;  
	*/
  pythia.readFile("HNLprop.cmnd");
  
  
  /***  Processes selection  ***/
  pythia.readString("HardQCD:all = on");
  pythia.readString("HardQCD:hardbbbar=on");
  pythia.readString("WeakSingleBoson:all=on");
  pythia.readString("WeakSingleBoson:ffbar2W = on");
  
 
  pythia.readString("WeakBosonExchange:all=on");
  pythia.readString("WeakBosonAndParton:all=on");
  pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	
  pythia.readString("LeftRightSymmmetry:all=on");
  
  //pythia.readString("TwoFermions2W2TwoFermion=on");
  pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");
  //pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	

  // Conditions on daughters  
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  
 
 
 
 
 // Initialisation
  // pythia.readString("Init:showAllParticleData=on");
  pythia.readString("Next:numberShowEvent=10");
  pythia.init(); 					//take its values from the beam specification stored in the Settings database

  
  
  
  /*** Histrograms defintion ***/
  /* Hist(string titleIn, int nBinIn = 100, double xMinIn = 0., double xMaxIn = 1., bool logXIn = false) */
  
  Hist mass(	"mass of N [GeV]",100, 1., 10000., true); // mass between 1 GeV and 10 TeV
  Hist tau(		"lifetime [s]", 				100, 10e-27, 10e-3);
  Hist pThard(	"process pT scale", 			100, 0., 500.);
  Hist nFinal(	"final particle multiplicity", 	100, -0.5, 1599.5);
  Hist nCharged("charged particle multiplicity",100, -0.5, 799.5);
  Hist dndy(	"dn/dy for charged particles", 	100, -10., 10.);
  Hist dndeta(	"dn/d(eta) for charged particles", 100, -10., 10.);
  Hist dndpT(	"dn/dpT for charged particles", 100, 0., 10.);
  Hist epCons(	"deviation from energy-momentum conservation", 100, 0., 1e-6);

  // Histogram particle spectra.
  Hist eGamma(	"energy spectrum of photons",		100, 0., 6000.);
  Hist eMu(    	"energy spectrum of mu+ and mu-",	100, 0., 6000.);
  Hist eNu(   	"energy spectrum of neutrinos",		100, 0., 6000.);
  Hist ePi( 	"energy spectrum of pi+ and pi-",	100, 0., 6000.);
  Hist eRest( 	"energy spectrum of others",		100, 0., 6000.);

  
  // Begin event loop.
  int iAbort = 0;
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    // Generate events. Quit if many failures.
    if (!pythia.next()) {
      if (++iAbort < nAbort) continue;
      cout << " Event generation aborted prematurely, owing to error!\n";
      break;
    }
    // Fill hard scale of event.
    pThard.fill( pythia.info.pTHat() );
	
    int  nFin = 0;
    int  nChg = 0;
    Vec4 pSum;
    // Loop over all particles and analyze the final-state ones.
    for (int i = 0; i < pythia.event.size(); ++i){
		if (pythia.event[i].isFinal()) {
			
		  // NTuple filling
		  //HepMC::I Pythia8::fill_next_event(pythia.event[i], hepmcevt)	
		  
		  
		  
		  int idAbs = pythia.event[i].idAbs();
		  double eI = pythia.event[i].e();
		  if (idAbs == 22) eGamma.fill(eI);
		  else if (idAbs == 13) {
			  eMu.fill(eI); 
			  //cout << "FinalState: Muon with mother 1: " << pythia.event[i].mother1() << " and mother 2 "<< pythia.event[i].mother2()<<endl;
			  //cout << "FinalState: Muon with daughter 1: " << pythia.event[i].daughter1() << " and daughter 2 "<< pythia.event[i].daughter2()<<endl;
		  }
		  else if (idAbs == 12 || idAbs == 14 || idAbs == 16) eNu.fill(eI);
		  else if (idAbs == 211){
			   ePi.fill(eI);
			   //cout << "FinalState: Pion with mother 1: " << pythia.event[i].mother1() << " and mother 2 "<< pythia.event[i].mother2()<<endl;
			   //cout << "FinalState: Pion with daughter 1: " << pythia.event[i].daughter1() << " and daughter 2 "<< pythia.event[i].daughter2()<<endl;
		   }
		  else {
			eRest.fill(eI);
			//cout << " Error: stable id = " << pythia.event[i].id() << endl;
		  }
		}
		
		nFin++;
        pSum += event[i].p();
        if (event[i].isCharged()) {
			++nChg;
			dndy.fill( event[i].y() );
			dndeta.fill( event[i].eta() );
			dndpT.fill( event[i].pT() );
        }
		nFinal.fill( nFin );
		nCharged.fill( nChg );
    }
    
  }// End of events loop
  
  
  
  pythia.stat();
  double sigma = pythia.info.sigmaGen();
  
  pThard   *= sigma * 1e6 * 0.2 / nEvent;
  nFinal   *= 1. / (16. * nEvent);
  nCharged *= 1. / (8. * nEvent);
  dndy     *=  5. / nEvent;
  dndeta   *=  5. / nEvent;
  dndpT    *= 10. / nEvent;
  cout << pThard << nFinal << nCharged << dndy << dndeta << dndpT << epCons;
  
  eGamma *= 2.5 / nEvent;
  eMu     *= 2.5 / nEvent;
  ePi     *= 2.5 / nEvent;
  eNu    *= 2.5 / nEvent;
  eRest    *= 2.5 / nEvent;
  cout << eGamma << eMu << ePi << eNu << eRest;



  / ** NTuple writing ** /
  
  
  
  

  // Write Python code that can generate a PDF file with the spectra.
  // Assuming you have Python installed on your platform, do as follows.
  // After the program has run, type "python main03plot.py" (without the " ")
  // in a terminal window, and open "out03plot.pdf" in a PDF viewer.
  // Colours and other choices can be omitted, but are shown as illustration.

  HistPlot hpl("mymain02plot");
  
  hpl.plotFrame("outmy02plot", pThard, "$p_{\\perp}$ scale of hard interaction",
    "$p_{\\perp}$ (GeV)", "$\\mathrm{d}\\sigma/\\mathrm{d}p_{\\perp}$ (nb/GeV)",
    "h", "$p_{\\perp}$ of $2 \\to 2$ process", true);
  hpl.frame("", "Total and charged particle multiplicities",
    "$n$", "$\\mathrm{d}P/\\mathrm{d}n$");
  hpl.add( nFinal, "h,royalblue", "total");
  hpl.add( nCharged, "h,orange", "charged (even only!)");
  hpl.plot();
  hpl.frame( "", "Charged (pseudo)rapidity distribution", "$y$ or $\\eta$",
    "$\\mathrm{d}n_{\\mathrm{charged}}/\\mathrm{d}(y/\\eta)$");
  hpl.add( dndy, "-", "$\\mathrm{d}n_{\\mathrm{charged}}/\\mathrm{d}y$");
  hpl.add( dndeta, "--,magenta",
    "$\\mathrm{d}n_{\\mathrm{charged}}/\\mathrm{d}\\eta$");
  hpl.plot();
  hpl.plotFrame("", dndpT, "Charged $p_{\\perp}$ spectrum",
    "$p_{\\perp}$ (GeV)", "$\\mathrm{d}n_{\\mathrm{charged}}/\\mathrm{d}"
    "p_{\\perp}$ (GeV$^{-1}$)", "", "charged", true);
  
  
  hpl.frame( "", "Particle energy spectra", "$E$ (GeV)",
    "$(1/N_{\\mathrm{event}}) \\mathrm{d}N / \\mathrm{d}E$ (GeV$^{-1}$)");
  hpl.add( eGamma, "-", "$\\gamma$");
  hpl.add( eMu, "-", "$\\mu^{\\pm}$");
  hpl.add( ePi, "-", "$\\pi^{\\pm}$");
  hpl.add( eNu, "-", "$\\nu$");
  hpl.add( eNu, "-", "others");
  // Use logarithmic y scale.
  hpl.plot( true);
  
  

   
  return 0;
}




