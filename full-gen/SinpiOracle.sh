#!/bin/bash
cd ../
mkdir -p oracles
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for sinpi. Estimated time: approximately 90 mins."
./Sinpi ../oracles/Sinpi34RNOOracle
echo -e "Oracle generation complete."

