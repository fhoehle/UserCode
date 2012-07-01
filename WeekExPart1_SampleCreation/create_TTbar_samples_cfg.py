import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process("Samplizer")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/Summer12/TTJets_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S7_START52_V9-v1/0000/FEDDBC6A-9290-E111-B7FD-0018F3D09628.root')
)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
if options.maxEvents != None:
 process.maxEvents.input = options.maxEvents
## Gen Selections
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtGenEvtFilter_cfi")
process.isSemiMuTTbar = process.ttGenEventFilter.clone(cut = cms.string("isTtBar() && isSemiLeptonic() && abs(singleLepton().pdgId()) == 13"))
process.pSemiMuTTbar = cms.Path(process.makeGenEvt * process.isSemiMuTTbar)

process.pNonSemiMuTTbar = cms.Path(process.makeGenEvt * ~process.isSemiMuTTbar)
## Output Module Configuration (expects a path 'p')
process.out_isSemiMuTTbar = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('ttbar_SemiMu.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('pSemiMuTTbar') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('keep *')
                               )
process.out_isNonSemiMuTTbar = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('ttbar_NonSemiMu.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('pNonSemiMuTTbar') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('keep *')
                               )

process.outpath = cms.EndPath(process.out_isSemiMuTTbar * process.out_isNonSemiMuTTbar)
