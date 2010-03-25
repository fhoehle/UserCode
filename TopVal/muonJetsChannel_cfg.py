import FWCore.ParameterSet.Config as cms
from JetMETCorrections.Configuration.JetCorrectionsRecord_cfi import *
process = cms.Process("TopDQMSemiMuon")

process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")
process.DQM.collectorHost = ''

process.dqmSaver.workflow = cms.untracked.string('/My/Test/DataSet')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200)
)

process.source = cms.Source(
    "PoolSource"
    ,fileNames = cms.untracked.vstring(
     '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0011/FE3B3C36-B413-DF11-9F84-002618FDA216.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/EC6B5FD5-6013-DF11-9795-001BFCDBD100.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/AE53FEB0-5F13-DF11-956B-001A928116C0.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/3621BC47-6013-DF11-9376-001731AF6A7D.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/280BA505-6513-DF11-867B-001A92971BB2.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/222EAB18-6B13-DF11-97D3-001A92971AEC.root',
        '/store/relval/CMSSW_3_4_2/RelValProdTTbar/GEN-SIM-RECO/MC_3XY_V15-v1/0010/166D53B0-6613-DF11-A4DC-0030486791C6.root'
    )
)
## add jet/MET corrections
process.load("JetMETCorrections.Configuration.L2L3Corrections_Summer09_7TeV_cff")

process.prefer("L2L3JetCorrectorAK5Calo")

# MET correction for Muons
from JetMETCorrections.Type1MET.MuonMETValueMapProducer_cff import *
from JetMETCorrections.Type1MET.MetMuonCorrections_cff import *
from JetMETCorrections.Type1MET.MetType1Corrections_cff import *

process.load("JetMETCorrections.Type1MET.MetType1Corrections_cff")
process.load("JetMETCorrections.Type1MET.MetMuonCorrections_cff")
## define process
process.load("DQM.Physics.leptonJetsChecker_cfi")
## configure semi-leptonic channel (muon)
process.leptonJetsChecker.Luminosity             =    20   ## in pb-1
process.leptonJetsChecker.MuonRelIso             =  0.05   ## relative isolation for muon
process.leptonJetsChecker.ApplyMETCut            = False   ##
process.leptonJetsChecker.VetoLooseLepton        =  True   ## 
process.leptonJetsChecker.PtThrMuonLoose         =  10.0   ## pt threshold for second muon veto
process.leptonJetsChecker.EtaThrMuonLoose        =   2.5   ## eta range for second muon veto 
process.leptonJetsChecker.RelIsoThrMuonLoose     =   0.2   ##
process.leptonJetsChecker.PtThrElectronLoose     =  15.0   ##
process.leptonJetsChecker.RelIsoThrElectronLoose =   0.2   ##
process.p = cms.Path(
		    process.metJESCorAK5CaloJet+
       		    process.leptonJetsChecker +
                     process.dqmSaver
                     )

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
