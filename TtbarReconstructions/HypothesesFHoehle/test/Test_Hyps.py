import sys

import FWCore.ParameterSet.Config as cms

process = cms.Process( 'TestHyps' )
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
fwkReportEvery = 100
process.MessageLogger.cerr.FwkReport.reportEvery = fwkReportEvery
#process.MessageLogger.suppressInfo = cms.untracked.vstring('TtSemiLepHypOwnPseudoMatchBJetCalcNu','ttSemiLepHypOwnPseudoMatchBJetCalcNu')
process.MessageLogger.suppressWarning = cms.untracked.vstring('TtSemiLepHypOwnPseudoMatchBJetCalcNu','ttSemiLepHypOwnPseudoMatchBJetCalcNu','ttSemiLepHypOwnM3BTag','ttSemiLepHypOwnPseudoMatchBJetGenNu','myttbarGenEvent','ttSemiLepHypOwnTopMassBTag','ttSemiLepHypOwnPseudoGenBMatchedCalcNu','ttSemiLepHypOwnPseudoGenBCalcNu','ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu')
#process.MessageLogger.debugModules = cms.untracked.vstring('ttSemiLepHypOwnPseudoMatchBJetCalcNu')
#process.MessageLogger.categories=cms.untracked.vstring('leptonicDecayBInfo')#'ttbar-Event','TopDecay','ttbar-Decay'
#process.MessageLogger.cout = cms.untracked.PSet( threshold = cms.untracked.string('WARNING') )#INFO WARNING
#process.MessageLogger.destinations = cms.untracked.vstring('cout')

#Standard Sequences
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
globalTagMC   = 'START42_V12' # default for CMSSW_4_2_3 RelVals: 'START42_V12'
process.GlobalTag.globaltag = globalTagMC   + '::All'
###source
process.source  = cms.Source( "PoolSource"
, noEventSort        = cms.untracked.bool( True )
, duplicateCheckMode = cms.untracked.string( 'noDuplicateCheck' )
, fileNames = cms.untracked.vstring(
       'file:/user/hoehle/TEST_CMSSW/CMSSW_4_2_5/src/my_patRefSel_muJets.root'# /TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
	)
)
# maximum number of events
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)
# output
process.out = cms.OutputModule("PoolOutputModule",
    fileName       = cms.untracked.string('TestHyps.root'),#pythiaOLD
    SelectEvents   = cms.untracked.PSet(SelectEvents = cms.vstring('p') ),
    outputCommands = cms.untracked.vstring( 'keep * ')#    
   # dropMetaData   = cms.untracked.string("DROPPED")  ## NONE    for none                                                  
   ## DROPPED for drop for dropped data
)
process.outpath = cms.EndPath(process.out)

process.load("TopQuarkAnalysis.TopEventProducers.tqafSequences_cff")
## process path
#process.p = cms.Path(process.patDefaultSequence *
                     #process.tqafTtSemiLeptonic
                     #)
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import addTtSemiLepHypotheses
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypHitFit_cff import *
addTtSemiLepHypotheses(process,
                           ["kGeom", "kMaxSumPtWMass", "kWMassDeltaTopMass","kKinFit","kWMassMaxSumPt","kHitFit"]
)
#,"kOwnPseudoMatchBJetCalcNu","kOwnPseudoMatchBJetGenNu","kKinFit","kOwnPseudoMatchBJetMatchedCalcNu","kOwnPseudoGenBCalcNu","kOwnPseudoGenBMatchedCalcNu"]
#process.tqafTtSemiLeptonic.remove(process.makeTtSemiLepKinematicFit)
#process.tqafTtSemiLeptonic.remove(process.makeTtSemiLepMVASelDiscriminant)
process.kinFitTtSemiLepEventSelection.jets = cms.InputTag("goodPatJetsPF")
process.kinFitTtSemiLepEventSelection.leps = cms.InputTag("tightPatMuonsPF")
process.kinFitTtSemiLepEventSelection.mets = cms.InputTag("patMETsPF")
process.hitFitTtSemiLepEventHypothesis.jets = cms.InputTag("goodPatJetsPF")
process.hitFitTtSemiLepEventHypothesis.leps = cms.InputTag("tightPatMuonsPF")
process.hitFitTtSemiLepEventHypothesis.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypWMassMaxSumPt.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypWMassMaxSumPt.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypWMassMaxSumPt.mets = cms.InputTag("patMETsPF")

