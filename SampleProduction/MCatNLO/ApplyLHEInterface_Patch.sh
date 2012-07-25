#!/bin/bash
cd $CMSSW_BASE/src
cvs co -r V00-07-13 GeneratorInterface/LHEInterface
patch -p0 < ../SampleProduction/MCatNLO/LHEInterface_patch.txt
scram b -j 4

