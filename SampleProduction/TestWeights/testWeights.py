import ROOT
ROOT.gROOT.SetBatch()
from DataFormats.FWLite import Events, Handle
labelMC = "addMCWeight"
labelPileup = "addPileupInfo"
events = Events("myOutputFile.root")
mcweightHandle = Handle('std::vector<double>')
mcPileupInfoHandle = Handle("vector<double>")
weights_2d = ROOT.TH2D("weights_2d","",200,0.0,20,20,-200,200)
numEvents_pos = ROOT.TH1D("numEvents_pos","",200,0,20)
numEvents_neg = numEvents_pos.Clone("numEvents_neg")
for event in events:
 try:
  event.getByLabel(labelMC,mcweightHandle)
  mcWeights=mcweightHandle.product()
  event.getByLabel(labelPileup,mcPileupInfoHandle)
  pileupWeights=mcPileupInfoHandle.product()
  # print "mcWeights ",mcWeights[0], "  pileupWeights ", pileupWeights[0]
  weights_2d.Fill(pileupWeights[0],mcWeights[0])
  if mcWeights[0] > 0:
   numEvents_pos.Fill(pileupWeights[0])
  elif mcWeights[0] < 0:
   numEvents_neg.Fill(pileupWeights[0])
  else:
   print "warning weight 0"
 except (KeyboardInterrupt, SystemExit):
  print "earlier stop"
  break
#
c1=ROOT.TCanvas("c1","",200,10,3000,500)
c1.cd()
weights_2d.Draw("TEXTBOX")
c1.SaveAs(c1.GetName()+".pdf")

for i in range(weights_2d.GetNbinsX()+2):
 for j in range(int(weights_2d.GetNbinsY()/2.0)+1):
  if weights_2d.GetBinContent(i,weights_2d.GetNbinsY()+1-j) > 0:
   ratio = weights_2d.GetBinContent(i,j)/weights_2d.GetBinContent(i,weights_2d.GetNbinsY()+1-j)
   if ratio > 0:
    print "bin ",i,"  pos entries ",weights_2d.GetBinContent(i,j)," pileupweight ","  ratio ",ratio

c2=ROOT.TCanvas("c2","",200,100,700,500)
c2.cd()
numEvents_neg.Sumw2()
numEvents_pos.Sumw2()
numEvents_div = numEvents_neg.Clone("numEvents_div")
numEvents_div.Divide(numEvents_pos)
numEvents_div.Draw()
c2.SaveAs(c2.GetName()+".pdf")