process.kinFitTtSemiLepEventHypothesis.leps = cms.InputTag("tightPatMuonsPF")
process.kinFitTtSemiLepEventHypothesis.jets = cms.InputTag("goodPatJetsPF")
process.kinFitTtSemiLepEventHypothesis.mets = cms.InputTag("patMETsPF")

process.ttSemiLepHypKinFit.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypKinFit.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypKinFit.mets = cms.InputTag("patMETsPF")
process.findTtSemiLepSignalSelMVA.muons = cms.InputTag("tightPatMuonsPF")
process.findTtSemiLepSignalSelMVA.jets = cms.InputTag("goodPatJetsPF")
process.findTtSemiLepSignalSelMVA.mets = cms.InputTag("patMETsPF")

process.ttSemiLepJetPartonMatch.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypGenMatch.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypGenMatch.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypGenMatch.mets = cms.InputTag("patMETsPF")

process.findTtSemiLepJetCombGeom.jets = cms.InputTag("goodPatJetsPF")
process.findTtSemiLepJetCombGeom.leps = cms.InputTag("tightPatMuonsPF")
process.findTtSemiLepJetCombGeom.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypWMassDeltaTopMass.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypWMassDeltaTopMass.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypWMassDeltaTopMass.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypGeom.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypGeom.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypGeom.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypMaxSumPtWMass.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypMaxSumPtWMass.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypMaxSumPtWMass.mets = cms.InputTag("patMETsPF")

process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoMatchBJetMatchedCalcNu_cff")
process.ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu.leps = cms.InputTag("tightPatMuonsPF")
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoGenBCalcNu_cff")
process.ttSemiLepHypOwnPseudoGenBCalcNu.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnPseudoGenBCalcNu.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypOwnPseudoGenBCalcNu.leps = cms.InputTag("tightPatMuonsPF")
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoGenBMatchedCalcNu_cff")
process.ttSemiLepHypOwnPseudoGenBMatchedCalcNu.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnPseudoGenBMatchedCalcNu.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepHypOwnPseudoGenBMatchedCalcNu.leps = cms.InputTag("tightPatMuonsPF") 
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnM3BTag_cff")
process.ttSemiLepHypOwnM3BTag.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnM3BTag.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypOwnM3BTag.jets = cms.InputTag("goodPatJetsPF")
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoMatchBJetCalcNu_cff")
process.ttSemiLepHypOwnPseudoMatchBJetCalcNu.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnPseudoMatchBJetCalcNu.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypOwnPseudoMatchBJetCalcNu.jets = cms.InputTag("goodPatJetsPF")
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoMatchBJetGenNu_cff")
process.ttSemiLepHypOwnPseudoMatchBJetGenNu.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnPseudoMatchBJetGenNu.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypOwnPseudoMatchBJetGenNu.jets = cms.InputTag("goodPatJetsPF")
process.load("TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnTopMassBTag_cff")
process.ttSemiLepHypOwnTopMassBTag.mets = cms.InputTag("patMETsPF")
process.ttSemiLepHypOwnTopMassBTag.leps = cms.InputTag("tightPatMuonsPF")
process.ttSemiLepHypOwnTopMassBTag.jets = cms.InputTag("goodPatJetsPF")
process.ttSemiLepEvent.hypotheses += ['ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu','ttSemiLepHypOwnPseudoGenBCalcNu', 
    'ttSemiLepHypOwnPseudoGenBMatchedCalcNu', 
    'ttSemiLepHypOwnM3BTag', 
    'ttSemiLepHypOwnPseudoMatchBJetCalcNu', 
    'ttSemiLepHypOwnPseudoMatchBJetGenNu', 
    'ttSemiLepHypOwnTopMassBTag']
process.myJet4Filter = cms.EDFilter(
  "PATCandViewCountFilter"
, src = cms.InputTag( 'goodPatJetsPF' )
, minNumber = cms.uint32( 4 )
, maxNumber = cms.uint32( 999999 )
)
process.p = cms.Path()
process.p += process.myJet4Filter
process.p += process.tqafTtSemiLeptonic
#
process.p.replace(process.ttSemiLepEvent,process.ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu * process.ttSemiLepHypOwnPseudoGenBCalcNu * process.ttSemiLepHypOwnPseudoGenBMatchedCalcNu * process.ttSemiLepHypOwnM3BTag * process.ttSemiLepHypOwnPseudoMatchBJetCalcNu * process.ttSemiLepHypOwnPseudoMatchBJetGenNu * process.ttSemiLepHypOwnTopMassBTag * process.ttSemiLepEvent)

