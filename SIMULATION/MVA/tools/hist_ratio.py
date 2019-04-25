import ROOT

class hist_ratio:
    
    h1=None
    h2=None
    c=None
    s=None
    
    def __init__(self, h1=None, h2=None, normalize=True):
        if (normalize):
            h1.Scale(1./h1.Integral())
            h2.Scale(1./h2.Integral())
        self.h1=h1
        self.h2=h2
        self.h_ratio = h2.Clone() #h_ratio = h1/h2
        self.h_ratio.SetName("MVA_rw"+h2.GetName())
        self.h_ratio.SetTitle("Weighs")
        self.h_ratio.Divide(h1)

        self.leg_x1 = 0.2
        self.leg_y1 = 0.65
        self.leg_x2 = 0.5
        self.leg_y2 = 0.85   

        self.y_title = "Events [a.u.]"
        
    def get_h_ratio(self):
        return self.h_ratio

    def save_h_ratio(self, filename):
        f = ROOT.TFile.Open(filename, "recreate")
        f.cd()
        self.h_ratio.Write()
        f.Close()
        del f

    def set_legend_xyxy(self, leg_x1, leg_y1, leg_x2, leg_y2):
        self.leg_x1 = leg_x1
        self.leg_y1 = leg_y1
        self.leg_x2 = leg_x2
        self.leg_y2 = leg_y2       


    def set_y_title(self, y_title):
        self.y_title = y_title   
        
    def Plot(self):
        self.c = ROOT.TCanvas("c"+self.h1.GetName())
        self.c.cd()
        self.pad1 = ROOT.TPad("pad1"+self.h1.GetName(), "pad1"+self.h1.GetName(), 0, 0.3, 1, 1.0) #histos
        self.pad1.SetBottomMargin(0.03)
        self.pad1.Draw()
        self.pad1.cd()
        self.h1.SetLineColor(ROOT.kBlue)
        self.h1.SetMarkerSize(0)#needed to avoid having the point appearing in the legend
        self.h2.SetLineColor(ROOT.kRed)
        self.h2.SetMarkerSize(0)#needed to avoid having the point appearing in the legend
        self.s = ROOT.THStack("hstack", "")
        self.s.Add(self.h1, "hist")
        self.s.Add(self.h2, "hist")
        self.s.Draw("nostack")
        self.s.GetXaxis().SetLabelSize(0)
        self.s.GetYaxis().SetLabelSize(0.08)
        self.s.GetYaxis().SetTitle(self.y_title)
        ROOT.gPad.BuildLegend(self.leg_x1, self.leg_y1, self.leg_x2, self.leg_y2)
        self.c.cd()
        self.pad2 = ROOT.TPad("pad2"+self.h1.GetName(), "pad2"+self.h1.GetName(), 0, 0.03, 1, 0.3) #ratio
        self.pad2.SetTopMargin(0.1)
        self.pad2.SetBottomMargin(0.4)
        self.pad2.Draw()
        self.pad2.cd()
        self.h_ratio.Draw()
        self.h_ratio.GetYaxis().SetTitle("Ratio")
        self.h_ratio.GetYaxis().SetNdivisions(503, ROOT.kTRUE)
        self.h_ratio.GetYaxis().SetRangeUser(0,2.0)
        self.h_ratio.GetXaxis().SetTitle("MVA output")
        self.h_ratio.GetXaxis().SetTitleSize(0.2)
        self.h_ratio.GetXaxis().SetLabelSize(0.2)
        self.h_ratio.GetYaxis().SetLabelSize(0.2)
        self.h_ratio.GetYaxis().SetTitleSize(0.18)
        self.h_ratio.GetYaxis().SetTitleOffset(0.39)
        self.h_ratio.SetLineColor(ROOT.kBlack)

        #draw line on 1
        self.l=ROOT.TLine(self.s.GetXaxis().GetXmin(),1,self.s.GetXaxis().GetXmax(),1)
        self.l.SetLineStyle(3)
        self.l.Draw()

        return self.c
              
    def saveAs(self, plotfilename):
        if self.c==None:
            raise Exception("The canvas does not exist. Did you call Plot first?")
            return
        self.c.SaveAs(plotfilename)
        
    def saveAsCandPdf(self, plotfilename):
        self.saveAs(plotfilename+".pdf")
        self.saveAs(plotfilename+".C")
