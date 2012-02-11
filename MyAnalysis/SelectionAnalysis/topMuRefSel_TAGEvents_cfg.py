### Generated by ConfigEditor ###
import sys
import os.path
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_BASE','MyAnalysis/SelectionAnalysis/GridPreSelection/BackGround_WJets'))))
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_RELEASE_BASE','MyAnalysis/SelectionAnalysis'))))
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_BASE','src/MyUtilities/MyFunctions'))))
### ------------------------- ###

from topMuRefSel_cfg import *
process.setName_('SelectionTagEvents')
### Generated by ConfigEditor ###
if hasattr(process,'resetHistory'): process.resetHistory()
### ------------------------- ###
process.path_step5=cms.Path(process.prodSequence*process.step5)
process.path_step4c=cms.Path(process.prodSequence*process.step4c)
process.path_step4b=cms.Path(process.prodSequence*process.step4b)
process.path_step4a=cms.Path(process.prodSequence*process.step4a)
process.path_step3=cms.Path(process.prodSequence*process.step3)
process.path_step2=cms.Path(process.prodSequence*process.step2)
process.path_step1a=cms.Path(process.prodSequence*process.step1a)
process.path_step1b=cms.Path(process.prodSequence*process.step1b)
process.path_step0c=cms.Path(process.selectSignal*process.goodOfflinePrimaryVertices*process.step0c)
process.path_step0b=cms.Path(process.selectSignal*process.goodOfflinePrimaryVertices*process.step0b)
process.path_step0a=cms.Path(process.selectSignal*process.step0a)

process.out.outputCommands = cms.untracked.vstring('keep *','drop *_*_*_SelectionTagEvents','keep *_TriggerResults_*_SelectionTagEvents')
process.out.SelectEvents.SelectEvents += 'p'
process.out.fileName='topMuRefSel_TaggedEvents.root'

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()
if options.inputFiles != cms.untracked.vstring():
 process.source.fileNames=options.inputFiles
# maximum number of events
process.maxEvents.input =  -1 # reduce for testing
if options.maxEvents != '':
 process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
if options.outputFile != None:
 process.out.fileName=options.outputFile
#

