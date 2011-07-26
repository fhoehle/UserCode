#include "TtbarReconstructions/Tools/interface/MyMEzCalculator.h"
#include "TMath.h"

/// constructor
MyMEzCalculator::MyMEzCalculator() 
{
  isComplex_ = false;
  isMuon_ = true;
}

/// destructor
MyMEzCalculator::~MyMEzCalculator() 
{
}

/// member functions
std::vector<double>
MyMEzCalculator::TwoSolCalculate()
{
//   if(type<0 || type>3)
//     throw cms::Exception("UnimplementedFeature") << "Type " << type << " not supported in MEzCalculator.\n";

  double M_W  = 80.4;
  double M_mu =  0.10566;
  double M_e = 0.511e-3;
  double M_lepton = M_mu;
  if (! isMuon_ ) M_lepton = M_e;
  
  double emu = lepton_.energy();
  double pxmu = lepton_.px();
  double pymu = lepton_.py();
  double pzmu = lepton_.pz();
  double pxnu = MET_.px();
  double pynu = MET_.py();
  double pznu = 0.;

//   use pznu = - B/2*A +/- sqrt(B*B-4*A*C)/(2*A)
  
  double a = M_W*M_W - M_lepton*M_lepton + 2.0*(pxmu*pxnu + pymu*pynu);
  double A = 4.0*(emu*emu - pzmu*pzmu);
  double B = -4.0*a*pzmu;
  double C = 4.0*emu*emu*(pxnu*pxnu + pynu*pynu) - a*a;
  
  double tmproot = B*B - 4.0*A*C;
  
	
	double sol1 = 0;
	double sol2 = 0;

  if (tmproot<=0) {
    isComplex_= true;
    sol1 = sol2 = - B/(2.0*A); // take real part of complex roots
  }
  else {
    isComplex_ = false;
    sol1 = (-B + TMath::Sqrt(tmproot))/(2.0*A);
    sol2 = (-B - TMath::Sqrt(tmproot))/(2.0*A);
  }
  std::vector<double> sols;
  sols.push_back(sol1); sols.push_back(sol2);

//   Particle neutrino;
//   neutrino.setP4( LorentzVector(pxnu, pynu, pznu, TMath::Sqrt(pxnu*pxnu + pynu*pynu + pznu*pznu ))) ;
  
  return sols;
}
