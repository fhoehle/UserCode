import FWCore.ParameterSet.Config as cms
#import sys
#from FWCore.ParameterSet.VarParsing import VarParsing

#process = cms.Process( 'Selection' )

from topMuRefSel_cff import path as testpath
process=testpath(False)
process.p.remove(process.MyTTbarGenEventProd)
process.p.remove(process.SemiLepMcFilter)
#process.p.remov(process.)
process.setName_('testname')
#import FWCore.ParameterSet.Config as cms
#import sys
from FWCore.ParameterSet.VarParsing import VarParsing
#from topMuRefSel_cff import path 
#process=path(cms.bool(True))
#
#process = cms.Process( 'Selection' )
options = VarParsing ('analysis')
options.parseArguments()
process.source.fileNames = cms.untracked.vstring('/store/data/Run2011A/SingleMu/AOD/08Nov2011-v1/0001/441EEB69-FE0C-E111-96C8-78E7D1E4B6E8.root')
if options.inputFiles != cms.untracked.vstring():
 process.source.fileNames=options.inputFiles
# maximum number of events
process.maxEvents.input =  -1 # reduce for testing
if options.maxEvents != '':
 process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))
if options.outputFile != None:
 process.out.fileName=options.outputFile
#
process.out.outputCommands = ['keep *']#,'drop *_*_*_MyPAT','keep *_TriggerResults_*_MyPAT']
##### checking basics
print "inputs: ",process.source.fileNames
print "output: ",process.out.fileName
print "commands ",process.out.outputCommands
print "selection ",process.out.SelectEvents.SelectEvents

