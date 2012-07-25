import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process('Test')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("MCatNLOSource",
                            fileNames = cms.untracked.vstring('file:ttb.events'),
                            processCode = cms.int32(-11706),
                            skipEvents=cms.untracked.uint32(0)

)
if options.inputFiles != cms.untracked.vstring():
 process.source.fileNames=cms.untracked.vstring(options.inputFiles)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))


process.RandomNumberGeneratorService.generator = cms.PSet(
        initialSeed = cms.untracked.uint32(123456789),
        engineName = cms.untracked.string('HepJamesRandom')
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.writer = cms.EDAnalyzer("LHEWriter",
	fileName = cms.untracked.string("test.lhe")
)
print options.outputFile
if options.outputFile != None:
 process.writer.fileName = cms.untracked.string(options.outputFile)
 print process.writer.fileName
print process.writer
process.p = cms.Path(process.writer)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

