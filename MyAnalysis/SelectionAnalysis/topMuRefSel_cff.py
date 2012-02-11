import FWCore.ParameterSet.Config as cms
import sys
from FWCore.ParameterSet.VarParsing import VarParsing

def path(runOnMC):
 process = cms.Process( 'Selection' )
 
 #options = VarParsing ('analysis')
 #options.parseArguments()
 ## constants and switches to steer job
 ### Data or MC? Will change trigger Selection
 #runOnMC = True
 ### Standard and PF work flow
 usePFJets      = True
 # PF2PAT
 runPF2PAT = True
 ### Switch on/off selection steps
 # Step 0a
 useTrigger      = True
 # Step 0b
 useGoodVertex   = True
 # Step 1a
 useLooseMuon    = True
 # Step 1b
 useTightMuon    = True
 # Step 2
 useMuonVeto     = True
 # Step 3
 useElectronVeto = True
 # Step 4a
 use1Jet         = True
 # Step 4b
 use2Jets        = True #FH False
 # Step 4c
 use3Jets        = True #FH False
 # Step 5
 use4Jets        = True #FH False
 # Step 6
 useBTag         = False
 ### Conditions
 # GlobalTags (w/o suffix '::All')
 globalTagData = 'GR_R_44_V11' #GlobalTags (w/o suffix '::All')
 globalTagMC   = 'START44_V7' 
 ### OutputFile, Report, Summary, trigger matching
 outputFile = 'topMuRefSel_output.root'
 fwkReportEvery = 50
 wantSummary = True
 addTriggerMatching = True
 #import reference selection
 import TopQuarkAnalysis.Configuration.patRefSel_refMuJets as patRefSel_refMuJets
 ### Particle flow configuration
 import myParticleFlowConfiguration as myParticleFlowConfiguration
 pfSuffix = 'PF'
 ### JEC levels
 # levels to be accessible from the jets; jets are corrected to L3Absolute (MC), L2L3Residual (data) automatically, if enabled here; and remain uncorrected, #if none of these levels is enabled here
 useL1FastJet    = True  # needs useL1Offset being off, error otherwise
 useL1Offset     = False # needs useL1FastJet being off, error otherwise
 useL2Relative   = True
 useL3Absolute   = True
 useL2L3Residual = True  # takes effect only on data
 useL5Flavor     = True
 useL7Parton     = True
 #### input Configuration
 import TopQuarkAnalysis.Configuration.patRefSel_inputModule_cfi as patRefSel_inputModule
 process.source = patRefSel_inputModule.source
 process.maxEvents = patRefSel_inputModule.maxEvents
 # filenames
 process.source.fileNames = cms.untracked.vstring('/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0000/42C14374-4B2A-E111-8C44-003048FFD744.root')# Fall11 TTbar muJets )
 #set filenames
 #if options.inputFiles != cms.untracked.vstring():
 # process.source.fileNames=options.inputFiles
 # maximum number of events
 maxInputEvents = -1 # reduce for testing
 #if options.maxEvents != '':
 # process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
 ### import standards GlobalTag, MagneticField, FrontierConditions_GlobalTag, MessageLogger
 process.load( "TopQuarkAnalysis.Configuration.patRefSel_basics_cff" ) 
 process.MessageLogger.cerr.FwkReport.reportEvery = fwkReportEvery 
 process.options.wantSummary = wantSummary
 if runOnMC:
   process.GlobalTag.globaltag = globalTagMC   + '::All'
 else:
   process.GlobalTag.globaltag = globalTagData + '::All'
 ## ouputModule configuration, process.out and process.outpath
 process.load( "TopQuarkAnalysis.Configuration.patRefSel_outputModule_cff" )
 # output file name
 process.out.fileName = outputFile
 #if options.outputFile != None:
 # process.out.fileName=options.outputFile
 # event content
 import PhysicsTools.PatAlgos.patEventContent_cff as patEventContent
 process.out.outputCommands = ["drop *"] #patEventContent.patEventContent
 # clear event selection
 process.out.SelectEvents.SelectEvents = []
 #### Load standard PAT
 process.load( "PhysicsTools.PatAlgos.patSequences_cff" )
 from PhysicsTools.PatAlgos.tools.coreTools import *
 ### Check JECs; JEC set
 #jecSet      = jecSetBase + 'Calo'
 jecSetAddPF = patRefSel_refMuJets.jecSetBase + pfSuffix
 jecSetPF    = jecSetAddPF
 if myParticleFlowConfiguration.usePFnoPU:
   jecSetPF += 'chs'
 # JEC levels
 if useL1FastJet and useL1Offset:
   sys.exit( 'ERROR: switch off either "L1FastJet" or "L1Offset"' )
 jecLevels = []
 if useL1FastJet:
   jecLevels.append( 'L1FastJet' )
 if useL1Offset:
   jecLevels.append( 'L1Offset' )
 if useL2Relative:
   jecLevels.append( 'L2Relative' )
 if useL3Absolute:
   jecLevels.append( 'L3Absolute' )
 if useL2L3Residual and not runOnMC:
   jecLevels.append( 'L2L3Residual' )
 if useL5Flavor:
   jecLevels.append( 'L5Flavor' )
 if useL7Parton:
   jecLevels.append( 'L7Parton' )
 #### Launch PF2PAT
 if runPF2PAT:
   if myParticleFlowConfiguration.useMuonCutBasePF:
     print "pfMuonSelectionCut : ",myParticleFlowConfiguration.pfMuonSelectionCut, " muonCutBase : ",myParticleFlowConfiguration.muonCutBase
     myParticleFlowConfiguration.pfMuonSelectionCut += ' && %s'%( myParticleFlowConfiguration.muonCutBase )
     print "changend pfMuonSelectionCut : ",myParticleFlowConfiguration.pfMuonSelectionCut
   if myParticleFlowConfiguration.useElectronCutBasePF:
     myParticleFlowConfiguration.pfElectronSelectionCut += ' && %s'%( myParticleFlowConfiguration.electronCutBase )
   from PhysicsTools.PatAlgos.tools.pfTools import usePF2PAT
   usePF2PAT( process
            , runPF2PAT      = runPF2PAT
            , runOnMC        = runOnMC
            , jetAlgo        = patRefSel_refMuJets.jetAlgo
            , postfix        = '' #myParticleFlowConfiguration.postfix
            , jetCorrections = ( jecSetPF
                               , jecLevels
                               )
            )
   process.out.outputCommands =  ["keep *"] 
   process.out.SelectEvents.SelectEvents = []
 
 if runOnMC:
   triggerSelection = patRefSel_refMuJets.triggerSelectionMC
 else:
   triggerSelection = patRefSel_refMuJets.triggerSelectionData
 import TopQuarkAnalysis.Configuration.patRefSel_triggerSelection_cff as patRefSel_triggerSelection_cff 
 process.step0a = patRefSel_triggerSelection_cff.triggerResults.clone(
   triggerConditions = [ triggerSelection ]
 )
 print "using trigger ",process.step0a.triggerConditions
 ###### only signal
 process.MyTTbarGenEventProd = cms.EDProducer('MyTTbarGenEventLepHad',
         genTag = cms.untracked.InputTag("genParticles"),
         )
 
 process.SemiLepMcFilter = cms.EDFilter('SemiLepMcFilter',
         ttbarEventTag = cms.untracked.InputTag("MyTTbarGenEventProd"),
         )
 process.selectSignal=cms.Sequence(process.MyTTbarGenEventProd*process.SemiLepMcFilter)
 ### Good vertex selection
 process.load("TopQuarkAnalysis.Configuration.patRefSel_goodVertex_cfi")
 process.step0b = process.goodOfflinePrimaryVertices.clone( filter = True )
 
 ### Event cleaning
 process.load("TopQuarkAnalysis.Configuration.patRefSel_eventCleaning_cff")
 process.step0c = cms.Sequence(
   process.HBHENoiseFilter + process.scrapingFilter
 )
 # register all modules
 import  TopQuarkAnalysis.Configuration.patRefSel_refMuJets_cfi as patRefSel_refMuJets_cfi
 import TopQuarkAnalysis.Configuration.patRefSel_common_cfi as patRefSel_common_cfi
 process.intermediatePatMuons =  patRefSel_refMuJets_cfi.intermediatePatMuons
 process.goodPatJets = patRefSel_refMuJets_cfi.goodPatJets
 process.goodPatJets.preselection = patRefSel_refMuJets.jetCutPF
 process.goodPatJets.checkOverlaps.muons.deltaR = patRefSel_refMuJets.jetMuonsDRPF
 process.patMuons.usePV=patRefSel_refMuJets.muonsUsePV
 process.patMuons.embedTrack = patRefSel_refMuJets.muonEmbedTrack
 process.selectedPatMuons.cut= patRefSel_refMuJets.muonCutPF
 process.intermediatePatMuons.preselection = patRefSel_refMuJets.looseMuonCutPF
 process.loosePatMuons = patRefSel_refMuJets_cfi.loosePatMuons
 process.loosePatMuons.preselection=patRefSel_refMuJets.looseMuonCutPF
 process.loosePatMuons.checkOverlaps.jets.deltaR = patRefSel_refMuJets.muonJetsDR
 process.tightPatMuons = patRefSel_refMuJets_cfi.tightPatMuons
 process.tightPatMuons.preselection=patRefSel_refMuJets.tightMuonCutPF
 process.patElectrons.electronIDSources = patRefSel_common_cfi.electronIDSources
 process.selectedPatElectrons.cut = patRefSel_refMuJets.electronCutPF 
 ## configure trigger matches
 if addTriggerMatching:
  if runOnMC:
   triggerObjectSelection = patRefSel_refMuJets.triggerObjectSelectionMC
  else:
   triggerObjectSelection = patRefSel_refMuJets.triggerObjectSelectionData
  from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import patTrigger
  from TopQuarkAnalysis.Configuration.patRefSel_triggerMatching_cfi import patMuonTriggerMatch
  from PhysicsTools.PatAlgos.tools.trigTools import *
  process.triggerProducer = patTrigger.clone()
  process.triggerMatch = patMuonTriggerMatch.clone( matchedCuts = triggerObjectSelection)
 process.step1a=patRefSel_refMuJets_cfi.step1a
 process.step1b=patRefSel_refMuJets_cfi.step1b
 process.step2 =patRefSel_refMuJets_cfi.step2
 process.step3 =patRefSel_refMuJets_cfi.step3
 process.step4a=patRefSel_refMuJets_cfi.step4a
 process.step4b=patRefSel_refMuJets_cfi.step4b
 process.step4c=patRefSel_refMuJets_cfi.step4c
 process.step5 =patRefSel_refMuJets_cfi.step5
 process.p = cms.Path(process.selectSignal)
 if useTrigger:
  process.p += process.step0a
 process.p += process.goodOfflinePrimaryVertices 
 if useGoodVertex:
  process.p += process.step0b
 if not runOnMC:
  process.p += process.step0c
 # CiC electron ID
 process.load( "RecoEgamma.ElectronIdentification.cutsInCategoriesElectronIdentificationV06_cfi" )
 process.eidCiCSequence = cms.Sequence(
   process.eidVeryLooseMC
  + process.eidLooseMC
 +process.eidMediumMC
 + process.eidTightMC
 + process.eidSuperTightMC
 + process.eidHyperTight1MC
 + process.eidHyperTight2MC
 + process.eidHyperTight3MC
 + process.eidHyperTight4MC
 )
 process.p += process.eidCiCSequence
 process.p += process.patPF2PATSequence
 process.patAddOnSequence = cms.Sequence(
     process.intermediatePatMuons
   * process.goodPatJets
   * process.loosePatMuons
   * process.tightPatMuons
 )
 process.p += process.patAddOnSequence
 process.load("RecoParticleFlow.PFProducer.electronPFIsolationDeposits_cff")
 process.load("RecoParticleFlow.PFProducer.electronPFIsolationValues_cff")
 process.electronPFIsolationSequence =  cms.Sequence(process.electronPFIsolationDepositsSequence*process.electronPFIsolationValuesSequence) 
 process.p.replace(process.pfSelectedElectrons,process.pfSelectedElectrons*process.electronPFIsolationSequence)
 process.prodSequence=cms.Sequence(process.selectSignal*process.goodOfflinePrimaryVertices*process.eidCiCSequence* process.patPF2PATSequence *process.patAddOnSequence*process.electronPFIsolationSequence)
 process.prodSequence.replace(process.pfSelectedElectrons,process.pfSelectedElectrons*process.electronPFIsolationSequence)
 process.p += process.step1a
 process.p += process.step1b
 process.p += process.step2
 process.p += process.step3
 process.p += process.step4a
 process.p += process.step4b
 process.p += process.step4c
 process.p += process.step5
 ##photonPFIsolationValuesSequence
 ##### tagging only
 process.out.SelectEvents.SelectEvents=[]
 process.out.outputCommands = ['keep *']#,'drop *_*_*_MyPAT','keep *_TriggerResults_*_MyPAT']
 ##### checking basics
 print "inputs: ",process.source.fileNames
 print "output: ",process.out.fileName
 print "commands ",process.out.outputCommands
 print "selection ",process.out.SelectEvents.SelectEvents
 return process  
