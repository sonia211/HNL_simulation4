## What is this repository.

This is a repository containing code for the analyis of the LFV Lb2Lemu decay.

_Analysts: G. Andreassi, F. Archilli, M. Mulder, M. Van Veghel, L. Pescatore_

Contact: luca.pescatore@cern.ch

## How to setup the repository

Clone the repository. N.B.: "--recursive" is important because it also clones submodules.

```git clone --recursive ssh://git@gitlab.cern.ch:7999/pluca/Lb2LemuAna.git```

If you want to run interactively in testing mode.

```source scripts/setup.sh```

If you want to use snakemake.

```source scripts/setup.sh snake ```

#### First installation

To work properly you have to setup some dependencies (Snakemake).
On lxplus or machines with CVMFS installed the following should be enough.

N.B.: This needs to be done **before** sourcing scripts/setup.sh.

source scripts/setup_snake.sh

### Environment

* The `LB2LEMUROOT` variable is now avilable pointing to the top folder.
* ROOT, matplotlib, sklearn, etc are setup.
* Now code into the `python` folder should be automatically picked up if you try to import.
* At the beginning of each python file you should add `from Lb2LemuEnv import *` (see later)


## Repository Structure
------

* The analysis code after stripping should be fully contained into the `scripts`, `cpp` and `python` folders.
If you make subfolders of `python` put an empty `__init__.py` file inside each one.
* `Ganga` contain Ganga options. In parituclar gangaoption.py where a function CreateDVJob()
is already setup. Running ganga with `runganga` all functions defined in gangaoption.py will be available.
* `Options` contains DaVinci options to create the tuples.
* `Data` contains files with lists of LFNs used to make tuples.
* `LHCb` contains generic LHCb stuff like the LHCb style file and the particle propeties.
* `tables` is where you should put the output tables (see Lb2LemuEnv). It also contains the `templates` folder which should contain latex templates to be filled automatically.
* `plots` is where you should put output splots (see Lb2LemuEnv).


### Lb2LemuEnv (important!!)

This module loads the python environment: `from Lb2LemuEnv import *`.

What will this do for you:

* Checking that you sourced the setup.sh file.

* Loading the LHCb style for plots.

* Make the cuts defined in cuts.py available to all python scripts. __All cuts should be defined here!!__

* Make the locations easily available to you though the `loc` object. Already defined locations the following, feel free to define more as you need them:

    - loc.ROOT   = $LB2LEMUANAROOT
    - loc.PYTHON = $LB2LEMUANAROOT/python/
    - loc.LHCB   = $LB2LEMUANAROOT/LHCb/
    - loc.PLOTS  = $LB2LEMUANAROOT/plots/
    - loc.TABS   = $LB2LEMUANAROOT/tables/
    - loc.TMPS   = $LB2LEMUANAROOT/tables/templates/
    - loc.TUPLE  = /eos/lhcb/user/p/pluca/Analysis/Lb2emu/Tuple/

* Provide a common database saved on disk (still needs handling of more people working at same time).

```
from Lb2LemuEnv import *
print db
{'Test':True, ...}
db['myeff'] = 0.99
dumpDB() ## Saves it to disk
```

* Provide easy handling of output files

```from Lb2LemuEnv import *
outfiles.create("yields") ## Will create (only first time) the $LB2LEMUROOT/tables/yields.txt file and remember that it exists 
outfile.writeline("yields","N_B0 = 4000")```

Or even better you can do the same using templates!!! Crate a file in the templates folder. You can write whatever you want into it just put the values to substitute into {}
   
E.g.: `seleff = ${sel_eff} \pm {sel_eff_err}$`
   
And then use the `db` object to fill it!!

```from Lb2LemuEnv import *
outfile.fill_template("efficiencies","eff_tmp",db)```
 
This will look for the keys into the db, fill them into your template and same everything to $REPO/tables/efficiency.txt

* Make available to every script any other variable you wish to define into it. 

### Access data

Raw data (the output of the stripping) can be accessed using a provided function:

```from utils import remote_ls_fromids
from Lb2LemuEnv import dataids
files = remote_ls_fromids(dataids['{some data label e.g. CL11}'])```

To see the available datasets: 

```from Lb2LemuEnv import dataids
print dataids.keys()
['CL16', 'CL15', 'CL12', 'CL11']```


## Snakemake

You can run the offline anaylsis (or parts of it) simply typing `snakemake`.
Snakemake tutorial: https://snakemake.bitbucket.io/snakemake-tutorial.html (start from Basics Step 1)

The steps are defined into `Snakefile` in the top folder. At its beginning you can see a list of the required (final and intermediate) outputs of the analyisis.

To run snakemake from a clean shell:

```
source setup.ch snake
snakemake
```

## Docker

Docker support is available for this repository to allow running the analysis on any machine anywhere in the world (with internet). Please have a look at the readme inside the Docker folder.

## Common utilities

The `pyutils` folder contains utilities which you may find useful. See pyutils/README.md.

The `tools-easyanalysis` folder contains utilities for fitting. See tools-easyanalysis/Tutorials.

## Using SWAN
To be able to use SWAN, a few dedicated steps are necessary.
1. on lxplus, go to your CERNBOX user folder: /eos/user/.../.../
2. clone this repository (NB: the following procedure currently works only if you clone the repository from this location)
3. open a new SWAN session from https://swan.cern.ch , choosing LCG87, gcc49 and no environment script
4. open a new terminal, using the dropdown menu on the top right
5. cd into the repository's folder
6. run ```source setup-swan.sh install-deps```. This script is going to compile the tools, install rep and other dependencies. It is going to take a fairly long time for it to run, but it's needed only the very first time.
7. close the SWAN session
8. open a new one with the same caracteristics as before, but this time specify ```$CERNBOX_HOME/Lb2LemuAna/setup-swan.sh```
as environment script
9. enjoy

The instructions up to 7. included will need to be run only the first time, as a setup, while 8. and 9. are necessary every time you want to start a new SWAN session. # WORKDIR_D
