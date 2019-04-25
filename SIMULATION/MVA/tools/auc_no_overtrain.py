from sklearn.metrics import roc_auc_score
from tools.compare_train_test import compare_train_test
from sklearn.base import clone

"""
this function will return the integral under the roc curve of a certain trained classifier multiplied by -1 if the classifier is overtrained.
In such a way, overtrained classifiers will get a bad score during parameters optimisation.
"""
class auc_no_overtrain(object):
    
    train_data_signal = None
    train_data_background = None
    test_data_signal = None
    test_data_background = None
    test_data = None
    test_labels = None
    train_data = None
    train_labels = None
    
    def __init__(self, train_data, test_data):
        self.train_data_signal = train_data.loc[train_data['labels']>0.5]
        self.train_data_background = train_data.loc[train_data['labels']<0.5]
        self.test_data_signal = test_data.loc[test_data['labels']>0.5]
        self.test_data_background = test_data.loc[test_data['labels']<0.5]

        self.test_data = test_data
        self.test_labels = test_data['labels'].tolist() 
        self.train_data = train_data
        self.train_labels = train_data['labels'].tolist() 

        
    def __call__(self, base_estimator, params, X, y, sample_weight=None):
        cl = clone(base_estimator)
        cl.set_params(**params)
        cl.fit(X, y)
        significance_level = 0.05
        pred = cl.predict_proba(self.test_data)
        
        ks = compare_train_test(cl, "", self.train_data_signal, self.train_data_background, self.test_data_signal,
                                self.test_data_background, bins=30, do_plot=False) #ks now contains [ks_sig, ks_bkg]
        #fill ks_is_ok with 1 if ks p_value > significance level and -1 otherwise
        ks_sig_is_ok = 1 if ks[0][1]>significance_level else 0 #ks[n][1] is the p-value of the kolmogorov-smirnov test on the n-th sample (sig-bkg)
        ks_bkg_is_ok = 1 if ks[1][1]>significance_level else 0 #ks[n][1] is the p-value of the kolmogorov-smirnov test on the n-th sample (sig-bkg)
        ks_is_ok = ks_sig_is_ok*ks_bkg_is_ok

        auc = roc_auc_score(self.test_labels, pred[:, 1])
        return ks_is_ok*auc