// -*- C++ -*-
//
// Package:    AddPileUpWeightsProducer
// Class:      AddPileUpWeightsProducer
// 
/**\class AddPileUpWeightsProducer AddPileUpWeightsProducer.cc MyProducers/AddPileUpWeightsProducer/src/AddPileUpWeightsProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Hoehle
//         Created:  Thu Mar 29 00:39:36 CEST 2012
// $Id: AddPileUpWeightsProducer.cc,v 1.2 2012/08/11 16:34:50 fhohle Exp $
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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

//
// class declaration
//

class AddPileUpWeightsProducer : public edm::EDProducer {
   public:
      explicit AddPileUpWeightsProducer(const edm::ParameterSet&);
      ~AddPileUpWeightsProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
	edm::InputTag vertexSrc_;

  edm::LumiReWeighting LumiWeights_;
  std::string PileupFile1_;
  std::string PileupFile2_;
  std::string PUHistname2_;
  std::string PUHistname1_;

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
AddPileUpWeightsProducer::AddPileUpWeightsProducer(const edm::ParameterSet& iConfig):
vertexSrc_(iConfig.getParameter<edm::InputTag>("vertexSrc")),
PileupFile1_(iConfig.getParameter<std::string>("pileupFile1")),
PileupFile2_(iConfig.getParameter<std::string>("pileupFile2")),
PUHistname1_(iConfig.getParameter<std::string>("PUHistname1")),
PUHistname2_(iConfig.getParameter<std::string>("PUHistname2"))
{
   //register your products
   produces<double>();
/*
   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  LumiWeights_ = edm::LumiReWeighting(PileupFile1_.c_str(),PileupFile2_.c_str(),PUHistname1_.c_str(),PUHistname2_.c_str());
//"/user/hoehle/CMSSW/CMSSW_4_4_2_patch6/src/MyAnalysisSettings/PileUpReweighting/input/pileUpHistos_TTbar-SemiMu_Selected_Reconstructed.root",//"/uscms_data/d2/mikeh/work/CMSDAS/Fall2011_MCdist_finebin.root",
//                                      "/user/hoehle/CMSSW/CMSSW_4_4_2_patch6/src/MyAnalysisSettings/PileUpReweighting/input/Test_Data_Run2011A_Pileup.root",//"/uscms_data/d2/mikeh/work/CMSDAS/Data_May10ReReco_Pileup.root",
//                                      "h1_TNPUTrue", //"F2011exp",
//
//                                      "pileup");  
//  LumiWeights_ = edm::LumiReWeighting("/afs/cern.ch/work/f/fhohle/CMSSW/CMSSW_SampleProduction/CMSSW_4_2_8_patch7/src/MyProducers/AddPileUpWeightsProducer/input/pileUpHistos_TTbar-SemiMu_Selected_Reconstructed.root",//"/uscms_data/d2/mikeh/work/CMSDAS/Fall2011_MCdist_finebin.root",
//                                      "/afs/cern.ch/work/f/fhohle/CMSSW/CMSSW_SampleProduction/CMSSW_4_2_8_patch7/src/MyProducers/AddPileUpWeightsProducer/input/Test_Data_Run2011A_Pileup.root",//"/uscms_data/d2/mikeh/work/CMSDAS/Data_May10ReReco_Pileup.root",
//                                      "h1_TNPUTrue", //"F2011exp",
//                                      "pileup");

}


AddPileUpWeightsProducer::~AddPileUpWeightsProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
AddPileUpWeightsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;


  float npT=-1.;
  float npIT=-1.;


  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {

    int BX = PVI->getBunchCrossing();

    if(BX == 0) {
      npT = PVI->getTrueNumInteractions();
      npIT = PVI->getPU_NumInteractions();
    }
  }
  edm::Handle<std::vector<reco::Vertex> > recVtx;
  iEvent.getByLabel(vertexSrc_,recVtx);
  std::cout<<"offlinePrimVtx "<<recVtx->size()<<std::endl;
  std::cout<<" npT "<<npT<<std::endl;
  double MyWeight = LumiWeights_.weight( npT );
  std::cout<<"myPUweight "<<MyWeight<<std::endl;
  std::cout<<"newPUWeight "<<LumiWeights_.weight( (int)recVtx->size()-1 );
  double MyNewWeight = LumiWeights_.weight( (int)recVtx->size()-1 ); 
//   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));*/
	std::auto_ptr<double> pOut(new double());
   *pOut=MyNewWeight;
   iEvent.put(pOut);


/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
AddPileUpWeightsProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AddPileUpWeightsProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
AddPileUpWeightsProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
AddPileUpWeightsProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
AddPileUpWeightsProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
AddPileUpWeightsProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AddPileUpWeightsProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AddPileUpWeightsProducer);
