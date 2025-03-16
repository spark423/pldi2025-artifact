#!/bin/bash
cd ../
mkdir -p oracles
touch Log234RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for log2. Estimated time: approximately 90 mins."
./Log2 ../oracles/Log234RNOOracle
echo -e "Oracle generation complete."

