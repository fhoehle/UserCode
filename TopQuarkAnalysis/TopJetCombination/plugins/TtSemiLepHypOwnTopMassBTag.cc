#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "TopQuarkAnalysis/TopJetCombination/plugins/TtSemiLepHypOwnTopMassBTag.h"
#include "TopQuarkAnalysis/TopTools/interface/MyMEzCalculator.h"
TtSemiLepHypOwnTopMassBTag::TtSemiLepHypOwnTopMassBTag(const edm::ParameterSet& cfg):
  TtSemiLepHypothesis( cfg ),
  maxNJets_            (cfg.getParameter<int>        ("maxNJets"            )),
  wMass_               (cfg.getParameter<double>     ("wMass"               )),
  topMass_               (cfg.getParameter<double>   ("topMass"               )),
  useBTagging_         (cfg.getParameter<bool>       ("useBTagging"         )),
  bTagAlgorithm_       (cfg.getParameter<std::string>("bTagAlgorithm"       )),
  minBDiscBJets_       (cfg.getParameter<double>     ("minBDiscBJets"       ))//,
  //maxBDiscLightJets_   (cfg.getParameter<double>     ("maxBDiscLightJets"   )),
  //neutrinoSolutionType_(cfg.getParameter<int>        ("neutrinoSolutionType"))
{
  if(maxNJets_<4 && maxNJets_!=-1)
    throw cms::Exception("WrongConfig") 
      << "Parameter maxNJets can not be set to " << maxNJets_ << ". \n"
      << "It has to be larger than 4 or can be set to -1 to take all jets.";
}

TtSemiLepHypOwnTopMassBTag::~TtSemiLepHypOwnTopMassBTag() { }

