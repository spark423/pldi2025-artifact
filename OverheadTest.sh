#!/bin/bash
cd overhead/
./CleanTest.sh
./BuildTest.sh
./RunTest.sh
cd ../
python3 SpeedupRIInputBoundsOverRLIBM.py
python3 SpeedupRIOutputsOverRLIBM.py 
