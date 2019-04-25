#author: Guido Andreassi <guido.andreassi@cern.ch>

from tools.applyMVA import applyMVA
from rootpy.io import root_open
import root_numpy
from tools.loadtuples import loadtuples

def MVA2root(k_classifiers = [], classifier_name="", inputfilenames=[], tuplename = "", max_files_atatime=50, branches=[], outfilenameroot = "test", fix_features_names_for_MVA=True, cuts="", fixvar={}):
    
    data_pandas, data_tree = loadtuples(file_names = inputfilenames,
                                        tuplename = tuplename,
                                        max_files_atatime = max_files_atatime,
                                        branches = branches,
                                        cuts = cuts,
                                        fixvar = fixvar)
    if (fix_features_names_for_MVA):
        for these_data in data_pandas:
            these_data.columns = [var.replace("+","_mathPLUS_").replace("-","_mathMINUS_").replace("*","_mathTIMES_").replace("/","_mathOVER_") for var in these_data.columns]
    
    for i in range (len(data_pandas)):
        print "Processing chunk", i, "of", len(data_pandas), "..."
        data_pandas_with_pred=applyMVA(k_classifiers, classifier_name,data_pandas[i])
        mva_column=data_pandas_with_pred[classifier_name].as_matrix().copy() 
        mva_column.dtype=[(classifier_name, '<f8')]
        with root_open(outfilenameroot+"_{0}.root".format(i), mode='RECREATE') as myfile:
            t = root_numpy.array2tree(mva_column, tree=data_tree[i])
            t.SetName("DecayTree")
            t.SetTitle("DecayTree")
            t.Write("",t.kWriteDelete);
            print "Writing output file with the following content: "
            myfile.ls()
            myfile.write()
        del data_pandas_with_pred
        del mva_column
