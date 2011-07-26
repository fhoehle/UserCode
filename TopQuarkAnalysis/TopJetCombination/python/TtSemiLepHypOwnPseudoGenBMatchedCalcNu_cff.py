import FWCore.ParameterSet.Config as cms

#
# produce ownPseudoGenBMatchedCalcNu hypothesis with all necessary 
# ingredients
#

## configure ownPseudoGenBMatchedCalcNu hyothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoGenBMatchedCalcNu_cfi import *

## make hypothesis
makeHypothesis_ownPseudoGenBMatchedCalcNu = cms.Sequence(ttSemiLepHypOwnPseudoGenBMatchedCalcNu)

