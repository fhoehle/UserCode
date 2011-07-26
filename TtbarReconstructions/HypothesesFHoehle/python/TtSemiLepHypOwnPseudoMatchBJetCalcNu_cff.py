import FWCore.ParameterSet.Config as cms

#
# produce ownPseudoMatchBJetCalcNu hypothesis with all necessary 
# ingredients
#

## configure ownPseudoMatchBJetCalcNu hyothesis
from TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoMatchBJetCalcNu_cfi import *

## make hypothesis
makeHypothesis_ownPseudoMatchBJetCalcNu = cms.Sequence(ttSemiLepHypOwnPseudoMatchBJetCalcNu)

