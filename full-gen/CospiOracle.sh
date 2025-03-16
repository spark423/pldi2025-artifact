#!/bin/bash
cd ../
mkdir -p oracles
touch Cospi34RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for cospi. Estimated time: approximately 90 mins."
./Cospi ../oracles/Cospi34RNOOracle
echo -e "Oracle generation complete."

