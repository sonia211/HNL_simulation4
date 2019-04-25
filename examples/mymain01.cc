// Goal = simulate N decay, select mu mu pi decay products and reco mass

#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main() {

  Pythia pythia;
  
  // Shorthand for the event record in pythia. LHC settings.
  Event& event = pythia.event;
  pythia.readString("Beams:eCM = 14000.");
  
  // Extract settings to be used in the main program.
  int nEvent = pythia.mode("Main:numberOfEvents");
  int nAbort = pythia.mode("Main:timesAllowErrors");
 
  // Redef of HNL
  //pythia.readString("id:channel:products =  product1 product2");
  double bratio1(1.);
  double bratio2(1e-6);
  pythia.readFile("HNL_prop.cmnd");
  
  
  //Processes selection
  pythia.readString("HardQCD:all = on");
  pythia.readString("WeakSingleBoson:ffbar2gmZ = on");	

  // Conditions on daughters  
  pythia.readString("PhaseSpace:pTHatMin = 20.");
 
 // Initialisation
  pythia.init(); 					//take its values from the beam specification stored in the Settings database

  
  
  
  // Define here the histogram to fill with the wanted daughters regarding a certain property
  /* Hist(string titleIn, int nBinIn = 100, double xMinIn = 0.,
    double xMaxIn = 1., bool logXIn = false) : nBin(), nFill(), xMin(), xMax(),
    linX(), dx(), under(), inside(), over() {
    book(titleIn, nBinIn, xMinIn, xMaxIn, logXIn);
    */
  Hist mass("mass of N [GeV]", 100, 1., 10000., 1); // mass between 1 GeV and 10 TeV
  Hist tau("lifetime [s]", 100, 10e-27, 10e-3);
  Hist pThard("process pT scale", 100, 0., 500.);
  Hist nFinal("final particle multiplicity", 100, -0.5, 1599.5);
  Hist nCharged("charged particle multiplicity", 100, -0.5, 799.5);
  Hist dndy("dn/dy for charged particles", 100, -10., 10.);
  Hist dndeta("dn/d(eta) for charged particles", 100, -10., 10.);
  Hist dndpT("dn/dpT for charged particles", 100, 0., 10.);
  Hist epCons("deviation from energy-momentum conservation", 100, 0., 1e-6);

  
  
  // Begin event loop. Generate event. Skip if error. List first one.
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
  //Loop over final particles in the event.
  int  nFin = 0;
  int  nChg = 0;
  Vec4 pSum;
  for (int i = 0; i < event.size(); ++i) if (event[i].isFinal()) {
    // Analyze all particles.
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
    pSum /= event[0].e();
    double epDev = abs(pSum.e() - 1.) + abs(pSum.px()) + abs(pSum.py())+ abs(pSum.pz());
    epCons.fill(epDev);
  }
  // End of event loop
}
  pythia.stat();
  double sigma = pythia.info.sigmaGen();
  
  pThard   *= sigma * 1e6 * 0.2 / nEvent;
  nFinal   *= 1. / (16. * nEvent);
  nCharged *= 1. / (8. * nEvent);
  dndy     *=  5. / nEvent;
  dndeta   *=  5. / nEvent;
  dndpT    *= 10. / nEvent;
  cout << pThard << nFinal << nCharged << dndy << dndeta << dndpT << epCons;
  

  // Write Python code that can generate a PDF file with the spectra.
  // Assuming you have Python installed on your platform, do as follows.
  // After the program has run, type "python main03plot.py" (without the " ")
  // in a terminal window, and open "out03plot.pdf" in a PDF viewer.
  // Colours and other choices can be omitted, but are shown as illustration.

  HistPlot hpl("mymain01plot");
  hpl.plotFrame("outmy01plot", pThard, "$p_{\\perp}$ scale of hard interaction",
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
    
 
   
  return 0;
}



