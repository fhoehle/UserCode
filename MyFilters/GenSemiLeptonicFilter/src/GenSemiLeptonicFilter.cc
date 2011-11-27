// -*- C++ -*-
//
// Package:    GenSemiLeptonicFilter
// Class:      GenSemiLeptonicFilter
// 
/**\class GenSemiLeptonicFilter GenSemiLeptonicFilter.cc MyFilters/GenSemiLeptonicFilter/src/GenSemiLeptonicFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Hoehle,,,RWTH
//         Created:  Thu Oct 20 23:12:01 CEST 2011
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
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

//
// class declaration
//

class GenSemiLeptonicFilter : public edm::EDFilter {
   public:
      explicit GenSemiLeptonicFilter(const edm::ParameterSet&);
      ~GenSemiLeptonicFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

	edm::InputTag src_;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenSemiLeptonicFilter::GenSemiLeptonicFilter(const edm::ParameterSet& iConfig):
src_(iConfig.getParameter<edm::InputTag>("src"))
{
   //now do what ever initialization is needed
}


GenSemiLeptonicFilter::~GenSemiLeptonicFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GenSemiLeptonicFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<TtSemiLeptonicEvent > ttSemiLepEvent_;
  iEvent.getByLabel( src_, ttSemiLepEvent_ );
  bool isSemiMuonic =  ttSemiLepEvent_->genEvent()->isSemiLeptonic() && abs(ttSemiLepEvent_->singleLepton()->pdgId()) == 13;
  return isSemiMuonic;
}

// ------------ method called once each job just before starting event loop  ------------
void 
GenSemiLeptonicFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenSemiLeptonicFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
GenSemiLeptonicFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
GenSemiLeptonicFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
GenSemiLeptonicFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
GenSemiLeptonicFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenSemiLeptonicFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(GenSemiLeptonicFilter);
