import FWCore.ParameterSet.Config as cms

#
# Example for a configuration of the GenSemiLeptonicFilter
# needs TQAF GenEvent
#

GenSemiLeptonicFilter = cms.EDFilter("GenSemiLeptonicFilter",src = cms.InputTag("ttSemiLepEvent"))

