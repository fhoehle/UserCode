#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/ServiceRegistry/interface/ServiceMaker.h"

#include "ex1/M3MassAnalyzer/interface/M3MassAnalyzer.h"
#include "PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h"
typedef edm::AnalyzerWrapper<M3MassAnalyzer> EDM3MassAnalyzer;
DEFINE_FWK_MODULE(EDM3MassAnalyzer);

