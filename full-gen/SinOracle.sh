#!/bin/bash
cd ../
mkdir -p oracles
touch Sin34RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for sin. Estimated time: approximately 90 mins."
./Sin ../oracles/Sin34RNOOracle
echo -e "Oracle generation complete."

