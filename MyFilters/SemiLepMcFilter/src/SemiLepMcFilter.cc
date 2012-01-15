// -*- C++ -*-
//
// Package:    SemiLepMcFilter
// Class:      SemiLepMcFilter
// 
/**\class SemiLepMcFilter SemiLepMcFilter.cc MyFilters/SemiLepMcFilter/src/SemiLepMcFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Hoehle
//         Created:  Fri Dec  3 14:16:41 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//
// class declaration
//

class SemiLepMcFilter : public edm::EDFilter {
   public:
      explicit SemiLepMcFilter(const edm::ParameterSet&);
      ~SemiLepMcFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag ttbarEventTag_;

//	bool isLeptonic(reco::GenParticle part);
	bool isMuonic(reco::GenParticle part);
	bool isHadronic(reco::GenParticle part);
      // ----------member data ---------------------------
};
//bool SemiLepMcFilter::isLeptonic(reco::GenParticle part){
//	if(abs(part.pdgId()) >= 11 && abs(part.pdgId()) <= 14 ) return true;
//	else return false;
//}
bool SemiLepMcFilter::isMuonic(reco::GenParticle part){
	return (abs(part.pdgId()) >= 13 && abs(part.pdgId()) <= 14 );
}
bool SemiLepMcFilter::isHadronic(reco::GenParticle part){
	return (abs(part.pdgId()) <=6 && part.pdgId()!= 0 );
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
SemiLepMcFilter::SemiLepMcFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
	ttbarEventTag_ = iConfig.getUntrackedParameter<edm::InputTag>("ttbarEventTag");
}


SemiLepMcFilter::~SemiLepMcFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
SemiLepMcFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	edm::Handle< edm::View< reco::GenParticle> > ttbarEvent; //std::vector< std::vector<std::vector<reco::GenParticle> > >
    	iEvent.getByLabel(ttbarEventTag_, ttbarEvent);
	reco::GenParticle WplusDecay1; WplusDecay1 = (*ttbarEvent)[3];
	reco::GenParticle WplusDecay2; WplusDecay2 = (*ttbarEvent)[4];
	
	reco::GenParticle WminusDecay1; WminusDecay1 = (*ttbarEvent)[8];
	reco::GenParticle WminusDecay2; WminusDecay2 = (*ttbarEvent)[9];


	bool muonicDecayWplus = (isMuonic(WplusDecay1) && isMuonic(WplusDecay2));
	bool muonicDecayWminus = (isMuonic(WminusDecay1) && isMuonic(WminusDecay2));

	bool hadronicDecayWplus = (isHadronic(WplusDecay1) && isHadronic(WplusDecay2));
	bool hadronicDecayWminus = (isHadronic(WminusDecay1) && isHadronic(WminusDecay2));
	//if( (leptonicDecayWplus && !leptonicDecayWminus) || (!leptonicDecayWplus && leptonicDecayWminus) ){
   		
		//std::cout<<"bling"<<std::endl;
	//	return true;
	//}
	//else return false;
	return ((muonicDecayWplus && hadronicDecayWminus) || ( muonicDecayWminus && hadronicDecayWplus)); 
}

// ------------ method called once each job just before starting event loop  ------------
void 
SemiLepMcFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SemiLepMcFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(SemiLepMcFilter);
