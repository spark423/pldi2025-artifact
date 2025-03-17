#!/bin/bash
cd ../
mkdir -p oracles
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for log. Estimated time: approximately 90 mins."
./Log ../oracles/Log34RNOOracle
echo -e "Oracle generation complete."

