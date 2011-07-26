import FWCore.ParameterSet.Config as cms

#
# produce ttSemiLep event hypotheses
#

## geom hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypGeom_cff import *

## wMassDeltaTopMass hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypWMassDeltaTopMass_cff import *

## wMassMaxSumPt hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypWMassMaxSumPt_cff import *

## maxSumPtWMass hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypMaxSumPtWMass_cff import *

## genMatch hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypGenMatch_cff import *

## mvaDisc hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypMVADisc_cff import *

## kinFit hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypKinFit_cff import *

## hitFit hypothesis
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypHitFit_cff import *

## ownTopMassBTag
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnTopMassBTag_cff import *

## ownM3BTag 
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnM3BTag_cff import *

## ownPseudoMatchBJetCalcNu
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoMatchBJetCalcNu_cff import *

## ownPseudoMatchBJetGenNu
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoMatchBJetGenNu_cff import *

## ownPseudoMatchBJetMatchedCalcNu
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoMatchBJetMatchedCalcNu_cff import *

## ownPseudoGenBMatchedCalcNu
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoGenBMatchedCalcNu_cff import *

## ownPseudoGenBCalcNu
from TopQuarkAnalysis.TopJetCombination.TtSemiLepHypOwnPseudoGenBCalcNu_cff import *

## make all considered event hypotheses
makeTtSemiLepHypotheses  = cms.Sequence(makeHypothesis_genMatch )  # makeHypothesis_geom
                                                                  # makeHypothesis_wMassDeltaTopMass
                                                                  # makeHypothesis_wMassMaxSumPt
                                                                  # makeHypothesis_maxSumPtWMass
                                                                  # makeHypothesis_mvaDisc
                                                                  # makeHypothesis_kinFit
                                        			  						# makeHypothesis_hitFit
																						# makeHypothesis_ownTopMassBTag
																						# makeHypothesis_ownM3BTag
																						# makeHypothesis_ownPseudoMatchBJetCalcNu
																						# makeHypothesis_ownPseudoMatchBJetGenNu
										#makeHypothesis_ownPseudoMatchBJetMatchedCalcNu
										#makeHypothesis_ownPseudoGenBMatchedCalcNu
										#makeHypothesis_ownPseudoGenBCalcNu
					

