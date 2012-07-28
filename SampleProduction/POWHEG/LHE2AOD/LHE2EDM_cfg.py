# Auto generated configuration file
# using: 
# Revision: 1.303.2.7 
# Source: /cvs/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: LHEtoEDM --conditions auto:mc -s NONE --eventcontent RAWSIM --datatier GEN --filein /user.test.lhe --no_exec --python_filename TTbar-mcatnlo-5217-wSc_LHE2EDM_cfg.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('LHE')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("LHESource",
    fileNames = cms.untracked.vstring('/user.test.lhe')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('LHEtoEDM nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('TT_mcatnlo_private_massTop-172.5_withSC_LHE2EDM.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_42_V12::All'

# Path and EndPath definitions
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.RAWSIMoutput_step)
##FH input output configuration
useCrab = False
if not useCrab:
 from FWCore.ParameterSet.VarParsing import VarParsing
 options = VarParsing ('analysis')
 options.parseArguments()
 if options.inputFiles != cms.untracked.vstring():
  process.source.fileNames=cms.untracked.vstring(options.inputFiles)
 if options.outputFile != None:
  process.RAWSIMoutput.fileName = cms.untracked.string(options.outputFile)

