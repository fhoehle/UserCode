// -*- C++ -*-
//
// Package:    MyCosThetaNupleMaker
// Class:      MyCosThetaNupleMaker
// 
/**\class MyCosThetaNupleMaker MyCosThetaNupleMaker.cc MyProducers/MyCosThetaNupleMaker/src/MyCosThetaNupleMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Hoehle
//         Created:  Tue Aug  2 16:27:32 CEST 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "Math/VectorUtil.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
//
// class declaration
//

class MyCosThetaNupleMaker : public edm::EDProducer {
   public:
      explicit MyCosThetaNupleMaker(const edm::ParameterSet&);
      ~MyCosThetaNupleMaker();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      double cosThetaStar(reco::Particle::LorentzVector lep, reco::Particle::LorentzVector Wlep, reco::Particle::LorentzVector toplep);
      edm::InputTag src_;
      std::string hypo_;
      double cosTRecT,cosTGenT;
      TTree * CosThetaStars_Tree;
      bool fillGen_;
      bool fillRec_;
      // ----------member data ---------------------------
};
double MyCosThetaNupleMaker::cosThetaStar(reco::Particle::LorentzVector lep, reco::Particle::LorentzVector Wlep, reco::Particle::LorentzVector toplep){
  reco::Particle::LorentzVector genLepBoosted = ROOT::Math::VectorUtil::boost( lep,Wlep.BoostToCM() );	
  reco::Particle::LorentzVector gentopBoosted = ROOT::Math::VectorUtil::boost( Wlep,toplep.BoostToCM() );
  return cos( ROOT::Math::VectorUtil::Angle(genLepBoosted, gentopBoosted) );
}
//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//

MyCosThetaNupleMaker::MyCosThetaNupleMaker(const edm::ParameterSet& iConfig) :
    src_( iConfig.getParameter<edm::InputTag>( "ttSemiLepEvent" ) ),
    hypo_( iConfig.getParameter<std::string>( "hypo" ) ),
    fillGen_(iConfig.getParameter<bool>("fillGen")),
    fillRec_(iConfig.getParameter<bool>("fillRec")){
      produces<std::vector<double> >( "cosThetaRec" );
      produces<std::vector<double> >( "cosThetaGen" )/*.setBranchAlias( "cosThetaGen" )*/;
	//produces<TH1F, edm::InRun>(histName_[i]).setBranchAlias(histName_[i]);
         //now do what ever initialization is needed
      edm::Service<TFileService> fs;
      if ( !fs.isAvailable() )
        throw cms::Exception("Configuration") << "TFileService not available: did you configure it?";
	// book Control TTree
      CosThetaStars_Tree = fs->make<TTree>("CosThetaStars_Tree", "CosThetaStars_Tree");
	//Angles
      CosThetaStars_Tree->Branch("cosTRec", &cosTRecT, "cosTRec/D");
      CosThetaStars_Tree->Branch("cosTGen", &cosTGenT, "cosTGen/D");
    }


MyCosThetaNupleMaker::~MyCosThetaNupleMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------

void MyCosThetaNupleMaker::produce( edm::Event & iEvent, const edm::EventSetup & iSetup ) {

	cosTRecT = cosTGenT = -3.0;

      	edm::Handle<TtSemiLeptonicEvent > ttSemiLepEvent_Tqaf;
      	iEvent.getByLabel( src_, ttSemiLepEvent_Tqaf );

	std::auto_ptr<std::vector<double> > cosThetaRec(new std::vector<double>);
	std::auto_ptr<std::vector<double> > cosThetaGen(new std::vector<double>);

	bool hypoOk = false;
	if(fillRec_){  
       		hypoOk = ttSemiLepEvent_Tqaf->isHypoAvailable(hypo_) &&  ttSemiLepEvent_Tqaf->isHypoValid(hypo_) && ttSemiLepEvent_Tqaf->leptonicDecayTop(hypo_) && ttSemiLepEvent_Tqaf->leptonicDecayW(hypo_) && ttSemiLepEvent_Tqaf->singleLepton(hypo_)&& ttSemiLepEvent_Tqaf->singleNeutrino(hypo_);
		cosTRecT = hypoOk ? cosThetaStar((ttSemiLepEvent_Tqaf->singleLepton(hypo_))->p4(),(ttSemiLepEvent_Tqaf->leptonicDecayW(hypo_))->p4(),(ttSemiLepEvent_Tqaf->leptonicDecayTop(hypo_))->p4()) : -2.0;
	}
	if(fillGen_){
		bool GenOk = /*ttSemiLepEvent_Tqaf->genEvent() != 0  && */(ttSemiLepEvent_Tqaf->genEvent())->isSemiLeptonic();
        	bool isSemiMuonic = GenOk && abs((ttSemiLepEvent_Tqaf->genEvent())->singleLepton()->pdgId()) == 13 ;
		cosTGenT = (isSemiMuonic ? cosThetaStar((ttSemiLepEvent_Tqaf->singleLepton())->p4(),(ttSemiLepEvent_Tqaf->leptonicDecayW())->p4(),(ttSemiLepEvent_Tqaf->leptonicDecayTop())->p4()) : -2.0);
	}
	CosThetaStars_Tree->Fill();
	cosThetaRec->push_back(cosTRecT);
	cosThetaGen->push_back(cosTGenT);
	iEvent.put(cosThetaRec,"cosThetaRec");
	iEvent.put(cosThetaGen,"cosThetaGen");
}

// ------------ method called once each job just before starting event loop  ------------
void 
MyCosThetaNupleMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyCosThetaNupleMaker::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
MyCosThetaNupleMaker::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MyCosThetaNupleMaker::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MyCosThetaNupleMaker::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MyCosThetaNupleMaker::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyCosThetaNupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyCosThetaNupleMaker);
