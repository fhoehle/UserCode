import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    "file:/afs/cern.ch/user/f/fhohle/scratch0/PatTutorial/myPATtut/ex1/CMSSW_4_2_5/src/ex1/patTuple.root"
  )
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger = cms.Service("MessageLogger")

## ---
## This is an example of the use of the BasicAnalyzer concept used to exploit C++ classes to do anaysis
## in full framework or FWLite using the same class. You can find the implementation of this module in
## PhysicsTools/UtilAlgos/plugins/WrappedEDMuonAnlyzer. You can find the EDAnalyzerWrapper.h class in
## PhysicsTools/UtilAlgos/interface/EDAnalyzerWrapper.h. You can find the implementation of the
## BasicMuonAnalyzer class in PhysicsTools/UtilAlgos/interface/BasicMuonAnlyzer.h. You will also find
## back the input parameters to the module.
process.M3MassAnalyzer = cms.EDAnalyzer("EDM3MassAnalyzer",
  jetTag = cms.InputTag("cleanPatJets"),                                             
)

process.TFileService = cms.Service("TFileService",
  fileName = cms.string('analyzeCMSSWM3MassAnalyzer.root')
)

process.p = cms.Path(process.M3MassAnalyzer)

