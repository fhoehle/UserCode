#include "WeekExPart1/M3MassAnalyzer/interface/M3MassAnalyzer.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "PhysicsTools/UtilAlgos/interface/FWLiteAnalyzerWrapper.h"

typedef fwlite::AnalyzerWrapper<M3MassAnalyzer> FWLiteM3MassAnalyzer;

int main(int argc, char* argv[]) 
{
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();

  // only allow one argument for this simple example which should be the
  // the python cfg file
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }
  if( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ){
    std::cout << " ERROR: ParametersSet 'plot' is missing in your configuration file" << std::endl; exit(0);
  }

  FWLiteM3MassAnalyzer ana(edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process"), std::string("M3MassAnalyzer"), std::string("analyzeBasicPat"));
  ana.beginJob();
  ana.analyze();
  ana.endJob();
  return 0;
}
