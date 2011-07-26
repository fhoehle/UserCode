#ifndef TopTools_MyMEzCalculator_h
#define TopTools_MyMEzCalculator_h

/**_________________________________________________________________
   class:   MyMEzCalculator.h

 author: Felix Höhle, RWTH Aachen (hoehleNOSPAM@physik.rwth-aachen.de)

 version $Id: MyMEzCalculator.h,v 0.0 2011/6/28 11:01:15 hoehle Exp $

________________________________________________________________**/
#include "TopQuarkAnalysis/TopTools/interface/MEzCalculator.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "TLorentzVector.h"

class MyMEzCalculator  { //: public MEzCalculator

  
 public:
   /// constructor 
   MyMEzCalculator(); 
   /// destructor 
   ~MyMEzCalculator(); 
   /// Set MET 
   void SetMET(const pat::MET& MET) { MET_ = MET; } ; 
   void SetMET(TLorentzVector MET) { 
 	  pat::Particle::LorentzVector p(MET.Px(),MET.Py(),MET.Pz(),MET.E()); 
 	  MET_.setP4(p); 
   } 
   /// Set lepton 
   void SetLepton(const pat::Particle& lepton, bool isMuon = true) { 
 	  lepton_ = lepton; 
 	  isMuon_ = isMuon; 
   }; 
   void SetLepton(TLorentzVector lepton) { 
 	  pat::Particle::LorentzVector p(lepton.Px(), lepton.Py(), lepton.Pz(), lepton.E() ); 
 	  lepton_.setP4(p); 
   } 
   /// Calculate MEz 
   /// options to choose roots from quadratic equation: 
   /// type = 0 : if real roots, pick the one nearest to 
   ///                     the lepton Pz except when the Pz so chosen 
   ///                     is greater than 300 GeV in which case pick 
   ///                     the most central root. 
   /// type = 1 (default): if real roots, choose the one closest to the lepton Pz 
   ///           if complex roots, use only the real part. 
   /// type = 2: if real roots, choose the most central solution. 
   ///           if complex roots, use only the real part. 
 //   double Calculate(int type = 1); 
     std::vector<double> TwoSolCalculate();
   /// check for complex root 
   bool IsComplex() const { return isComplex_; }; 
   /// verbose 
   void Print() { 
 	  std::cout << " METzCalculator: pxmu = " << lepton_.px() << " pzmu= " << lepton_.pz() << std::endl; 
 	  std::cout << " METzCalculator: pxnu = " << MET_.px() << " pynu= " << MET_.py() << std::endl; 
   } 

  private: 
  
   bool isComplex_; 
   pat::Particle lepton_; 
   pat::MET MET_; 
   bool isMuon_; 


};

#endif
