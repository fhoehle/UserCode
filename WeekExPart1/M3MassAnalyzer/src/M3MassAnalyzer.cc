#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "ex1/M3MassAnalyzer/interface/M3MassAnalyzer.h"


/// default constructor
M3MassAnalyzer::M3MassAnalyzer(const edm::ParameterSet& cfg, TFileDirectory& fs): 
  edm::BasicAnalyzer::BasicAnalyzer(cfg, fs),
  jetTag_(cfg.getParameter<edm::InputTag>("jetTag"))
{
  h_M3Mass = fs.make<TH1D>("M3Mass"  , "M3Mass"  ,  200,  0., 800.);
}

/// everything that needs to be done during the event loop
void 
M3MassAnalyzer::analyze(const edm::EventBase& event)
{
  // Handle to the jet collection
  edm::Handle<std::vector<pat::Jet> > jets;
  event.getByLabel(jetTag_, jets);
  double M3Mass = ((*jets)[0].p4() + (*jets)[1].p4() + (*jets)[2].p4()).M();
  h_M3Mass->Fill(M3Mass);
}
