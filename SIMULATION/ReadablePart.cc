#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"

class ReadablePart{
	public:
		Event& event;
		Int_t id;
		Double_t P2,	PX,		PY,	PZ, PT, E;
		Double_t M,	MT,	TAU;
		Double_t Xp,	Yp,	Zp,  	Tp, Vp;
		Double_t Xd,	Yd,	Zd,  	Td, Vd;
		Double_t Xdiff,	Ydiff,	Zdiff,  	Tdiff;
		Double_t POL,	SCALE;
		bool willDecay;
	
		// Constructor.
		ReadablePart(bool _willDecay){
			id=0;
			P2=0.,	PX=0., 	PY=0.,	PZ=0., 	PT=0., 	E=0.;
			M=0.,	MT=0.,	TAU=0.;
			Xp=0.,	Yp=0.,	Zp=0.,  	Tp=0.,		Vp=0.;
			Xd=0.,	Yd=0.,	Zd=0.,  	Td=0., 		Vd=0.;
			Xdiff=0.,	Ydiff=0.,		Zdiff=0.,	Tdiff=0.;
			POL=0.,	SCALE=0.;
			willDecay=_willDecay;
			
			
			
		}
		
		//Setter (filling after a step of the simu)
		setPart(int i){
			
			id = event[i].id();
			E = event[i].e();
			M = event[i].m();
			//P2 = event[i].p2(
			PX = event[i].px();
			PY = event[i].py();
			PZ = event[i].pz();
			PT = event[i].pT();
			TAU = event[i].tau();
				  
			Xp = event[i].xProd();
			Yp = event[i].yProd();
			Zp = event[i].zProd();
			Tp = event[i].tProd();
					
			Xd = event[i].xDec();
			Yd = event[i].yDec();
			Zd = event[i].zDec();
			Td = event[i].tDec();
			
		}
	
	
	
	
};
