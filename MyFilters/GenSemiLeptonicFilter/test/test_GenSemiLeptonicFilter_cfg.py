import FWCore.ParameterSet.Config as cms

process = cms.Process("SemiMuonicGenSkim")

## configure message logger
#process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger.cerr.threshold = 'INFO'

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02C07708-9898-E011-BC86-001A92971B0C.root')
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
process.load("TopQuarkAnalysis.TopEventProducers.tqafSequences_cff")
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import removeTtSemiLepHypGenMatch
removeTtSemiLepHypGenMatch(process)

#process.ttSemiLepEvent.hypotheses = cms.vstring()
#process.ttSemiLepEvent.hypotheses.remove("ttSemiLepHypGenMatch")
process.GenSemiLeptonicFilter = cms.EDFilter("GenSemiLeptonicFilter",src = cms.InputTag("ttSemiLepEvent"))

## process path
process.p = cms.Path(
                     process.tqafTtSemiLeptonic * process.GenSemiLeptonicFilter 
                     )
#
process.p.remove(process.kinFitTtSemiLepEventSelection)
process.p.remove(process.findTtSemiLepSignalSelMVA)
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('semiMuonic_ttbarSkim.root'),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    ),
    outputCommands = cms.untracked.vstring(
        'keep *')
)
process.outpath = cms.EndPath(process.out)

