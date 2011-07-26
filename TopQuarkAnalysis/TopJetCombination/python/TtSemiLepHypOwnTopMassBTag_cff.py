import FWCore.ParameterSet.Config as cms

#
# produce ownTopMassBTag hypothesis with all necessary 
# ingredients
#

## configure ownTopMassBTag hyothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnTopMassBTag_cfi import *

## make hypothesis
makeHypothesis_ownTopMassBTag = cms.Sequence(ttSemiLepHypOwnTopMassBTag)

