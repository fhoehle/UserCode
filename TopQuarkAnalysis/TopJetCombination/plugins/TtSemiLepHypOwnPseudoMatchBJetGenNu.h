#ifndef TtSemiLepHypOwnPseudoMatchBJetGenNu_h
#define TtSemiLepHypOwnPseudoMatchBJetGenNu_h

#include "TopQuarkAnalysis/TopJetCombination/interface/TtSemiLepHypothesis.h"


class TtSemiLepHypOwnPseudoMatchBJetGenNu : public TtSemiLepHypothesis  {

 public:

  explicit TtSemiLepHypOwnPseudoMatchBJetGenNu(const edm::ParameterSet&);
  ~TtSemiLepHypOwnPseudoMatchBJetGenNu();

 private:

  /// build the event hypothesis key
  virtual void buildKey() { key_= TtSemiLeptonicEvent::kOwnPseudoMatchBJetGenNu; };  
  /// build event hypothesis from the reco objects of a semi-leptonic event 
  virtual void buildHypo(edm::Event&,
			 const edm::Handle<edm::View<reco::RecoCandidate> >&,
			 const edm::Handle<std::vector<pat::MET> >&,
			 const edm::Handle<std::vector<pat::Jet> >&,
			 std::vector<int>&, const unsigned int iComb);

 private:

  double maxDeltaR_ ;
  double maxEfrac_ ;
//   double topMass_ ;
//   int maxNJets_;
//   double wMass_;
//   double topMass_;
//   bool useBTagging_;
//   std::string bTagAlgorithm_;
//   double minBDiscBJets_;
//   double maxBDiscLightJets_;
//   int neutrinoSolutionType_;
};

#endif
