# Auto generated configuration file
# using: 
# Revision: 1.303.2.7 
# Source: /cvs/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/python/TT_7TeV_mcatnlo_cff.py -s GEN,FASTSIM,HLT --geometry DB --datatier AODSIM -n 100 --filein /store/user/fhohle/FastSim_MCatNLOwSC_offSummer11_LHE2EDM_120428/FastSim_MCatNLOwSC_offSummer11_LHE2EDM_120428/6c743465271a51929ca60e76e090b219/TT_7TeV_mcatnlo-5217_wSC_LHE2EDM_7_1_RV5.root --eventcontent AODSIM --pileup FlatDist10_2011EarlyData_50ns --conditions auto:mc --no_exec --python_filename TTbar-mcatnlo-wSc_PU_S4_FastSim_AOD_cfg.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('FastSimulation.Configuration.EventContent_cff')
process.load('FastSimulation.PileUpProducer.PileUpSimulator_FlatDist10_2011EarlyData_50ns_cff')
process.load('FastSimulation.Configuration.Geometries_MC_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('FastSimulation.Configuration.FamosSequences_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedParameters_cfi')
process.load('FastSimulation.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/user/fhohle/FastSim_mcatnlo-5217_LHE2EDM_v1_Desy_0518/FastSim_mcatnlo-5217_LHE2EDM_v1_Desy_0518//6c743465271a51929ca60e76e090b219/TT_7TeV_mcatnlo-5217_LHE2EDM_101_1_qEr.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.303.2.7 $'),
    annotation = cms.untracked.string('Configuration/Generator/python/TT_7TeV_mcatnlo_cff.py nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    outputCommands = process.AODSIMEventContent.outputCommands,
    fileName = cms.untracked.string('TT_7TeV_mcatnlo_cff_py_herwig-5217_GEN_FASTSIM_HLT_PU_withSC.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('AODSIM')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.famosSimHits.SimulateCalorimetry = True
process.famosSimHits.SimulateTracking = True
process.simulation = cms.Sequence(process.simulationWithFamos)
process.HLTEndSequence = cms.Sequence(process.reconstructionWithFamos)
process.Realistic7TeV2011CollisionVtxSmearingParameters.type = cms.string("BetaFunc")
process.famosSimHits.VertexGenerator = process.Realistic7TeV2011CollisionVtxSmearingParameters
process.famosPileUp.VertexGenerator = process.Realistic7TeV2011CollisionVtxSmearingParameters
process.GlobalTag.globaltag = 'MC_42_V12::All'

process.generator = cms.EDFilter("Herwig6HadronizerFilter",
    HerwigParameters = cms.PSet(
        parameterSets = cms.vstring('herwigUEsettings', 
            'herwigMcatnlo'),
        herwigMcatnlo = cms.vstring('PTMIN      = 0.5    ! minimum pt in hadronic jet'),
        herwigUEsettings = cms.vstring('JMUEO     = 1       ! multiparton interaction model', 
            'PTJIM     = 4.449   ! 2.8x(sqrt(s)/1.8TeV)^0.27 @ 10 TeV', 
            'JMRAD(73) = 1.8     ! inverse proton radius squared', 
            'PRSOF     = 0.0     ! prob. of a soft underlying event', 
            'MAXER     = 1000000 ! max error')
    ),
    doMPInteraction = cms.bool(True),
    useJimmy = cms.bool(True),
    herwigHepMCVerbosity = cms.untracked.bool(False),
    filterEfficiency = cms.untracked.double(1.0),
    herwigVerbosity = cms.untracked.int32(0),
    emulatePythiaStatusCodes = cms.untracked.bool(True),
    comEnergy = cms.double(7000.0),
    lhapdfSetPath = cms.untracked.string(''),
    printCards = cms.untracked.bool(False),
    crossSection = cms.untracked.double(0.523),
    maxEventsToPrint = cms.untracked.int32(0)
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen_genonly)
process.reconstruction = cms.Path(process.reconstructionWithFamos)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.reconstruction,process.AODSIMoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 
##FH input output configuration
useCrab = False
if not useCrab:
 from FWCore.ParameterSet.VarParsing import VarParsing
 options = VarParsing ('analysis')
 options.parseArguments()
 if options.inputFiles != cms.untracked.vstring():
  process.source.fileNames=cms.untracked.vstring(options.inputFiles)
 if options.outputFile != None:
  process.AODSIMoutput.fileName = cms.untracked.string(options.outputFile)


