#include "TH1D.h"
#include "PhysicsTools/UtilAlgos/interface/BasicAnalyzer.h"

/**
   \class BasicMuonAnalyzer BasicMuonAnalyzer.h "PhysicsTools/UtilAlgos/interface/BasicMuonAnalyzer.h"
   \brief Example class that can be used both within FWLite and within the full framework

   This is an example for keeping classes that can be used both within FWLite and within the full 
   framework. The class is derived from the BasicAnalyzer base class, which is an interface for 
   the two wrapper classes EDAnalyzerWrapper and FWLiteAnalyzerWrapper. The latter provides basic 
   configuration file reading and event looping equivalent to the FWLiteHistograms executable of 
   this package. You can see the FWLiteAnalyzerWrapper class at work in the FWLiteWithBasicAnalyzer
   executable of this package.
*/

class M3MassAnalyzer : public edm::BasicAnalyzer {

 public:
  /// default constructor
  M3MassAnalyzer(const edm::ParameterSet& cfg, TFileDirectory& fs);
  /// default destructor
  virtual ~M3MassAnalyzer(){};
  /// everything that needs to be done before the event loop
  void beginJob(){};
  /// everything that needs to be done after the event loop
  void endJob(){};
  /// everything that needs to be done during the event loop
  void analyze(const edm::EventBase& event);

 private:
  /// input tag for mouns
  edm::InputTag jetTag_;
  /// histograms
  TH1D* h_M3Mass;
};
