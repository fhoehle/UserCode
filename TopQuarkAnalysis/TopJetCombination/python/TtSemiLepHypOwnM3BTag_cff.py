import FWCore.ParameterSet.Config as cms

#
# produce ownM3BTag hypothesis with all necessary 
# ingredients
#

## configure ownM3BTag hyothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnM3BTag_cfi import *

## make hypothesis
makeHypothesis_ownM3BTag = cms.Sequence(ttSemiLepHypOwnM3BTag)

