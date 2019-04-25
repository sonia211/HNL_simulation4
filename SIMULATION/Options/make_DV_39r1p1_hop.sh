cd $LB2LEMUROOT
lb-dev DaVinci/v39r1p1
cd DaVinciDev_v39r1p1/
git lb-use Analysis
git lb-checkout Analysis/v15r1 Phys/DecayTreeTuple
git lb-checkout Analysis/v18r5p1 Phys/DecayTreeTuple/src/TupleToolHOP.cpp
git lb-checkout Analysis/v18r5p1 Phys/DecayTreeTuple/src/TupleToolHOP.h
git lb-use Phys
git lb-checkout Phys/v21r1  Phys/LoKiPhys/
git lb-checkout Phys/v23r5  Phys/LoKiPhys/src/Particles38.cpp
git lb-checkout Phys/v23r5  Phys/LoKiPhys/LoKi/Particles38.h
cp $LB2LEMUROOT/scripts/functions.py Phys/LoKiPhys/python/LoKiPhys/