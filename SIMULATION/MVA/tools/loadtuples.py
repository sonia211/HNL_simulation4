#author: Guido Andreassi <guido.andreassi@cern.ch>
#this function takes a list of root files and returns a list of TChains containing the corresponding tuples (tuplename) along with the corresponding pandas dataframes

def loadtuples(file_names = [], tuplename = "", max_files_atatime = 50, branches=[], cuts="", fixvar={}):
    from glob import glob
    import ROOT
    import root_numpy
    import pandas as pd
    
    #remove fixed variables.  fixvar must be a dictionary structured like {Name_of_var : fixed_value}
    for var, default in fixvar.iteritems():
        branches.remove(var)
    
    l = []
    for file_name in file_names: #file_names can contain regexp, e.g. "*.root"
        l.extend(glob(file_name)) #convert file_names into a list of legit file names
    lofl=[]
    all_data_tree=[] #list of the chains
    pd_data=[]
    #split input files in chunks of size max_files_atatime
    for i in range(0, len(l), max_files_atatime):
        these_files = l[i:i+max_files_atatime]
        this_chain = (ROOT.TChain(tuplename))
        for file in these_files:
            this_chain.AddFile(file)
        these_pd_data = root_numpy.tree2array(tree=this_chain,selection=(cuts), branches=branches)
        pd_data.append(pd.DataFrame(these_pd_data))
        all_data_tree.append(this_chain.CopyTree(cuts))
        #fix variables to be fixed.
        for var, default in fixvar.iteritems():
            pd_data[-1][var] = default
        
    return pd_data, all_data_tree