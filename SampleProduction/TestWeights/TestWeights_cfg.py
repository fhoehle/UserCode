# Auto generated configuration file
# using: 
# Revision: 1.303.2.7 
# Source: /cvs/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: LHEtoEDM --conditions auto:mc -s NONE --eventcontent RAWSIM --datatier GEN --filein /user.test.lhe --no_exec --python_filename TTbar-mcatnlo-5217-wSc_LHE2EDM_cfg.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('TestWeights')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)


# import of standard configurations
#process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
#process.load('SimGeneral.MixingModule.mixNoPU_cfi')
#process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('')
)

process.options = cms.untracked.PSet(

)

#process.analysisWeights = cms.EDAnalyzer("AnalysisWeights")
process.addMCWeight = cms.EDProducer("AddMCWeightProducer"
)
process.addPileupInfo = cms.EDProducer("AddPileUpWeightsProducer",
                                  vertexSrc = cms.InputTag("offlinePrimaryVertices"),
  pileupFile1 = cms.string("$CMSSW_BASE/src/MyProducers/AddPileUpWeightsProducer/input/pileUpHistos_TTbar-SemiMu_Selected_Reconstructed.root"),
  pileupFile2 = cms.string("$CMSSW_BASE/src/MyProducers/AddPileUpWeightsProducer/input/Test_Data_Run2011A_Pileup.root"),
  PUHistname1 = cms.string("h1_TNPUTrue"),
  PUHistname2 = cms.string("pileup") 
)

process.p = cms.Path(process.addMCWeight*process.addPileupInfo)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root'),
	outputCommands = cms.untracked.vstring("drop *","keep *_*_*_TestWeights")
)


process.e = cms.EndPath(process.out)

# Additional output definition
useCrab = False
if not useCrab:
 from FWCore.ParameterSet.VarParsing import VarParsing
 options = VarParsing ('analysis')
 options.parseArguments()
 if options.inputFiles != cms.untracked.vstring():
  process.source.fileNames=cms.untracked.vstring(options.inputFiles)

