#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnM3BTag.h"
#include "TopQuarkAnalysis/TopTools/interface/MyMEzCalculator.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
TtSemiLepHypOwnM3BTag::TtSemiLepHypOwnM3BTag(const edm::ParameterSet& cfg):
  TtSemiLepHypothesis( cfg ),
  maxNJets_            (cfg.getParameter<int>        ("maxNJets"            )),
  wMass_               (cfg.getParameter<double>     ("wMass"               )),
  topMass_             (cfg.getParameter<double>     ("topMass"             )),
  useBTagging_         (cfg.getParameter<bool>       ("useBTagging"         )),
  bTagAlgorithm_       (cfg.getParameter<std::string>("bTagAlgorithm"       )),
  minBDiscBJets_       (cfg.getParameter<double>     ("minBDiscBJets"       ))
//   neutrinoSolutionType_(cfg.getParameter<int>        ("neutrinoSolutionType"))
{
  if(maxNJets_<4 && maxNJets_!=-1)
    throw cms::Exception("WrongConfig") 
      << "Parameter maxNJets can not be set to " << maxNJets_ << ". \n"
      << "It has to be larger than 4 or can be set to -1 to take all jets.";
}

TtSemiLepHypOwnM3BTag::~TtSemiLepHypOwnM3BTag() { }

