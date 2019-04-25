from __future__ import print_function #this makes it compatible with python 3, which I need in snakemake


template="""
import sys, os
print "pythonpath:", os.environ['PYTHONPATH']
print "path:", os.environ['PATH']

decay = "{decay}"
from Lb2LemuEnv import db
k = db["MVA_k_folding_k"]
best_classifier_name="{best_classifier_name}"
classifier_name_suffix="{classifier_name_suffix}"
classifiers_dir = os.environ['LB2LEMUROOT']+'/MVA/classifiers/'
classifiers_subdir = "/trained_"+best_classifier_name+str({tag})+"_"+decay+"/"
dir_name = classifiers_dir+classifiers_subdir
if not os.path.exists(dir_name):
    raise Exception("Cannot find the classifiers folder!")
   
#X-checking
from glob import glob
if (len(glob(dir_name+best_classifier_name+"_k*.pickle.dat"))!=k):
    raise Exception("Number of folds != number of classifiers found in", dir_name)
    exit

import cuts
cut = ""
if {cuts}:
    try:
        cut = getattr(cuts, {cuts}).GetTitle()
    except:
        cut = {cuts}

print "Using the following cut: ", cut


#retrieve trained classifier
import pickle

k_classifiers=[]
for i in range(k):
    file_name = dir_name+best_classifier_name+"_k"+str(i)+".pickle.dat"
    k_classifiers.append(pickle.load(open(file_name, "r")))
    
if os.path.exists(file_name):
        best_classifier = pickle.load(open(file_name, "r"))
else: raise Exception("Cannot find the classifier!")
    
branches = k_classifiers[0].features
branches = [var.replace("_mathPLUS_", "+").replace("_mathMINUS_", "-").replace("_mathTIMES_", "*").replace("_mathOVER_", "/") for var in branches]
additional_branches = ['Lb_M', 'eventNumber'] #spectator variables and others


from tools.MVA2root import MVA2root

MVA2root (k_classifiers,
          classifier_name=best_classifier_name+str({tag})+classifier_name_suffix,
          inputfilenames = {inputfilenames},
          tuplename = "{tuplename}",
          max_files_atatime = 5,
          branches = branches+additional_branches,
          outfilenameroot = "{outfilenameroot}",
          fix_features_names_for_MVA = True,
          cuts=cut,
          fixvar = {fixvar}
         )
"""
#def oufilefolder_root(decay, tag, out_tag):
#    import os
#    return os.getenv("WGANAEOSLOC")+"tuples_with_MVA/"+decay+"/"+str(tag)+"/"+str(out_tag)


def apply(opts):
    
    fixvar = "{}"
    classifier_name_suffix=""
    if opts.fixhop:
        fixvar = "{'Lb_HOP' : 1}" #for fixing hop
        classifier_name_suffix="_fixhop"
    import sys
    import os
    from glob import glob

    infiles=[]
    #infiles.extend(glob(os.getenv("LBMICKJOBLOC")+"209/*/DVNtuple.root"))
    #infiles.extend(glob(os.getenv("LBMICKJOBLOC")+"210/*/DVNtuple.root"))
    #infiles.extend(glob("/eos/lhcb/user/g/gandreas/Lb2Lemu/tuples/S28/25122017/job*/LbLemu_BDT_*.root"))
    #infiles=["/eos/lhcb/user/g/gandreas/Lb2Lemu/tuples/S28/25102017/Lb2Lemu_BDT.root"]
    for name in opts.infiles_names:
        infiles.extend(glob(name))

    jobs_macro_folder = os.environ["LB2LEMUROOT"]+"/MVA/apply_jobs"
    stdout_folder=jobs_macro_folder+"/batchout/"
    try:
        os.stat(jobs_macro_folder)
    except:
        os.mkdir(jobs_macro_folder)
    try:
        os.stat(stdout_folder)
    except:
        os.mkdir(stdout_folder)

    print ("I'm going to process", len(infiles), "files... Be patient.")
    n = 50 #size of chunk of files
    print ("Splitting the files in chunks of size", n, ", one chunk per job.")


    for i in range(0, len(infiles), n):

        #define outplut folder, and create it if it donesn't exist
        k = opts.outfilename.rfind("/")
        outfilefolder = opts.outfilename[:k]+"/job"+str(i)
        try:
            os.stat(outfilefolder)
        except:
            os.makedirs(outfilefolder)

        k2 = opts.outfilename.rfind(".")
        outfilenameroot = outfilefolder+"/"+opts.outfilename[k:k2]

        macro_name=jobs_macro_folder+"/macro_"+str(i)+".py"

        with open(macro_name, 'wb') as f:
            f.write(
                template.format(
                    tag = opts.tag,
                    decay = opts.decay,
                    best_classifier_name=opts.best_classifier_name,
                    tuplename=opts.tuplename,
                    classifier_name_suffix=classifier_name_suffix,
                    inputfilenames=infiles[i:i + n],
                    outfilenameroot=outfilenameroot,
                    fixvar = fixvar,
                    cuts=opts.cuts
                )
            )

        #os.system("python {0}/pyutils/processing/submit.py -d MVA_apply_{1}  -s 'source {0}/scripts/setup.sh; cd {0}/MVA'  -D {3} -c 'python {2}'".format(os.environ["LB2LEMUROOT"], str(i), macro_name, stdout_folder))

        os.system("python {0}/pyutils/processing/submit.py -d MVA_apply_{1}  -s 'cd {0}/MVA'  -D {3} -c 'python {2}'".format(os.environ["LB2LEMUROOT"], str(i), macro_name, stdout_folder))

    
    
    
    
    
    

########## PARSER ###########
from argparse import ArgumentParser
parser = ArgumentParser()
parser.add_argument('-t', "--tag", default=-1, dest="tag", type=int, 
                    help="Tag of the MVA", required=False) #if not set, it will be taken from the db
parser.add_argument('-c', "--cl_name", default="", dest="best_classifier_name", 
                    help="Name of the desired classifier", required=False) #if not set, it will be taken from the db
parser.add_argument('-d', "--decay", default="emu", dest="decay", 
                    help="Decay (emu, ee)", required=True)
parser.add_argument('-f', "--fixhop", default=False, dest="fixhop", type=bool,
                    help="Flag for fixing hop", required=False)
parser.add_argument('-i','--input-files', nargs='+', dest="infiles_names",#infiles_names is a list
                    help='List of input files (regexp allowed)', required=True)
parser.add_argument('-n','--tuple-name', dest="tuplename", type=str,
                    help='Name/path of the tuple inside the file', required=True)
parser.add_argument('-o','--output-file', dest="outfilename", type=str,#infiles_names is a list
                    help='Output file name format', required=True)
parser.add_argument('-s','--cuts', dest="cuts", type=str, default = "''",
                    help='Cuts to apply. It accepts a name of a cut existing in cuts.py , or a string like "cuts.cut1+cuts.cut2...')





# Main
if __name__ == "__main__" :
    from Lb2LemuEnv import db
    opts = parser.parse_args()
    if opts.tag is -1:
        opts.tag = db["best_classifier_tag_"+opts.decay]
    if not opts.best_classifier_name:
        opts.best_classifier_name = db["best_classifier_name_"+opts.decay]
    print(opts)
    apply(opts)

