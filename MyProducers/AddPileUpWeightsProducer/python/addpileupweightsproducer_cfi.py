import FWCore.ParameterSet.Config as cms

addPileupWeightsProducer = cms.EDProducer("AddPileUpWeightsProducer",
                                  vertexSrc = cms.InputTag("offlinePrimaryVertices")
)


