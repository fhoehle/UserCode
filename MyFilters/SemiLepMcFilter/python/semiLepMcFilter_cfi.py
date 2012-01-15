import FWCore.ParameterSet.Config as cms

MyTTbarGenEventProd = cms.EDProducer('MyTTbarGenEventLepHad',
        genTag = cms.untracked.InputTag("genParticles"),
        )

SemiLepMcFilter = cms.EDFilter('SemiLepMcFilter',
        ttbarEventTag = cms.untracked.InputTag("MyTTbarGenEventProd"),
        )
pdgIdTest = cms.PSet(min          = cms.untracked.double(     -30.5),
                          max          = cms.untracked.double(    30.5),
                          nbins        = cms.untracked.int32 (     122),
                          name         = cms.untracked.string('GenPartPt'),
                          description  = cms.untracked.string(     ''),
                          plotquantity = cms.untracked.string(   'pdgId')
                          )
genHists = cms.EDAnalyzer(
    'CandViewHistoAnalyzer',
    src = cms.InputTag('MyTTbarGenEventProd'),
    histograms = cms.VPSet(pdgIdTest)
)

