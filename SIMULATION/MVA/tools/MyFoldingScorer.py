from __future__ import division, print_function, absolute_import
from itertools import islice
from collections import OrderedDict
import logging
import copy
from scipy import stats
import numpy
from sklearn.base import clone
from sklearn.cross_validation import StratifiedKFold, KFold
from sklearn.ensemble.forest import RandomForestRegressor
from sklearn.utils.random import check_random_state

from six.moves import zip
from rep.estimators.utils import check_inputs
from rep.utils import fit_metric
from rep.metaml.utils import map_on_cluster
from rep.metaml.utils import get_classifier_probabilities, get_regressor_prediction

class FoldingScorerBase_no_overtrain(object):
    def __init__(self, score_function, folds=3, fold_checks=1, shuffle=False, random_state=None):
        """
        Scorer, which implements logic of data folding and scoring. This is a function-like object
        :param int folds: 'k' used in k-folding while validating
        :param int fold_checks: not greater than folds, the number of checks we do by cross-validating
        :param function score_function: quality. if fold_checks > 1, the average is computed over checks.
        """
        self.folds = folds
        self.fold_checks = fold_checks
        self.score_function = score_function
        self.shuffle = shuffle
        self.random_state = random_state

    def _compute_score(self, k_folder, prediction_function, base_estimator, params, X, y, sample_weight=None):
        """
        :return float: quality
        """
        score = 0
        significance_level = 0.05

        for ind, (train_indices, test_indices) in enumerate(islice(k_folder, 0, self.fold_checks)):
            estimator = clone(base_estimator)
            estimator.set_params(**params)

            trainX, trainY = X.iloc[train_indices, :], y[train_indices]
            testX, testY = X.iloc[test_indices, :], y[test_indices]
            decisions = []

            score_metric = copy.deepcopy(self.score_function)
            if sample_weight is not None:
                train_weights, test_weights = sample_weight[train_indices], sample_weight[test_indices]
                #modified by Guido Andreassi. The MLP classifier of sklearn is a bit different, and does not want weights in fit(). only in score().
                try: cc = estimator.clf
                except: cc=0
                if (str(type(cc)) == "<class 'sklearn.neural_network.multilayer_perceptron.MLPClassifier'>"):
                    estimator.fit(trainX, trainY)
                else:
                    estimator.fit(trainX, trainY, sample_weight=train_weights)
                fit_metric(score_metric, testX, testY, sample_weight=test_weights)
                prediction_test = prediction_function(estimator, testX) #I will separate this between train and test samples
                prediction_train = prediction_function(estimator, trainX)
                
                for prob in (prediction_test, prediction_train):
                    prob0 = [item[0] for item in prob]
                    prob1 = [item[1] for item in prob]
                    decisions.append([b-a for a, b in zip(prob0, prob1)])
                ks = stats.ks_2samp(decisions[0], decisions[1])  #ks[1] is the p-value of the kolmogorov-smirnov test on the n-th sample (sig-bkg)
                overtraining_penalisation = 1. if ks[1]>significance_level else 0.

                score += (score_metric(testY, prediction_test, sample_weight=test_weights)*overtraining_penalisation)
            else:
                estimator.fit(trainX, trainY)
                fit_metric(score_metric, testX, testY)
                
                prediction_test = prediction_function(estimator, testX) #I will separate this between train and test samples
                prediction_train = prediction_function(estimator, trainX)
                
                for prob in (prediction_test, prediction_train):
                    prob0 = [item[0] for item in prob]
                    prob1 = [item[1] for item in prob]
                    decisions.append([b-a for a, b in zip(prob0, prob1)])
                ks = stats.ks_2samp(decisions[0], decisions[1])  #ks[1] is the p-value of the kolmogorov-smirnov test on the n-th sample (sig-bkg)
                overtraining_penalisation = 1. if ks[1]>significance_level else 0.
                score += (score_metric(testY, prediction_test)*overtraining_penalisation)
        return score / self.fold_checks


class ClassificationFoldingScorer_no_overtrain(FoldingScorerBase_no_overtrain):
    """
    Scorer, which implements logic of data folding and scoring for classification models. This is a function-like object
    :param int folds: 'k' used in k-folding while validating
    :param int fold_checks: not greater than folds, the number of checks we do by cross-validating
    :param function score_function: quality. if fold_checks > 1, the average is computed over checks.
    Example:
    >>> def new_score_function(y_true, proba, sample_weight=None):
    >>>     '''
    >>>     y_true: [n_samples]
    >>>     proba: [n_samples, n_classes]
    >>>     sample_weight: [n_samples] or None
    >>>     '''
    >>>     ...
    >>>
    >>> f_scorer = FoldingScorer(new_score_function)
    >>> f_scorer(base_estimator, params, X, y, sample_weight=None)
    0.5
    """
    def __call__(self, base_estimator, params, X, y, sample_weight=None):
        """
        Estimate quality of estimator with given parameters with kFolding.
        :return float: quality
        """
        k_folder = StratifiedKFold(y=y, n_folds=self.folds, shuffle=self.shuffle, random_state=self.random_state)
        return self._compute_score(k_folder, get_classifier_probabilities, base_estimator, params, X, y,
                                   sample_weight=sample_weight)
