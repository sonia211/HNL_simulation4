#author: Guido Andreassi <guido.andreassi@cern.ch>


#plot vars
import numpy as np
import matplotlib.pyplot as plt

def plot_sig_bkg(sig_data, bkg_data, variable, subfolder, binning=0):
    sig = sig_data[variable]
    bkg = bkg_data[variable]

    low = min(np.min(sig), np.min(bkg))
    high = max(np.max(sig), np.max(bkg))
    low_high = (low,high)
    
    if (not (isinstance(binning, list) and len(binning)==3)):
        bins = 50
    else:
        bins = binning[0]
        low_high = (binning[1], binning[2])

    sig_Ntot = sig.count()
    bkg_Ntot = bkg.count()    
    
    fig, ax = plt.subplots()
    
    counts_sig, bins_sig, bars_sig = ax.hist(sig, bins = bins,
             color='b', alpha=0.5, range=low_high, 
             histtype='stepfilled', normed=True,
             label='S (train)')
    counts_bkg, bins_bkg, bars_bkg = ax.hist(bkg, bins = bins,
             color='r', alpha=0.5, range=low_high, 
             histtype='stepfilled', normed=True,
             label='B (train)')
    
    plt.xlabel(variable)
    plt.ylabel("Arbitrary units")
    plt.legend(loc='best')
    highest_bin = max(counts_sig.max(), counts_bkg.max())
    ax.set_ylim(bottom=0, top=highest_bin*1.05)
    plt.savefig(subfolder+"/"+variable.replace("/", "_over_")+".pdf") #replace is necessary for slashes, otherwise part of the name will be interpreted as folders
    plt.show()