from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
pp   = PdfPages('outmy02plot.pdf')
tmp1 = plt.figure(1)
plot = open('outmy02plot-0.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', label=r'$p_{\perp}$ of $2 \to 2$ process')
plt.yscale('symlog', linthreshy=1.57e+02)
plt.legend(frameon=False,loc='best')
plt.title(r'$p_{\perp}$ scale of hard interaction')
plt.xlabel(r'$p_{\perp}$ (GeV)')
plt.ylabel(r'$\mathrm{d}\sigma/\mathrm{d}p_{\perp}$ (nb/GeV)')
pp.savefig(tmp1,bbox_inches='tight')
plt.clf()
tmp2 = plt.figure(2)
plot = open('outmy02plot-1.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='royalblue', label=r'total')
plot = open('outmy02plot-2.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='orange', label=r'charged (even only!)')
plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,3))
plt.legend(frameon=False,loc='best')
plt.title(r'Total and charged particle multiplicities')
plt.xlabel(r'$n$')
plt.ylabel(r'$\mathrm{d}P/\mathrm{d}n$')
pp.savefig(tmp2,bbox_inches='tight')
plt.clf()
tmp3 = plt.figure(3)
plot = open('outmy02plot-3.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'$\mathrm{d}n_{\mathrm{charged}}/\mathrm{d}y$')
plot = open('outmy02plot-4.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '--', color='magenta', label=r'$\mathrm{d}n_{\mathrm{charged}}/\mathrm{d}\eta$')
plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,3))
plt.legend(frameon=False,loc='best')
plt.title(r'Charged (pseudo)rapidity distribution')
plt.xlabel(r'$y$ or $\eta$')
plt.ylabel(r'$\mathrm{d}n_{\mathrm{charged}}/\mathrm{d}(y/\eta)$')
pp.savefig(tmp3,bbox_inches='tight')
plt.clf()
tmp4 = plt.figure(4)
plot = open('outmy02plot-5.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', label=r'charged')
plt.yscale('symlog', linthreshy=9.80e-01)
plt.legend(frameon=False,loc='best')
plt.title(r'Charged $p_{\perp}$ spectrum')
plt.xlabel(r'$p_{\perp}$ (GeV)')
plt.ylabel(r'$\mathrm{d}n_{\mathrm{charged}}/\mathrm{d}p_{\perp}$ (GeV$^{-1}$)')
pp.savefig(tmp4,bbox_inches='tight')
plt.clf()
tmp5 = plt.figure(5)
plot = open('outmy02plot-6.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'$\gamma$')
plot = open('outmy02plot-7.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'$\mu^{\pm}$')
plot = open('outmy02plot-8.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'$\pi^{\pm}$')
plot = open('outmy02plot-9.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'$\nu$')
plot = open('outmy02plot-10.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
plt.plot( valx, valy, '-', label=r'others')
plt.yscale('symlog', linthreshy=2.50e-03)
plt.legend(frameon=False,loc='best')
plt.title(r'Particle energy spectra')
plt.xlabel(r'$E$ (GeV)')
plt.ylabel(r'$(1/N_{\mathrm{event}}) \mathrm{d}N / \mathrm{d}E$ (GeV$^{-1}$)')
pp.savefig(tmp5,bbox_inches='tight')
plt.clf()
pp.close()
