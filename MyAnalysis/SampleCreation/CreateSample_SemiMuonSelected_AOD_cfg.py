import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
 
options = VarParsing ('analysis')
# add a list of strings for events to process
#options.register ('eventsToProcess',
#                   '',
#                   VarParsing.multiplicity.list,
#                   VarParsing.varType.string,
#                   "Events to process")
#options.register ('maxSize',
#                   0,
#                   VarParsing.multiplicity.singleton,
#                   VarParsing.varType.int,
#                   "Maximum (suggested) file size (in Kb)")

options.parseArguments()
process = cms.Process('TestSemiLepMcFilter')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
if options.maxEvents != '':
 process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
print process.maxEvents
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring()) #'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FED956DF-7F2A-E111-8124-002618943958.root',
#'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FE77BD53-752A-E111-AD03-002618943905.root',
#'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FE51F179-732A-E111-8586-002618943985.root',
#'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FE35F649-6F2A-E111-A7F7-00261894392C.root',
#'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FC77ECAD-7A2A-E111-829B-002618943877.root',
#'/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0001/FC2D45A8-672A-E111-BF45-0026189438C4.root')
#)
#if options.inputFiles != cms.untracked.vstring():
# process.source.fileNames=cms.untracked.vstring(options.inputFiles)

from MyAnalysisSettings.Samples.mySamples_cfi import mcatnlo_Fall11_AC 
process.source.fileNames = mcatnlo_Fall11_AC

process.load('Configuration.StandardSequences.Services_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

from MyFilters.SemiLepMcFilter.semiLepMcFilter_cfi import SemiLepMcFilter
process.SemiLepMcFilter = SemiLepMcFilter

from MyFilters.DiLepMcFilter.diLepMcFilter_cfi import DiLepMcFilter
process.DiLepMcFilter = DiLepMcFilter

process.load("MyProducers.MyTTbarGenEventLepHad.myTTbarGenEventLepHad_cfi")

process.SemiLepPath = cms.Path(process.MyTTbarGenEventProd*process.SemiLepMcFilter )
#process.DiLepPath = cms.Path(process.DiLepMcFilter)

process.output_SemiLep = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string('SemiLepMc_mcatnlo_AOD_SemiMu_selected.root'),
                                  SelectEvents = cms.untracked.PSet(
		SelectEvents = cms.vstring('SemiLepPath' )
	),
	outputCommands = cms.untracked.vstring('keep *')#,'keep *_genParticles_*_*','keep *_MyTTbarGenEventProd_*_*')
)
process.output_SemiLep_Path = cms.EndPath(process.output_SemiLep)
#process.output_DiLep = cms.OutputModule("PoolOutputModule",
#                                  fileName = cms.untracked.string('DiLepMc_Gen_selected.root'),
#                                  SelectEvents = cms.untracked.PSet(
#                SelectEvents = cms.vstring('DiLepPath' )
#        ),
#        outputCommands = cms.untracked.vstring('drop *','keep *_genParticles_*_*','keep *_MyTTbarGenEventProd_*_*')
#)
#process.output_DiLep_Path = cms.EndPath(process.output_DiLep)
#process.schedule cms.Schedule(process.SemiLepPath , process.DiLepPath , process.output_SemiLep_Path , process.output_DiLep_Path)

print "source ",process.source.fileNames
print "output ",process.output_SemiLep.fileName #, " and " , process.output_DiLep.fileName
