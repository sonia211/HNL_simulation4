import root_numpy
import numpy as np
import pandas as pd
from sklearn.cross_validation import train_test_split

def convert_data (signal_tree, signal_cut, background_tree, background_cut, variables, test_frac=0.33,  match_sample_sizes=False, default_err=float('NaN')):

    from cuts import strip_variables

    #################################################################################################
    #check that the required branches exist
    #This allows you to request for a variables that is there on signal and not on MC, or vice-versa.
    #That variable, will then be added where it exists, and it will be replaced by the default_err where not.
    #On signal...
    list_of_branches = [x.GetName() for x in signal_tree.GetListOfBranches()]
    stripped_branches = strip_variables(variables)
    list_of_missing_branches_sig = [x for x in stripped_branches if x not in list_of_branches]
    list_of_missing_variables_sig = []
    for var in variables:
      if any(x in var for x in list_of_missing_branches_sig):
        list_of_missing_variables_sig.append(var)
    print "Found the following missing variables in signal:"
    print list_of_missing_variables_sig
    #...and on bkg
    list_of_branches = [x.GetName() for x in background_tree.GetListOfBranches()]
    list_of_missing_branches_bkg = [x for x in stripped_branches if x not in list_of_branches]
    list_of_missing_variables_bkg = []
    for var in variables:
      if any(x in var for x in list_of_missing_branches_bkg):
        list_of_missing_variables_bkg.append(var)
    print "Found the following missing variables in background:"
    print list_of_missing_variables_bkg
    #################################################################################################

    #take signal
    signal_np = root_numpy.tree2array(tree=signal_tree,
                                      branches=[x for x in variables if x not in list_of_missing_variables_sig], #removing branches that are not there
                                      selection=signal_cut)
    #now add missing branches with default error value
    for var in list_of_missing_variables_sig:
      signal_np = append_fields(signal_np, var, np.full(signal_np.shape[0], default_err), dtypes=int)

    signal = pd.DataFrame.from_records(signal_np) ##convert into pandas dataframe


    #take background
    background_np = root_numpy.tree2array(tree=background_tree,
                                       branches=[x for x in variables if x not in list_of_missing_variables_bkg], #removing branches that are not there
                                       selection=background_cut)
    #now add missing branches with default error value
    for var in list_of_missing_variables_sig:
      background_np = append_fields(background_np, var, np.full(background_np.shape[0], default_err), dtypes=int)

    background = pd.DataFrame.from_records(background_np) ##convert into pandas dataframe
    

    #adapt size of signal and background samples
    if match_sample_sizes:
        if (signal.shape[0] > background.shape[0]):
            signal = signal.sample(n=background.shape[0], random_state=2190)
        else:
            background = background.sample(n=signal.shape[0], random_state=2190)
            

    data = pd.concat([signal, background], axis=0)
    labels = np.concatenate((np.ones(signal.shape[0]),
                    np.zeros(background.shape[0])))
    
    train_data,test_data, train_labels,test_labels = train_test_split(data, labels,
                                                  test_size=test_frac, random_state=492)

    return train_data, train_labels, test_data, test_labels
