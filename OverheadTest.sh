#!/bin/bash
cd overhead/
./CleanTest.sh
./BuildTest.sh
./RunTest.sh
python3 SpeedupRIInputBoundsOverRLIBM.py
python3 SpeedupRIOutputsOverRLIBM.py 
