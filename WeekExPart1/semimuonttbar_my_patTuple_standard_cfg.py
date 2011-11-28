## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *
## ------------------------------------------------------
#  NOTE: you can use a bunch of core tools of PAT to
#  taylor your PAT configuration; for a few examples
#  uncomment the lines below
## ------------------------------------------------------
from PhysicsTools.PatAlgos.tools.coreTools import *

## remove MC matching from the default sequence
# removeMCMatching(process, ['Muons'])
# runOnData(process)

## remove certain objects from the default sequence
# removeAllPATObjectsBut(process, ['Muons'])
# removeSpecificPATObjects(process, ['Electrons', 'Muons', 'Taus'])
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 50

process.selectedPatMuons.cut = cms.string('pt > 20 & eta < 2.1')
process.countPatMuons.maxNumber = cms.uint32(999999)
process.countPatMuons.minNumber  = cms.uint32(1)
process.selectedPatJets.cut = cms.string('pt > 30 & eta < 2.4')
process.countPatJets.minNumber  = cms.uint32(4)
##let it run
#from RecoJets.Configuration.RecoPFJets_cff import kt6PFJets
#process.kt6PFJets = kt6PFJets

process.p = cms.Path(
    process.patDefaultSequence
    )

## ------------------------------------------------------
#  In addition you usually want to change the following
#  parameters:
## ------------------------------------------------------
#
#   process.GlobalTag.globaltag =  ...    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
#                                         ##
process.source.fileNames = [          ##
 'rfio:/castor/cern.ch/user/f/fhohle/ttbar442/semiMuonic_ttbarSkim.root'#	'/user/f/fhohle/nonsemiMuonic_ttbarSkim.root'
]                                     ##  (e.g. 'file:AOD.root')
##
process.maxEvents.input = -1         ##  (e.g. -1 to run on all events)
#                                         ##
process.out.outputCommands = [ 'drop *','keep *_cleanPatJets_*_*' ]  ##  (e.g. taken from PhysicsTools/PatAlgos/python/patEventContent_cff.py)
#                                         ##
process.out.dropMetaData = cms.untracked.string("DROPPED")

process.out.fileName = 'mypatTuple.root'            ##  (e.g. 'myTuple.root')
#                                         ##
process.options.wantSummary = True    ##  (to suppress the long output at the end of the job)    
