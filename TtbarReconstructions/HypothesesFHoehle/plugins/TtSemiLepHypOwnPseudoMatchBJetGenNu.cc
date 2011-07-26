#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "TtbarReconstructions/HypothesesFHoehle/plugins/TtSemiLepHypOwnPseudoMatchBJetGenNu.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
// OwnPseudoMatchBJetCalcNu
// #include "TopQuarkAnalysis/TopTools/interface/MyMEzCalculator.h"
#include "Math/VectorUtil.h"
TtSemiLepHypOwnPseudoMatchBJetGenNu::TtSemiLepHypOwnPseudoMatchBJetGenNu(const edm::ParameterSet& cfg):
  TtSemiLepHypothesis( cfg ),
  maxDeltaR_              (cfg.getParameter<double>   ("maxDeltaR"              )),
  maxEfrac_               (cfg.getParameter<double>   ("maxEfrac"               ))
//   topMass_                (cfg.getParameter<double>   ("topMass"                ))
{
  
}

TtSemiLepHypOwnPseudoMatchBJetGenNu::~TtSemiLepHypOwnPseudoMatchBJetGenNu() { }

void
TtSemiLepHypOwnPseudoMatchBJetGenNu::buildHypo(edm::Event& evt,
				     const edm::Handle<edm::View<reco::RecoCandidate> >& leps, 
				     const edm::Handle<std::vector<pat::MET> >& mets, 
				     const edm::Handle<std::vector<pat::Jet> >& jets, 
				     std::vector<int>& match, const unsigned int iComb)
{
  edm::Handle<TtGenEvent> genEvt;
  evt.getByLabel("genEvt", genEvt);

  if(leps->empty() || mets->empty() ||jets->empty() || jets->size() < 1 || !genEvt->isSemiLeptonic()|| genEvt->leptonicDecayB() == 0 ){
    // create empty hypothesis
	if(jets->empty() || jets->size() < 1 ) edm::LogWarning("Jets")<<"non sense jetNumber"<<"jets->size() "<< (jets->empty() ? -1 : jets->size());
	if( !genEvt->isSemiLeptonic()|| genEvt->leptonicDecayB() == 0 ) edm::LogWarning("genInfo")<<"genEvt->isSemiLeptonic() "<<genEvt->isSemiLeptonic()<<" genEvt->leptonicDecayB() "<<genEvt->leptonicDecayB();
    return;
  }
  int maxNJets = jets->size();
// 	std::cout<<" genEvt ask for blep "<<std::endl;
  const reco::GenParticle * blep_Gen = genEvt->leptonicDecayB();


// 		std::cout<<"found genParticle px: "<< blep_Gen->px()<<std::endl;
  int blepMatch_Idx = -1;
  double tempDeltaR = -1.0;   double tempMinDeltaR = -1.0;
   double Efrac = -1.0;
    for(int idx=0; idx<maxNJets; ++idx) {
// 	std::cout<<"before deltaR idx: "<<idx<<" jets->size() "<<jets->size() <<"  maxNJets "<<maxNJets<<std::endl;
	tempDeltaR = ROOT::Math::VectorUtil::DeltaR( blep_Gen->p4(), (*jets)[idx].p4() );
// 	std::cout<<"after deltaR"<<std::endl;
	Efrac = fabs( blep_Gen->energy()-(*jets)[idx].energy() )/blep_Gen->energy();
	if(tempDeltaR < maxDeltaR_ && Efrac < maxEfrac_ && (tempDeltaR < tempMinDeltaR || tempMinDeltaR == -1.0  ) ){  
		blepMatch_Idx = idx; tempMinDeltaR = tempDeltaR;
	}
    }
// 	std::cout<<"search for matching jet finished "<< blepMatch_Idx <<std::endl;
  if(blepMatch_Idx == -1) return;

	edm::Ptr<pat::MET> ptr = edm::Ptr<pat::MET>(mets, 0);
//   	MyMEzCalculator mez;
//     	mez.SetMET( *(mets->begin()) );
//     	mez.SetLepton( (*leps)[0], true );
//   	std::vector<double> nuzSols = mez.TwoSolCalculate();
// // 	std::cout<<"neutrino calc ended "<<nuzSols.size()<<std::endl;
// //   	numberOfRealNeutrinoSolutions_ = mez.IsComplex() ? 0 : 2;
//   	const math::XYZTLorentzVector nuSol1( ptr->px(), ptr->py(), nuzSols[0], sqrt(ptr->px()*ptr->px() + ptr->py()*ptr->py() + nuzSols[0]*nuzSols[0]) );
// 	const math::XYZTLorentzVector nuSol2( ptr->px(), ptr->py(), nuzSols[1], sqrt(ptr->px()*ptr->px() + ptr->py()*ptr->py() + nuzSols[1]*nuzSols[1]) );
// 	std::cout<<"nu Sols calculated"<<std::endl;
// 	std::cout<<"two neutrino sols set "<<nuzSols.size()<<std::endl;
	if(genEvt->singleNeutrino() == 0) return ;
// 	const math::XYZTLorentzVector nuSol = singleNeutrino( fabs( topMass_ - ( (*leps)[0].p4() + nuSol1 - (*jets)[blepMatch_Idx].p4() ).M()) < fabs( topMass_ - ( (*leps)[0].p4() + nuSol2 - (*jets)[blepMatch_Idx].p4() ).M() ) ) ? nuSol1 : nuSol2;
// 	std::cout<<"neutrino calc + conversion finished"<<std::endl;
	neutrino_ = new reco::ShallowClonePtrCandidate( ptr, ptr->charge(), genEvt->singleNeutrino()->p4(), ptr->vertex() );
// 	pat::MET neutrino = (*mets)[0];
//   	neutrino.setP4(nuSol);
// 	edm::Handle<std::vector<pat::MET> > mymets;
// 	(*mymets).push_back(neutrino);
	


  // -----------------------------------------------------
  // add jets
  // -----------------------------------------------------
// 	std::cout<<"add jets blepMatch_Idx: "<<blepMatch_Idx<<"  jets->size() "<<jets->size()<<std::endl;
     if( isValid(blepMatch_Idx, jets) ){
	// hadronic side set to nonsense values
	setCandidate(jets, blepMatch_Idx, lightQBar_, jetCorrectionLevel("wQuarkMix"));
    	match[TtSemiLepEvtPartons::LightQBar] = blepMatch_Idx;

    	setCandidate(jets, blepMatch_Idx, lightQ_, jetCorrectionLevel("wQuarkMix"));
    	match[TtSemiLepEvtPartons::LightQ] = blepMatch_Idx;

	setCandidate(jets, blepMatch_Idx, hadronicB_, jetCorrectionLevel("bQuark"));
	match[TtSemiLepEvtPartons::HadB] = blepMatch_Idx;
	//end hadronic section
    	setCandidate(jets, blepMatch_Idx, leptonicB_, jetCorrectionLevel("bQuark"));
    	match[TtSemiLepEvtPartons::LepB] = blepMatch_Idx;
  }
// 	std::cout<<"addlep "<<std::endl;
  // -----------------------------------------------------
  // add lepton
  // -----------------------------------------------------
  setCandidate(leps, 0, lepton_);
  match[TtSemiLepEvtPartons::Lepton] = 0;
//   std::cout<<"finish "<<std::endl;
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