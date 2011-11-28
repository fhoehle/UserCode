import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring('/afs/cern.ch/user/f/fhohle/scratch0/PatTutorial/myPATtut/ex1/CMSSW_4_2_5/src/ex1/myLocal_nonsemi_patTuple.root'), ## mandatory /afs/cern.ch/user/f/fhohle/scratch0/PatTutorial/myPATtut/ex1/CMSSW_4_2_5/src/ex1/myLocal_patTuple.root
   # maxEvents   = cms.int32(100),                            ## optional
    outputEvery = cms.uint32(10),                            ## optional
)
    
process.fwliteOutput = cms.PSet(
    fileName  = cms.string('analyzeFWLiteM3MassAnalyzer_nonsemi.root'),  ## mandatory
)

process.M3MassAnalyzer = cms.PSet(
    ## input specific for this analyzer
    jetTag = cms.InputTag('cleanPatJets')
)
