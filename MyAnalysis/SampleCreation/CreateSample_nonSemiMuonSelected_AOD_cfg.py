import sys
import os.path
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_BASE','MyAnalysis/SelectionAnalysis'))))
sys.path.append(os.path.abspath(os.path.expandvars(os.path.join('$CMSSW_RELEASE_BASE','MyAnalysis/SelectionAnalysis'))))
### ------------------------- ###

from CreateSample_SemiMuonSelected_AOD_cfg import *

### Generated by ConfigEditor ###
if hasattr(process,'resetHistory'): process.resetHistory()
### ------------------------- ###
process.setName_('AddCollection2SelectedEvents')

process.SemiLepPath.replace(process.SemiLepMcFilter,~process.SemiLepMcFilter)
process.output_SemiLep.fileName='SemiLepMc_mcatnlo_AOD_NonSemiMu_selected.root'
