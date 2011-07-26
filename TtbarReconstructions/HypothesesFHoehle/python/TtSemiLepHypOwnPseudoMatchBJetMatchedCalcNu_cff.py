import FWCore.ParameterSet.Config as cms

#
# produce ownPseudoMatchBJetMatchedCalcNu hypothesis with all necessary 
# ingredients
#

## configure ownPseudoMatchBJetMatchedCalcNu hyothesis
from TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoMatchBJetMatchedCalcNu_cfi import *

## make hypothesis
makeHypothesis_ownPseudoMatchBJetMatchedCalcNu = cms.Sequence(ttSemiLepHypOwnPseudoMatchBJetMatchedCalcNu)

