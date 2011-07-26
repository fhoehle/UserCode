import FWCore.ParameterSet.Config as cms

#
# produce ownPseudoGenBCalcNu hypothesis with all necessary 
# ingredients
#

## configure ownPseudoGenBCalcNu hyothesis
from TtbarReconstructions.HypothesesFHoehle.TtSemiLepHypOwnPseudoGenBCalcNu_cfi import *

## make hypothesis
makeHypothesis_ownPseudoGenBCalcNu = cms.Sequence(ttSemiLepHypOwnPseudoGenBCalcNu)

