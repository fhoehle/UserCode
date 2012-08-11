// -*- C++ -*-
//
// Package:    AddMCWeightProducer
// Class:      AddMCWeightProducer
// 
/**\class AddMCWeightProducer AddMCWeightProducer.cc MyProducers/AddMCWeightProducer/src/AddMCWeightProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Benedikt Hohle,32 4-B20,+41227676487,
//         Created:  Fri Aug 10 21:33:59 CEST 2012
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

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//
// class declaration
//

class AddMCWeightProducer : public edm::EDProducer {
   public:
      explicit AddMCWeightProducer(const edm::ParameterSet&);
      ~AddMCWeightProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

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
AddMCWeightProducer::AddMCWeightProducer(const edm::ParameterSet& iConfig)
{
   produces<double>();
 
  
}


AddMCWeightProducer::~AddMCWeightProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
AddMCWeightProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   edm::Handle<GenEventInfoProduct> evt_info;
   iEvent.getByType(evt_info);


   double weight = evt_info->weight();

   if(!weight) std::cout<< "MCWeight is corrupted"<<std::endl;
   double sign = (weight >= 0) ? 1 : -1;

   std::auto_ptr<double> pout(new double(weight));
   iEvent.put(pout);
}

// ------------ method called once each job just before starting event loop  ------------
void 
AddMCWeightProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AddMCWeightProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
AddMCWeightProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
AddMCWeightProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
AddMCWeightProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
AddMCWeightProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AddMCWeightProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AddMCWeightProducer);
