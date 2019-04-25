#By Guido Andreassi. Adapted from Tim Head: http://betatim.github.io/posts/sklearn-for-TMVA-users/

from scipy import stats
import matplotlib.pyplot as plt
import numpy as np
from applyMVA import applyMVA

def compare_train_test(clf, name, signal_train, background_train, signal_test=None, background_test=None, bins=30, do_plot=True, pdf_file_name=None, k_folding=False, use_weights=False):
    
    decisions = []
    data_with_pred = []

    """
    for data in (signal_train, background_train, signal_test, background_test):
        prob = clf.predict_proba(data)
        prob0 = [item[0] for item in prob]
        prob1 = [item[1] for item in prob]
        decisions.append([b-a for a, b in zip(prob0, prob1)])
    """

    if k_folding:
        if ((signal_test is not None) or (background_test is not None)):
            raise Exception("compare_train_test", "With k-folding, there should be no test sample!")
            return -1
        for data in (signal_train, background_train): #analogous to train distributions
            data_with_pred.append(applyMVA(clf, "temp_classifier_name",data,invert_folds=True))
            decisions.append(data_with_pred[-1]["temp_classifier_name"].as_matrix().copy())
        for data in (signal_train, background_train): #analogous to test distributions
            data_with_pred.append(applyMVA(clf, "temp_classifier_name",data))
            decisions.append(data_with_pred[-1]["temp_classifier_name"].as_matrix().copy())
    else:
        for data in (signal_train, background_train, signal_test, background_test):
            data_with_pred.append(applyMVA(clf, "temp_classifier_name",data))
            decisions.append(data_with_pred[-1]["temp_classifier_name"].as_matrix().copy())

    low = min(np.min(d) for d in decisions)
    high = max(np.max(d) for d in decisions)
    low_high = (low,high)

    ks_sig = stats.ks_2samp(decisions[0], decisions[2])
    ks_bkg = stats.ks_2samp(decisions[1], decisions[3])

    #print ks_sig[1], ks_bkg[1]

    p_value_text = "K-S test p-value:"
    p_value_text += "\n"
    p_value_text += "Sig: {:.2e}".format(ks_sig[1])
    p_value_text += "\n"
    p_value_text += "Bkg: {:.2e}".format(ks_bkg[1])

    if do_plot:
        plt.figure()

        plt.annotate(p_value_text, xy=(0.03, 0.95), xycoords='axes fraction', fontsize=12,
                     horizontalalignment='left', verticalalignment='top')

        w=data_with_pred[0]["weight"] if use_weights else None
        plt.hist(decisions[0],
                 color='b', alpha=0.5, range=low_high, bins=bins,
                 histtype='stepfilled', normed=True,
                 label='S (train)',
                 weights=w
                 )
        w=data_with_pred[1]["weight"] if use_weights else None
        plt.hist(decisions[1],
                 color='r', alpha=0.5, range=low_high, bins=bins,
                 histtype='stepfilled', normed=True,
                 label='B (train)',
                 weights=w
                 )


        w=data_with_pred[2]["weight"] if use_weights else None
        hist, bins = np.histogram(decisions[2],
                                  bins=bins, range=low_high, normed=True, weights=w)
        scale = len(decisions[2]) / sum(hist)
        err = np.sqrt(hist * scale) / scale

        width = (bins[1] - bins[0])
        center = (bins[:-1] + bins[1:]) / 2
        plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='S (test)')

        w=data_with_pred[3]["weight"] if use_weights else None
        hist, bins = np.histogram(decisions[3],
                                  bins=bins, range=low_high, normed=True, weights=w)
        scale = len(decisions[2]) / sum(hist)
        err = np.sqrt(hist * scale) / scale
        plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='B (test)')

        plt.xlabel(name+" classifier response")
        plt.ylabel("Arbitrary units")
        plt.legend(loc='best')
        plt.savefig(pdf_file_name) ##add python saving!
        plt.show()
    return [ks_sig, ks_bkg]

