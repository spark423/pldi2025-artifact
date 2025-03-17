#!/bin/bash
cd ../
mkdir -p oracles
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for cosh. Estimated time: approximately 90 mins."
./Cosh ../oracles/Cosh34RNOOracle
echo -e "Oracle generation complete."

