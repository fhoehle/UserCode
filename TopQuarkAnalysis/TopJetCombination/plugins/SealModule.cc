#include "FWCore/Framework/interface/MakerMacros.h"

#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepJetCombMVAComputer.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepJetCombMVATrainer.h"

// define mva modules
DEFINE_FWK_MODULE(TtSemiLepJetCombMVAComputer);
DEFINE_FWK_MODULE(TtSemiLepJetCombMVATrainer);

#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepJetCombGeom.h"
DEFINE_FWK_MODULE(TtSemiLepJetCombGeom);

#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypGeom.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypWMassDeltaTopMass.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypWMassMaxSumPt.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypMaxSumPtWMass.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypGenMatch.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypMVADisc.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypKinFit.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypHitFit.h"

// define event hypotheses
DEFINE_FWK_MODULE(TtSemiLepHypGeom);
DEFINE_FWK_MODULE(TtSemiLepHypWMassDeltaTopMass);
DEFINE_FWK_MODULE(TtSemiLepHypWMassMaxSumPt);
DEFINE_FWK_MODULE(TtSemiLepHypMaxSumPtWMass);
DEFINE_FWK_MODULE(TtSemiLepHypGenMatch);
DEFINE_FWK_MODULE(TtSemiLepHypMVADisc);
DEFINE_FWK_MODULE(TtSemiLepHypKinFit);
DEFINE_FWK_MODULE(TtSemiLepHypHitFit);

#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnTopMassBTag.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnTopMassBTag);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnM3BTag.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnM3BTag);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnPseudoMatchBJetCalcNu.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnPseudoMatchBJetCalcNu);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnPseudoMatchBJetGenNu.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnPseudoMatchBJetGenNu);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnPseudoMatchBJetMatchedCalcNu.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnPseudoMatchBJetMatchedCalcNu);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnPseudoGenBCalcNu.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnPseudoGenBCalcNu);
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnPseudoGenBMatchedCalcNu.h"
DEFINE_FWK_MODULE(TtSemiLepHypOwnPseudoGenBMatchedCalcNu);

// define fully leptonic event hypotheses
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtFullLepHypGenMatch.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtFullLepHypKinSolution.h"

DEFINE_FWK_MODULE(TtFullLepHypGenMatch);
DEFINE_FWK_MODULE(TtFullLepHypKinSolution);

// define fully hadronic event hypotheses
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtFullHadHypGenMatch.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtFullHadHypKinFit.h"
DEFINE_FWK_MODULE(TtFullHadHypGenMatch);
DEFINE_FWK_MODULE(TtFullHadHypKinFit);
