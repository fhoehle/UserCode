import FWCore.ParameterSet.Config as cms

#
# produce ownPseudoMatchBJetGenNu hypothesis with all necessary 
# ingredients
#

## configure ownPseudoMatchBJetGenNu hyothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoMatchBJetGenNu_cfi import *

## make hypothesis
makeHypothesis_ownPseudoMatchBJetGenNu = cms.Sequence(ttSemiLepHypOwnPseudoMatchBJetGenNu)

