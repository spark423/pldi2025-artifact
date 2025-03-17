#!/bin/bash
cd ../
mkdir -p oracles
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for sinh. Estimated time: approximately 90 mins."
./Sinh ../oracles/Sinh34RNOOracle
echo -e "Oracle generation complete."

