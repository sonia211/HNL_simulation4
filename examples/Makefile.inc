# PYTHIA configuration file.
# Generated on Thu Apr 25 14:54:27 CEST 2019 with the user supplied options:
# --enable-shared
# --with-root=/usr/local/Cellar/root/6.16.00/

# Install directory prefixes.
PREFIX_BIN=/Users/bouchiba/Documents/PDM/HNL_simulation4/bin
PREFIX_INCLUDE=/Users/bouchiba/Documents/PDM/HNL_simulation4/include
PREFIX_LIB=/Users/bouchiba/Documents/PDM/HNL_simulation4/lib
PREFIX_SHARE=/Users/bouchiba/Documents/PDM/HNL_simulation4/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=true
CXX=g++
CXX_COMMON=-O2  -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-dynamiclib
CXX_SONAME=-Wl,-dylib_install_name,@rpath/
LIB_SUFFIX=.dylib

# EVTGEN configuration.
EVTGEN_USE=false
EVTGEN_BIN=
EVTGEN_INCLUDE=
EVTGEN_LIB=

# FASTJET3 configuration.
FASTJET3_USE=false
FASTJET3_BIN=
FASTJET3_INCLUDE=
FASTJET3_LIB=

# HEPMC2 configuration.
HEPMC2_USE=false
HEPMC2_BIN=
HEPMC2_INCLUDE=
HEPMC2_LIB=

# HEPMC3 configuration.
HEPMC3_USE=false
HEPMC3_BIN=
HEPMC3_INCLUDE=
HEPMC3_LIB=

# LHAPDF5 configuration.
LHAPDF5_USE=false
LHAPDF5_BIN=
LHAPDF5_INCLUDE=
LHAPDF5_LIB=

# LHAPDF6 configuration.
LHAPDF6_USE=false
LHAPDF6_BIN=
LHAPDF6_INCLUDE=
LHAPDF6_LIB=

# POWHEG configuration.
POWHEG_USE=false
POWHEG_BIN=
POWHEG_INCLUDE=
POWHEG_LIB=

# PROMC configuration.
PROMC_USE=false
PROMC_BIN=
PROMC_INCLUDE=
PROMC_LIB=

# ROOT configuration.
ROOT_USE=true
ROOT_BIN=/usr/local/Cellar/root/6.16.00/bin/
ROOT_LIBS=-L/usr/local/Cellar/root/6.16.00/lib/root -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lpthread -stdlib=libc++ -lm -ldl
CXX_ROOT=-O2  -W -Wall -Wshadow -fPIC -pthread -stdlib=libc++ -std=c++11 -m64 -I/usr/local/Cellar/root/6.16.00/include/root

# GZIP configuration.
GZIP_USE=false
GZIP_BIN=
GZIP_INCLUDE=
GZIP_LIB=

# BOOST configuration.
BOOST_USE=false
BOOST_BIN=
BOOST_INCLUDE=
BOOST_LIB=

# PYTHON configuration.
PYTHON_USE=false
PYTHON_BIN=
PYTHON_INCLUDE=
PYTHON_LIB=
