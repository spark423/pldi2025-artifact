#!/bin/bash
cd ../
mkdir -p oracles
touch Exp34RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for exp. Estimated time: approximately 90 mins."
./Exp ../oracles/Exp34RNOOracle
echo -e "Oracle generation complete."

