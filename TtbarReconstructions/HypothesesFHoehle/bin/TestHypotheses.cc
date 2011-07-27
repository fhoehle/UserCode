#include <TSystem.h>
#include <TROOT.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include "TStyle.h"
#include "TPaveStats.h"
//
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "Math/VectorUtil.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
//
#include "TtbarReconstructions/HypothesesFHoehle/bin/plotCommon.hpp"
double cosThetaStar(reco::Particle::LorentzVector lep, reco::Particle::LorentzVector Wlep, reco::Particle::LorentzVector toplep){
	reco::Particle::LorentzVector genLepBoosted = ROOT::Math::VectorUtil::boost( lep,Wlep.BoostToCM() );	
	reco::Particle::LorentzVector gentopBoosted = ROOT::Math::VectorUtil::boost( Wlep,toplep.BoostToCM() );
	return cos( ROOT::Math::VectorUtil::Angle(genLepBoosted, gentopBoosted) );
}
double cosThetaStar_tqafHyp(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	// check Event and Hypo are okay
	if(!tqaf_semiLepEvt->leptonicDecayTop(hypoClassKey) && !tqaf_semiLepEvt->leptonicDecayW(hypoClassKey) && !tqaf_semiLepEvt->singleLepton(hypoClassKey) ) return -2.0;
	// calc cos ThetaStar
	return  cosThetaStar((tqaf_semiLepEvt->singleLepton(hypoClassKey))->p4(),(tqaf_semiLepEvt->leptonicDecayW(hypoClassKey))->p4(),(tqaf_semiLepEvt->leptonicDecayTop(hypoClassKey))->p4() );
}
//void FWLite_RecoVgl()
double DeltaRNu_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return ROOT::Math::VectorUtil::DeltaR( tqaf_semiLepEvt->singleNeutrino()->p4() ,  tqaf_semiLepEvt->singleNeutrino(hypoClassKey)->p4() );
}
double DeltaPxNu_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return (tqaf_semiLepEvt->singleNeutrino()->px() -  tqaf_semiLepEvt->singleNeutrino(hypoClassKey)->px()) ;
}
double DeltaPyNu_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return (tqaf_semiLepEvt->singleNeutrino()->py() -  tqaf_semiLepEvt->singleNeutrino(hypoClassKey)->py()) ;
}
double DeltaPzNu_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return (tqaf_semiLepEvt->singleNeutrino()->pz() -  tqaf_semiLepEvt->singleNeutrino(hypoClassKey)->pz()) ;
}
double DeltaCosT_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return cosThetaStar( tqaf_semiLepEvt->singleLepton()->p4() ,tqaf_semiLepEvt->leptonicDecayW()->p4() , tqaf_semiLepEvt->leptonicDecayTop()->p4() ) - cosThetaStar_tqafHyp(tqaf_semiLepEvt,hypoClassKey);
}
double DeltaRB_Gen_F(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return ROOT::Math::VectorUtil::DeltaR( tqaf_semiLepEvt->leptonicDecayB()->p4() ,  tqaf_semiLepEvt->leptonicDecayB(hypoClassKey)->p4() );
}
bool isHypoOKAY(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt, std::string hypoClassKey){
	return tqaf_semiLepEvt->isHypoAvailable(hypoClassKey) &&  tqaf_semiLepEvt->isHypoValid(hypoClassKey) && tqaf_semiLepEvt->leptonicDecayTop(hypoClassKey) && tqaf_semiLepEvt->leptonicDecayW(hypoClassKey) && tqaf_semiLepEvt->singleLepton(hypoClassKey)&& tqaf_semiLepEvt->singleNeutrino(hypoClassKey);
}
bool isGenOKAY(fwlite::Handle<TtSemiLeptonicEvent> tqaf_semiLepEvt){
	return /*tqaf_semiLepEvt->isHypoAvailable() &&*/ /* tqaf_semiLepEvt->isHypoValid() &&*/ tqaf_semiLepEvt->leptonicDecayTop() && tqaf_semiLepEvt->leptonicDecayW() && tqaf_semiLepEvt->singleLepton()&& tqaf_semiLepEvt->singleNeutrino();
}
int main(void)
{
  InitgStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetLabelSize(0.03, "XYZ");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat("nemruo");//1001100
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  // Hyps
  enum HypsEnum {kOwnPseudoGenBCalcNu,kOwnPseudoGenBMatchedCalcNu,kOwnPseudoMatchBJetCalcNu,kOwnPseudoMatchBJetGenNu,kOwnPseudoMatchBJetMatchedCalcNu,kOwnTopMassBTag,kOwnM3BTag,kHitFit,kKinFit,kGeom,kMaxSumPtWMass,kWMassDeltaTopMass,kWMassMaxSumPt};
  std::string myHypsa [] = {"kOwnPseudoGenBCalcNu","kOwnPseudoGenBMatchedCalcNu","kOwnPseudoMatchBJetCalcNu","kOwnPseudoMatchBJetGenNu","kOwnPseudoMatchBJetMatchedCalcNu","kOwnTopMassBTag","kOwnM3BTag","kHitFit","kKinFit","kGeom", "kMaxSumPtWMass", "kWMassDeltaTopMass","kWMassMaxSumPt"};
  std::vector<std::string> myHyps (myHypsa, myHypsa + sizeof(myHypsa) / sizeof(std::string) );
  //file
  TFile *Results = new TFile("Results.root","recreate");	
  //creating vectors ...
  const uint numHyps = myHyps.size();
  enum VabsEnum {DeltaRNu_Gen,DeltaPxNu_Gen,DeltaPyNu_Gen,DeltaPzNu_Gen,DeltaCosT_Gen,CosStar,DeltaRB_Gen};
  std::string myVabsA [] = {"DeltaRNu_Gen","DeltaPxNu_Gen","DeltaPyNu_Gen","DeltaPzNu_Gen","DeltaCosT_Gen","CosStar","DeltaRB_Gen"};
  std::vector<std::string> myVabs (myVabsA, myVabsA + sizeof(myVabsA) / sizeof(std::string) );
  const uint numVariables = myVabs.size();
  TH1D * h_Nupi_temp = new TH1D("h_Nupi_temp","h_Nupi_temp",500,-1000.0,1000.0);h_Nupi_temp->GetXaxis()->SetTitle(" Pi_{#nu} - Pi_{rec} ");
  std::vector<TH1D*> template_hists; template_hists.reserve(numVariables);
  template_hists[DeltaPxNu_Gen] = h_Nupi_temp; template_hists[DeltaPyNu_Gen] = h_Nupi_temp; template_hists[DeltaPzNu_Gen] = h_Nupi_temp;
  TH1D * h_DeltaR_temp = new TH1D("h_DeltaR_temp","h_DeltaR_temp",500,0.0,10.0);h_DeltaR_temp->GetXaxis()->SetTitle(" #Delta R_{#nu - rec} ");
  template_hists[DeltaRNu_Gen] = h_DeltaR_temp; template_hists[DeltaRB_Gen] = h_DeltaR_temp;
  TH1D * h_genCosStar_temp = new TH1D("h_genCosStar_temp","h_genCosStar_temp",10,-1.0,1.0);h_genCosStar_temp->GetXaxis()->SetTitle(" cos #theta * ");
  template_hists[CosStar] = h_genCosStar_temp;
  TH1D * h_CosStarDiff_temp = new TH1D("h_CosStarDiff_temp","h_CosStarDiff_temp",40,-2.0,2.0);
  template_hists[DeltaCosT_Gen] = h_CosStarDiff_temp;
  std::string test2;
  std::vector<TDirectory*> dirs;
  std::vector<TDirectory*> dirs_All;
  std::vector<std::vector<TH1D *> > histos;
  std::vector<std::vector<TH1D *> > histos_All;
  std::string PostFix = "_All";
  for (uint i=0;i<numHyps;i++) { 
    TDirectory *dir;
    dir = Results->mkdir(myHyps[i].c_str());
    dir->cd();
    dirs.push_back(dir);
    std::vector<TH1D*> hist;
    for (uint j=0;j<numVariables;j++) {
      test2.resize(0);
      test2 = myHyps[i];
      test2 += "_"; test2 += myVabs[j];
      TH1D * testhist = (TH1D*)template_hists[j]->Clone(test2.c_str());
      testhist->SetTitle(test2.c_str());
      hist.push_back(testhist);
    }
    histos.push_back(hist);
    Results->cd();    // change current directory to Result
    TDirectory *dir_All;
    std::vector<TH1D*> hist_All;
    dir_All = Results->mkdir((myHyps[i] + PostFix).c_str());
    dir_All->cd();
    dirs_All.push_back(dir_All);
    for (uint j=0;j<numVariables;j++) {
      test2.resize(0);
      test2 = myHyps[i];
      test2 += "_"; test2 += myVabs[j];
      TH1D * testhist = (TH1D*)template_hists[j]->Clone((test2 + PostFix).c_str());
      testhist->SetTitle((test2 + PostFix).c_str());
      hist_All.push_back(testhist);
    }
    histos_All.push_back(hist_All);
    Results->cd();
  }
  //read file and loop ...
  TFile file("/user/hoehle/TEST_CMSSW/CMSSW_4_2_5/src/TestHyps.root");
  fwlite::Event ev(&file);
  int counter = 0;
  for( ev.toBegin(); ! ev.atEnd(); ++ev , ++counter) {
    // tqaf
    fwlite::Handle<TtSemiLeptonicEvent> ttSemiLepEvent_Tqaf;
    ttSemiLepEvent_Tqaf.getByLabel(ev,"ttSemiLepEvent");
    //Kinematic variables
    fwlite::Handle<std::vector<pat::MET> > mets;
    mets.getByLabel(ev,"patMETsPF");
    //
    bool forAllHypsOk = true;
    for (uint i=0;i<numHyps;i++) {
      dirs[i]->cd();
      if(isGenOKAY(ttSemiLepEvent_Tqaf) && isHypoOKAY(ttSemiLepEvent_Tqaf,myHyps[i])){
        histos[i][DeltaRNu_Gen]->Fill(DeltaRNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][DeltaPxNu_Gen]->Fill(DeltaPxNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][DeltaPyNu_Gen]->Fill(DeltaPyNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][DeltaPzNu_Gen]->Fill(DeltaPzNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][DeltaCosT_Gen]->Fill(DeltaCosT_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][CosStar]->Fill(cosThetaStar_tqafHyp(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos[i][DeltaRB_Gen]->Fill(DeltaRB_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));	
      }
      else forAllHypsOk = forAllHypsOk && false;	
    }
    if(forAllHypsOk){
      for (uint i=0;i<numHyps;i++) {
        dirs_All[i]->cd();
        histos_All[i][DeltaRNu_Gen]->Fill(DeltaRNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][DeltaPxNu_Gen]->Fill(DeltaPxNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][DeltaPyNu_Gen]->Fill(DeltaPyNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][DeltaPzNu_Gen]->Fill(DeltaPzNu_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][DeltaCosT_Gen]->Fill(DeltaCosT_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][CosStar]->Fill(cosThetaStar_tqafHyp(ttSemiLepEvent_Tqaf,myHyps[i]));
        histos_All[i][DeltaRB_Gen]->Fill(DeltaRB_Gen_F(ttSemiLepEvent_Tqaf,myHyps[i]));
      }
    }	
  }
  Results->Write();
  delete Results;
  std::cout<<"counter : "<<counter<< " Events: "<<counter-1<<std::endl;
  return 0;
}
