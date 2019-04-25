#This code is complementary to rep.report.metrics. It implements the Punzi fom as a metric available in REP.
#Implemented by Guido Andreassi <guido.andreassi@cern.ch>

from rep.report.metrics import *

#in analogy to OptimalSignificance, let's define OptimalPunziFOM
class OptimalPunziFOM(OptimalMetric):
    """
    Optimal values of Punzi FOM: eps(s) /(a/2 + sqrt(b))
    (a is the desired number of sigmas of a one-sided Gaussian test)

    :param float expected_s: expected amount of signal
    :param float expected_b: expected amount of background
    """
    

    def __init__(self, expected_s=1., expected_b=1.):
        OptimalMetric.__init__(self, metric=PunziFOM,
                               expected_s=expected_s,
                               expected_b=expected_b)
        
        
        
def PunziFOM(s, b):
    import numpy
    """
    :param s: amount (efficiency) of signal passed
    :param b: amount of background passed
    
    For simplicity, here a is set directly to 3
    """
    #print "s: ", s
    #print "b: ", b

    a=3. #significance, in number of sigmas
    return s / (a/2 + numpy.sqrt(b))
