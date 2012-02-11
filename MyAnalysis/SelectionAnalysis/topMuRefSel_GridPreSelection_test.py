import ROOT, math

from DataFormats.FWLite import Events, Handle
import getopt, sys, decimal

from MyUtilities.MyFunctions.CosPhiSpinCorrlation_cfi import CosPhi
#from MyUtilities.MyFunctions.CosPhiSpinCorrlation_cfi import CosPhi
#from MyUtilities.MyFunctions.DeltaR_cfi import DeltaR
from MyUtilities.MyFunctions.AddAsymStatBox_cfi import AddAsymStatBox
from MyUtilities.MyFunctions.MyHistFunctions_cfi import SetErrorsNormHist
#from MyUtilities.MyFunctions.CosTheta1Theta2SpinCorrlation_cfi import CosTheta1Theta2
#from MyUtilities.MyFunctions.StatPadStyle1d_cfi import SetMy1dStyle,SetMy2dStyle
from MyUtilities.MyFunctions.StatBoxFunctions_cfi import GetStatBox
#from MyUtilities.MyFunctions.CreateNextCanvas_cfi import CreateNextCanvas,CreateNextCanvas2d
#from MyUtilities.MyFunctions.MySpinCorrelationPlotFunctions_cfi import Plot1dSpinCorrelationHist

opts, args = getopt.getopt(sys.argv[1:], 'i:p:m:',['inputfile=','postfix=','maxEvents='])
#print opts
#print args
postfix=''
maxEvents=-1
for opt,arg in opts:
 #print opt , " :   " , arg
 if opt in  ("-i","--inputfile"):
  filename=arg
 if opt in ("-p","--postfix"):
  postfix=arg
 if opt in ("-m","--maxEvents"):
  maxEvents=decimal.Decimal(arg)
events = Events (filename)#'patRefSel_muJets_semimuon_ttbar_MoreHyps_Reconstruction_SMAllPART.root')#patRefSel_muJets_nonsemimuon_ttbar_HitFit_Reconstruction.root')
myTrigResultslabel=("TriggerResults")
myTrigResultshandle=Handle("edm::TriggerResults")
ROOT.gROOT.SetBatch()
# Create histograms, etc.
ROOT.gROOT.SetStyle('Plain') # white background
ROOT.gStyle.SetOptStat("e")
ROOT.gStyle.SetOptFit(1)

h2_PreSelection_FullSelection = ROOT.TH2D ("h2_PreSelection_FullSelection", "PreSel vs FullSel",5,-2.5,2.5,5,-2.5,2.5)
# loop over events
evtNum=0
for event in events:
 evtNum=evtNum+1
 if maxEvents != -1 and evtNum > maxEvents:
  break
 event.getByLabel(myTrigResultslabel,myTrigResultshandle)
 myTrigResults=myTrigResultshandle.product()
 if evtNum == 1:
  TriggerNames=event.object().triggerNames(myTrigResults)
  print "following paths were found:"
  for i in range(len(TriggerNames)):
   print "path: ",TriggerNames.triggerName(i)
 h2_PreSelection_FullSelection.Fill( myTrigResults[0].accept(), myTrigResults[1].accept())
#################
ROOT.gStyle.SetOptStat("e")
c1=ROOT.TCanvas("c1","",700,300)
ROOT.gStyle.SetPadBorderMode(0)
ROOT.gStyle.SetFrameBorderMode(0)
c1.cd(1)
h2_PreSelection_FullSelection.Draw("TEXTBOX")
c1.SaveAs("h2_PreSelection_FullSelection.pdf")

