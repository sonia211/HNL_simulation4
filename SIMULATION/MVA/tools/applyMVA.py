#author: Guido Andreassi <guido.andreassi@cern.ch>
import pandas as pd

def applyMVA(k_classifiers, cl_name, data, invert_folds=False):
    
    k = len(k_classifiers) #number of folds
    
    #define the k samples for the whole background
    data_folds = []

    if invert_folds: #this is used to apply the MVA on the same folds on which it is trained, e.g. to obtain the "training sample" distributions
        print "Inverting folds"
        for i in range(k):
            data_folds.append(data.loc[data['eventNumber']%k!=i])
    else: #regular case
        for i in range(k):
            data_folds.append(data.loc[data['eventNumber']%k==i])        

        
    # X-check
    adj = 1. if not invert_folds else k-1 #if I'm summing over all the k-1 training sample for each k, then I have N+(k-1) events instead of N
    tot = data.shape[0]*adj
    for i in range(k):
        tot = tot-data_folds[i].shape[0]
    if (tot!=0):
        raise Exception("Something went wrong in the splitting in k-folds!")
    
    #produce the classifier's output
    outputs = []
    for i in range(k):
        print "Applying MVA to fold", i , "..."
        predicted_prob = k_classifiers[i].predict_proba(data_folds[i])
        outputs.append([a[1]-a[0] for a in predicted_prob])
    print "Done!"
    
    #add predictions to each single fold
    data_folds_with_pred = []
    for i in range(k):
        this = data_folds[i].copy()
        this[cl_name] = pd.Series(outputs[i], index=this.index)
        data_folds_with_pred.append(this)
        
    #now we put all the folds together, with their prediction, keeping the correct indices, and then we reorder by the inices
    #so we preserve the order, which is crucial for adding the branch correctly to the data file!
    data_with_pred = pd.concat(data_folds_with_pred) #add column with mva output
    data_with_pred=data_with_pred.sort_index() #order indices
    
    return data_with_pred