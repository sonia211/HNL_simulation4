import matplotlib
matplotlib.use('Agg')
#from matplotlib import pyplot as plt
import pylab as plt
import matplotlib.colors as colors
from matplotlib.backends.backend_pdf import PdfPages
import numpy as np

import sys
sys.path.insert(0, '../FairShip/python')
from hnl import *

import yaml
#HNL decay


with open("./cfg_files/cfg_scan.yml", 'r') as stream:
    try:
        cfg_file = yaml.safe_load(stream)
    except yaml.YAMLError as exc:
        print(exc)


x = cfg_file['mNvec']; #x=x[0:len(x)-1]
x=np.array(x)
print "\n type mNvec", type(x)
y = cfg_file['U2vec']
y=np.array(y)



#o_tau0   = PdfPages('o_tau0.pdf')
#o_decBR  = PdfPages('o_decBR.pdf')

p_tau0   = np.loadtxt( './hnltau0_ch1.dat' )
p_decBR  = np.loadtxt( './hnldecayBR_ch1.dat')
p_prodBR  = np.loadtxt( '../br_prod_B0.dat')
p_prodBR_B  = np.loadtxt( '../br_prod_B.dat')
p_prodBR_Bc  = np.loadtxt( '../br_prod_Bc.dat')
#declare 3 arrays of constant U2

br_U2_a =	p_prodBR[:,0]					# all masses, U2 = 1e-9, el 0
br_U2_b =	p_prodBR[:,3]					# all masses, U2 = 1e-6, el 3
br_U2_c =	p_prodBR[:,6]					# all masses, U2 = 1e-3, el 6
#U2_a =	p_decBR[]					# all masses, U2 = 1e-1, el 8

br_B0 = p_prodBR[:,3]					
br_B  = p_prodBR_B[:,3]	
br_Bc = p_prodBR_Bc[:,3]	



print "brU2a", br_U2_a

print "brU2b", br_U2_b
print "brU2c", br_U2_c
#im1 = plt.imshow(p_tau0, cmap='hot')
#plt.colorbar(im1, orientation='vertical')
#plt.xscale('log')
#plt.show()
#plt.savefig('o_tau0.pdf')


# BEAUTIFUL GRAPH TEMPLATE
from matplotlib import rc
#rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
## for Palatino and other serif fonts use:
#rc('font',**{'family':'serif','serif':['Palatino']})
#rc('text', usetex=True)

'''
plt.figure()
im2 = plt.pcolormesh(x,y,p_prodBR.T,norm=colors.LogNorm(vmin=p_prodBR.min(), vmax=p_prodBR.max()))
plt.colorbar(im2, orientation='vertical')
plt.yscale('log')
#plt.rc('text', usetex=True)
#plt.rc('font', family='serif')
plt.xlabel("$m_N$ [GeV]"); plt.ylabel("$U_{\mu}^{2}$")
plt.show()
plt.savefig('o_prodBR.pdf')
#plt.imshow(p_decBR)
#plt.show()
'''

######### SEVERAL BR for fixed U2
#with plt.style.context('Solarize_Light2'):

'''
plt.figure()
plt.yscale('log')
plt.plot(x, br_U2_c, color='blue', label='$U_{\mu}^{2} = 10^{-3}$')
plt.plot(x, br_U2_b, color='skyblue', label='$U_{\mu}^{2} = 10^{-6}$')
plt.plot(x, br_U2_a, color='olive', label='$U_{\mu}^{2} = 10^{-9}$')


plt.legend()

plt.title('BR prod from B0')
plt.xlabel("$m_N$ [GeV]", fontsize=14)
plt.ylabel('BR', fontsize=14)
    
plt.savefig('o_prodBR_several.pdf')
plt.show()
'''
#------------------------------------------
plt.figure()
plt.yscale('log')
plt.plot(x, br_B0, color='blue', label='$B_0$')
plt.plot(x, br_B, color='skyblue', label='$B^+$')
plt.plot(x, br_Bc, color='olive', label='$B_c$')


plt.legend()

plt.title('BR prod from B0')
plt.xlabel("$m_N$ [GeV]", fontsize=14)
plt.ylabel('BR', fontsize=14)
    
plt.savefig('o_prodBR_allBmesons_U1em6.pdf')
plt.show()





