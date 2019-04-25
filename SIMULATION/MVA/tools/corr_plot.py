#author: Guido Andreassi <guido.andreassi@cern.ch>
#implementation of class for plotting 2d histograms with Pearson correlation factor overlaid

import matplotlib as mpl
from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from vars_db import vars_db
import warnings
import pickle 
import numbers


class corr_plot():
    
    h = None
    ax = None
    corr = None
    
    def __init__(self, data, x, y,
                 bins, x_min=0, x_max=0, y_min=0, y_max=0, #binning
                 x_label=None, y_label=None, #axes labels
                 text_x=0.9, text_y=0.5): #position of the box with the correlation factor
        #convert DataFrame to numpy structured array
        if isinstance(data, pd.DataFrame): data = data.to_records()
            
        ######## sanity checks on inputs ########
        assert (isinstance(data, np.ndarray))
        assert isinstance(x, basestring)
        assert isinstance(y, basestring)
        assert isinstance(bins, list)
        assert all(isinstance(item, int) for item in bins)
        assert (len(bins) is 2)
        assert isinstance(x_label, basestring)
        assert isinstance(y_label, basestring)
        assert isinstance(text_x, float)
        assert isinstance(text_y, float)
        assert all(isinstance(item, numbers.Real) for item in [x_min,x_max, y_min,y_max])
        #########################################

        #create plot, compute correlation and print it on the plot
        self.ax = plt.subplot('111')
        plt.subplots_adjust(left=0.12, bottom=0.15, right=0.99, top=0.95)
        plt.hist2d(data[x], data[y], bins=bins)
        self.h = plt.gcf() #this, instead of directly h=plt.hist2d allows to be able to save the figure even after showing it. Otherwise it will save an empty canvas
        data_2vars = data[[x, y]]
        data_2vars = data_2vars.view((float, len(data_2vars.dtype.names))) #convert from numpy structured array to ndarray
        self.corr = np.corrcoef(data_2vars.transpose())[1,0]
        print "The correlation between {x} and {y} is {corr}".format(x=x, y=y, corr=self.corr)
        plt.text(text_x, text_y,'c = {0:.2f}'.format(self.corr), ha='center', va='center', transform=self.ax.transAxes, backgroundcolor="white")
        plt.colorbar()
        
        
        #put axes labels
        for xy, xy_label in zip([x,y], [x_label, y_label]):
            if ((xy_label == None) and (xy in vars_db)):
                xy_label = '${0}\, {1}$'.format(vars_db[xy]['title'], vars_db[xy]['unit']).replace('#', '\\')
            
        if x_label is not None:  
            plt.xlabel(x_label, fontsize=14)
        else: warnings.warn("No x label found", Warning)
        
        if y_label is not None:   
            plt.ylabel(y_label, fontsize=14)
        else: warnings.warn("No y label found", Warning)
            
        if x_min<x_max:
            self.ax.set_xlim(x_min, x_max)
        if y_min<y_max:
            self.ax.set_ylim(y_min, y_max)
    
    def get_hist(self): #just return the histogram
        return self.h
    
    def get_corr(self): #just return the histogram
        return self.corr
    
    def show_hist(self): #analogous to Draw in ROOT
        plt.show()
        
    def saveAs(self, filename): #flexible save function
        if filename.endswith(".py"): #In this case we want a "macro" (analogy with ROOT) then we have to save it with pickle.
            with open (filename, 'wb') as myfile:
                pickle.dump(self.ax, myfile)
        else:
            self.h.savefig(filename)