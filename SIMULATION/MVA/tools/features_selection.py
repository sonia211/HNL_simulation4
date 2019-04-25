from math import log
import numpy as np

def entropy(sig_data, bkg_data, variable):
    
    sig = sig_data[variable]
    bkg = bkg_data[variable]
    
    minimum = min(np.min(sig), np.min(bkg))
    maximum = max(np.max(sig), np.max(bkg))
    if (minimum>=maximum):
        raise ValueError, "The variable seems to be constant!"
        return None
    stepsize = float(maximum-minimum)/100
    
    cut = minimum+stepsize #I cannot start from the minimum otherwise n_low will be zero
    D_min = None #entropy
    while (cut<=maximum):
        D=0
        n_sig_low = float(sig.loc[sig<cut].count())
        n_sig_high = float(sig.loc[sig>cut].count())
        n_bkg_low = float(bkg.loc[bkg<cut].count())
        n_bkg_high = float(bkg.loc[bkg>cut].count())
        n_high = n_sig_high + n_bkg_high
        n_low = n_sig_low + n_bkg_low
        T = n_high + n_low

        if n_sig_low != 0 and n_bkg_low != 0 :
            D += - (n_low/T)*(  (n_sig_low / n_low)*log(n_sig_low / n_low) + (n_bkg_low / n_low)*log(n_bkg_low / n_low) )
        if n_sig_high != 0 and n_bkg_high != 0 :
            D += - (n_high/T)*( (n_sig_high / n_high)*log(n_sig_high / n_high) + (n_bkg_high / n_high)*log(n_bkg_high / n_high) )
        
        if ((D<D_min) or D_min==None): D_min = D #I'm looking for the minimum D
        
        cut = cut+stepsize
        
    return {'min entropy' : D_min, 'best cut' : cut-stepsize}


def entropy_normalised(sig_data, bkg_data, variable):
    
    sig = sig_data[variable]
    bkg = bkg_data[variable]
    
    minimum = min(np.min(sig), np.min(bkg))
    maximum = max(np.max(sig), np.max(bkg))
    if (minimum>=maximum):
        raise ValueError, "The variable, {0}, seems to be constant!".format(variable)
        return None
    stepsize = float(maximum-minimum)/100
    
    cut = minimum+stepsize #I cannot start from the minimum otherwise n_low will be zero
    D_min = None #entropy
    while (cut<=maximum):
        D=0
        n_sig = float(sig.count())
        n_bkg = float(bkg.count())
        f_sig_low = float(sig.loc[sig<cut].count())/n_sig #now these are fractions, normalised to nsig or nbkg
        f_sig_high = float(sig.loc[sig>cut].count())/n_sig #now these are fractions, normalised to nsig or nbkg
        f_bkg_low = float(bkg.loc[bkg<cut].count())/n_bkg #now these are fractions, normalised to nsig or nbkg
        f_bkg_high = float(bkg.loc[bkg>cut].count())/n_bkg #now these are fractions, normalised to nsig or nbkg
        f_high = f_sig_high + f_bkg_high
        f_low = f_sig_low + f_bkg_low
        T = f_high + f_low

        if f_sig_low != 0 and f_bkg_low != 0 :
            D += - (f_low/T)*(  (f_sig_low / f_low)*log(f_sig_low / f_low) + (f_bkg_low / f_low)*log(f_bkg_low / f_low) )
        if f_sig_high != 0 and f_bkg_high != 0 :
            D += - (f_high/T)*( (f_sig_high / f_high)*log(f_sig_high / f_high) + (f_bkg_high / f_high)*log(f_bkg_high / f_high) )
        
        if ((D<D_min) or D_min==None): D_min = D #I'm looking for the minimum D
        
        cut = cut+stepsize
        
    return {'min entropy' : D_min, 'best cut' : cut-stepsize}