void
TtSemiLepHypOwnTopMassBTag::buildHypo(edm::Event& evt,
				     const edm::Handle<edm::View<reco::RecoCandidate> >& leps, 
				     const edm::Handle<std::vector<pat::MET> >& mets, 
				     const edm::Handle<std::vector<pat::Jet> >& jets, 
				     std::vector<int>& match, const unsigned int iComb)
{
  if(leps->empty() || mets->empty() ||jets->empty() || jets->size() < 2 || !useBTagging_ || (maxNJets_ != -1 && maxNJets_ < 2)){
    // create empty hypothesis
	if(jets->empty() || jets->size() < 2 || !useBTagging_ || (maxNJets_ != -1 && maxNJets_ < 2) ) edm::LogWarning("Jets")<<"jets->empty() "<<jets->empty()<<" jets->size()  "<<jets->size()<<" useBTagging_ "<<useBTagging_<<" maxNJets_ "<<maxNJets_;
    return;
  }

  int maxNJets = (maxNJets_ == -1 && jets->size() >= 2 ) ? jets->size() : maxNJets_;
// 	std::cout<<"maxNJets_ "<<maxNJets_<<"  jets->size() "<<jets->size()<<" maxNJets "<<maxNJets<<std::endl;

  std::vector<int> bJets_Idxs;
  int cntBJets = 0;
  if(useBTagging_) {
    for(int idx=0; idx<maxNJets; ++idx) {
	if( (*jets)[idx].bDiscriminator(bTagAlgorithm_) > minBDiscBJets_ ) bJets_Idxs.push_back(idx); 
    }
  }
	// if less than 2 Bjets mit mindisc found return empty hypothesis
	if(bJets_Idxs.size() < 2){
		return;
	}
	// find bJet with best topmass
	int blep_idx = -1;
	double temp_toplepabsdiffmass = -1.0;
	for(uint bidx=0; bidx<bJets_Idxs.size(); ++bidx){
		if(blep_idx == -1.0 || temp_toplepabsdiffmass > fabs( topMass_ - ( (*leps)[0].p4() + (*mets)[0].p4() - (*jets)[bJets_Idxs[bidx]].p4() ).M() ) ){
			temp_toplepabsdiffmass = fabs( topMass_ - ( (*leps)[0].p4() + (*mets)[0].p4() - (*jets)[bJets_Idxs[bidx]].p4() ).M() );
			blep_idx = bJets_Idxs[bidx];
		}
	}
	if(blep_idx == -1){return ;}
// 	std::cout<<"blep_idx "<<blep_idx<<std::endl;
	// calculate neutrino
// 	std::cout<<"neutrino calcstart"<<std::endl;
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
	const math::XYZTLorentzVector nuSol = ( fabs( topMass_ - ( (*leps)[0].p4() + nuSol1 + (*jets)[blep_idx].p4() ).M()) < fabs( topMass_ - ( (*leps)[0].p4() + nuSol2 + (*jets)[blep_idx].p4() ).M() ) ) ? nuSol1 : nuSol2;
// 	std::cout<<"neutrino calc + conversion finished"<<std::endl;
	neutrino_ = new reco::ShallowClonePtrCandidate( ptr, ptr->charge(), nuSol, ptr->vertex() );
// 	pat::MET neutrino = (*mets)[0];
//   	neutrino.setP4(nuSol);
// 	edm::Handle<std::vector<pat::MET> > mymets;
// 	(*mymets).push_back(neutrino);
	


  // -----------------------------------------------------
  // add jets
  // -----------------------------------------------------

     if( isValid(blep_idx, jets) ){
	// hadronic side set to nonsense values
	setCandidate(jets, blep_idx, lightQBar_, jetCorrectionLevel("wQuarkMix"));
    	match[TtSemiLepEvtPartons::LightQBar] = blep_idx;

    	setCandidate(jets, blep_idx, lightQ_, jetCorrectionLevel("wQuarkMix"));
    	match[TtSemiLepEvtPartons::LightQ] = blep_idx;

	setCandidate(jets, blep_idx, hadronicB_, jetCorrectionLevel("bQuark"));
	match[TtSemiLepEvtPartons::HadB] = blep_idx;
	//end hadronic section
    	setCandidate(jets, blep_idx, leptonicB_, jetCorrectionLevel("bQuark"));
    	match[TtSemiLepEvtPartons::LepB] = blep_idx;
  }

  // -----------------------------------------------------
  // add lepton
  // -----------------------------------------------------
  setCandidate(leps, 0, lepton_);
  match[TtSemiLepEvtPartons::Lepton] = 0;
  
  // -----------------------------------------------------
  // add neutrino
  // -----------------------------------------------------
//   if(neutrinoSolutionType_ == -1)
//      setCandidate(mymets, 0, neutrino_);
//   else
//     setNeutrino(mets, leps, 0, neutrinoSolutionType_);
}
//   // -----------------------------------------------------
//   // associate those jets with maximum pt of the vectorial 
//   // sum to the hadronic decay chain
//   // -----------------------------------------------------
//   double maxPt=-1.;
//   std::vector<int> maxPtIndices;
//   maxPtIndices.push_back(-1);
//   maxPtIndices.push_back(-1);
//   maxPtIndices.push_back(-1);
//   for(int idx=0; idx<maxNJets; ++idx){
//     if(useBTagging_ && (!isLJet[idx] || (cntBJets<=2 && isBJet[idx]))) continue;
//     for(int jdx=(idx+1); jdx<maxNJets; ++jdx){
//       if(jdx==idx || (useBTagging_ && (!isLJet[jdx] || (cntBJets<=2 && isBJet[jdx]) || (cntBJets==3 && isBJet[idx] && isBJet[jdx])))) continue;
//       for(int kdx=0; kdx<maxNJets; ++kdx){
// 	if(kdx==idx || kdx==jdx || (useBTagging_ && !isBJet[kdx])) continue;
// 	reco::Particle::LorentzVector sum = 
// 	  (*jets)[idx].p4()+
// 	  (*jets)[jdx].p4()+
// 	  (*jets)[kdx].p4();
// 	if( maxPt<0. || maxPt<sum.pt() ){
// 	  maxPt=sum.pt();
// 	  maxPtIndices.clear();
// 	  maxPtIndices.push_back(idx);
// 	  maxPtIndices.push_back(jdx);
// 	  maxPtIndices.push_back(kdx);
// 	}
//       }
//     }
//   }
// 
//   // -----------------------------------------------------
//   // associate those jets that get closest to the W mass
//   // with their invariant mass to the W boson
//   // -----------------------------------------------------
//   double wDist =-1.;
//   std::vector<int> closestToWMassIndices;
//   closestToWMassIndices.push_back(-1);
//   closestToWMassIndices.push_back(-1);
//   if( isValid(maxPtIndices[0], jets) && isValid(maxPtIndices[1], jets) && isValid(maxPtIndices[2], jets)) {
//     for(unsigned idx=0; idx<maxPtIndices.size(); ++idx){  
//       for(unsigned jdx=0; jdx<maxPtIndices.size(); ++jdx){  
// 	if( jdx==idx || maxPtIndices[idx]>maxPtIndices[jdx] || (useBTagging_ && (!isLJet[maxPtIndices[idx]] || !isLJet[maxPtIndices[jdx]] || (cntBJets<=2 && isBJet[maxPtIndices[idx]]) || (cntBJets<=2 && isBJet[maxPtIndices[jdx]]) || (cntBJets==3 && isBJet[maxPtIndices[idx]] && isBJet[maxPtIndices[jdx]])))) continue;
// 	reco::Particle::LorentzVector sum = 
// 	  (*jets)[maxPtIndices[idx]].p4()+
// 	  (*jets)[maxPtIndices[jdx]].p4();
// 	if( wDist<0. || wDist>fabs(sum.mass()-wMass_) ){
// 	  wDist=fabs(sum.mass()-wMass_);
// 	  closestToWMassIndices.clear();
// 	  closestToWMassIndices.push_back(maxPtIndices[idx]);
// 	  closestToWMassIndices.push_back(maxPtIndices[jdx]);
// 	}
//       }
//     }
//   }
// 
//   // -----------------------------------------------------
//   // associate the remaining jet with maximum pt of the   
//   // vectorial sum with the leading lepton with the 
//   // leptonic decay chain
//   // -----------------------------------------------------
//   maxPt=-1.;
//   int lepB=-1;
//   for(int idx=0; idx<maxNJets; ++idx){
//     if(useBTagging_ && !isBJet[idx]) continue;
//     // make sure it's not used up already from the hadronic decay chain
//     if( std::find(maxPtIndices.begin(), maxPtIndices.end(), idx) == maxPtIndices.end() ){
//       reco::Particle::LorentzVector sum = 
// 	(*jets)[idx].p4()+(*leps)[ 0 ].p4();
//       if( maxPt<0. || maxPt<sum.pt() ){
// 	maxPt=sum.pt();
// 	lepB=idx;
//       }
//     }
//   }
