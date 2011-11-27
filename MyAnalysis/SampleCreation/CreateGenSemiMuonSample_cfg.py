import FWCore.ParameterSet.Config as cms

process = cms.Process("SemiMuonGenSkim")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 50

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/user/hoehle/CMSSW/CMSSW_datasets/CMSSW442/F25BCF39-AD04-E111-86B2-002354EF3BDF.root'
#	'/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v2/0000/04010DA0-CBA9-E011-A8B1-002618943964.root'
	)
)
## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)
#std sequence for TQAF
process.load("TopQuarkAnalysis.TopEventProducers.tqafSequences_cff")
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import removeTtSemiLepHypGenMatch
removeTtSemiLepHypGenMatch(process)

#process.ttSemiLepEvent.hypotheses = cms.vstring()
#process.ttSemiLepEvent.hypotheses.remove("ttSemiLepHypGenMatch")
process.load("MyFilters.GenSemiLeptonicFilter.genSemiLeptonicFilter_cfi")
#process.GenSemiLeptonicFilter = cms.EDFilter("GenSemiLeptonicFilter",src = cms.InputTag("ttSemiLepEvent"))

## process path
process.p = cms.Path(
                     process.tqafTtSemiLeptonic * ~process.GenSemiLeptonicFilter 
                     )
#
process.p.remove(process.kinFitTtSemiLepEventSelection)
process.p.remove(process.findTtSemiLepSignalSelMVA)
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('nonsemiMuon_ttbar_Fall11_Skim.root'),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    ),
    outputCommands = cms.untracked.vstring(
        'keep *')
)
process.outpath = cms.EndPath(process.out)

## tracking
print "this config creates from "
print process.source.fileNames
print "this output file "
print process.out.fileName