void
TtSemiLepHypOwnM3BTag::buildHypo(edm::Event& evt,
				     const edm::Handle<edm::View<reco::RecoCandidate> >& leps, 
				     const edm::Handle<std::vector<pat::MET> >& mets, 
				     const edm::Handle<std::vector<pat::Jet> >& jets, 
				     std::vector<int>& match, const unsigned int iComb)
{
if(leps->empty() || mets->empty() ||jets->empty() || jets->size() < 4 || !useBTagging_ || (maxNJets_ != -1 && maxNJets_ < 4)){
    // create empty hypothesis
	if(jets->empty() || jets->size() < 4 || !useBTagging_ || (maxNJets_ != -1 && maxNJets_ < 4)) edm::LogWarning("Jets")<<" maxNJets_ "<<maxNJets_<<"jets->size() "<< jets->size()<< " jets->empty() "<<jets->empty()<< " useBTagging_ "<<useBTagging_;
    return;
  }

  int maxNJets = (maxNJets_ == -1 && jets->size() >= 4 ) ? jets->size() : maxNJets_;
  // find two highest/significant b-Jets
  double maxBTagJet1 = -0.001; double maxBTagJet2 = -0.001;
  int maxBIdxJet1 = -1; int maxBIdxJet2 = -1;
  double tempBTag ;
  if(useBTagging_) {
    for(int idx=0; idx<maxNJets; ++idx) {
	tempBTag =  (*jets)[idx].bDiscriminator(bTagAlgorithm_);
      if(tempBTag > minBDiscBJets_  ){
	if(tempBTag > maxBTagJet1){
		maxBTagJet2 = maxBTagJet1;
		maxBTagJet1 = tempBTag;
		maxBIdxJet2 = maxBIdxJet1;
		maxBIdxJet1 = idx;
	}
	else if(tempBTag > maxBTagJet2){maxBTagJet2 = tempBTag; maxBIdxJet2 = idx;}


	}
    }
  }
	if(maxBIdxJet1 == -1 || maxBIdxJet2 == -1) return ;

	double maxPt =-1.;
	std::vector<int> WIndices;
	WIndices.push_back(-1);
	WIndices.push_back(-1);
	int bhadIdx = -1;
	for(int idx=0; idx<maxNJets; ++idx){
		for(int jdx=(idx+1); jdx<maxNJets; ++jdx){
			if(jdx ==  maxBIdxJet1 || jdx ==  maxBIdxJet2) continue;
				reco::Particle::LorentzVector sum1 = (*jets)[idx].p4() + (*jets)[jdx].p4() + (*jets)[maxBIdxJet1].p4();
				reco::Particle::LorentzVector sum2 = (*jets)[idx].p4() + (*jets)[jdx].p4() + (*jets)[maxBIdxJet2].p4();
					if( maxPt<sum1.pt() || maxPt<sum2.pt()  ){
						maxPt = (sum1.pt() > sum2.pt() ) ? sum1.pt() : sum2.pt() ;
						WIndices.clear();
						WIndices.push_back(idx);
						WIndices.push_back(jdx);
						bhadIdx = (sum1.pt() > sum2.pt() ) ? maxBIdxJet1 : maxBIdxJet2 ;
					}
				}
			}
			int blepIdx = -1;
			if(bhadIdx != -1) blepIdx = (bhadIdx == maxBIdxJet1) ? maxBIdxJet2 : maxBIdxJet1 ; 
			else edm::LogError("RecoError")<<"This should not happen big error before";
		
			if(bhadIdx == -1 || WIndices[0] == -1 || WIndices[1] == -1 ){
				edm::LogError("RecoError")<<"This should not happen big error before this";
			}

  // calc neutrino 
	edm::Ptr<pat::MET> ptr = edm::Ptr<pat::MET>(mets, 0);
  	MyMEzCalculator mez;
    	mez.SetMET( *(mets->begin()) );
    	mez.SetLepton( (*leps)[0], true );
  	std::vector<double> nuzSols = mez.TwoSolCalculate();
// 	std::cout<<"neutrino calc ended "<<nuzSols.size()<<std::endl;
//   	numberOfRealNeutrinoSolutions_ = mez.IsComplex() ? 0 : 2;
  	const math::XYZTLorentzVector nuSol1( ptr->px(), ptr->py(), nuzSols[0], sqrt(ptr->px()*ptr->px() + ptr->py()*ptr->py() + nuzSols[0]*nuzSols[0]) );
	const math::XYZTLorentzVector nuSol2( ptr->px(), ptr->py(), nuzSols[1], sqrt(ptr->px()*ptr->px() + ptr->py()*ptr->py() + nuzSols[1]*nuzSols[1]) );
// 	std::cout<<"two neutrino sols set "<<nuzSols.size()<<std::endl;
	const math::XYZTLorentzVector nuSol = ( fabs( topMass_ - ( (*leps)[0].p4() + nuSol1 + (*jets)[blepIdx].p4() ).M()) < fabs( topMass_ - ( (*leps)[0].p4() + nuSol2 + (*jets)[blepIdx].p4() ).M() ) ) ? nuSol1 : nuSol2;
	// add neutrino
	neutrino_ = new reco::ShallowClonePtrCandidate( ptr, ptr->charge(), nuSol, ptr->vertex() );
  // -----------------------------------------------------
  // add jets
  // -----------------------------------------------------
  if( isValid(WIndices[0], jets) ){
    setCandidate(jets, WIndices[0], lightQ_, jetCorrectionLevel("wQuarkMix"));
    match[TtSemiLepEvtPartons::LightQ] = WIndices[0];
  }

  if( isValid(WIndices[1], jets) ){
    setCandidate(jets, WIndices[1], lightQBar_, jetCorrectionLevel("wQuarkMix"));
    match[TtSemiLepEvtPartons::LightQBar] = WIndices[1];
  }

      if( isValid(bhadIdx, jets) ){
	setCandidate(jets, bhadIdx, hadronicB_, jetCorrectionLevel("bQuark"));
	match[TtSemiLepEvtPartons::HadB] = bhadIdx;
      }
  
  if( isValid(blepIdx, jets) ){
    setCandidate(jets, blepIdx, leptonicB_, jetCorrectionLevel("bQuark"));
    match[TtSemiLepEvtPartons::LepB] = blepIdx;
  }

  // -----------------------------------------------------
  // add lepton
  // -----------------------------------------------------
  setCandidate(leps, 0, lepton_);
  match[TtSemiLepEvtPartons::Lepton] = 0;
  
}
