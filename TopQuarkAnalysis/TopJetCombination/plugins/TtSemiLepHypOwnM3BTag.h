#ifndef TtSemiLepHypOwnM3BTag_h
#define TtSemiLepHypOwnM3BTag_h

#include "TopQuarkAnalysis/TopJetCombination/interface/TtSemiLepHypothesis.h"


class TtSemiLepHypOwnM3BTag : public TtSemiLepHypothesis  {

 public:

  explicit TtSemiLepHypOwnM3BTag(const edm::ParameterSet&);
  ~TtSemiLepHypOwnM3BTag();

 private:

  /// build the event hypothesis key
  virtual void buildKey() { key_= TtSemiLeptonicEvent::kOwnM3BTag; };  
  /// build event hypothesis from the reco objects of a semi-leptonic event 
  virtual void buildHypo(edm::Event&,
			 const edm::Handle<edm::View<reco::RecoCandidate> >&,
			 const edm::Handle<std::vector<pat::MET> >&,
			 const edm::Handle<std::vector<pat::Jet> >&,
			 std::vector<int>&, const unsigned int iComb);

 private:

  int maxNJets_;
  double wMass_;
  double topMass_;
  bool useBTagging_;
  std::string bTagAlgorithm_;
  double minBDiscBJets_;
};

#endif
