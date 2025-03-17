#!/bin/bash
cd ../
mkdir -p oracles
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for log10. Estimated time: approximately 90 mins."
./Log10 ../oracles/Log1034NOOracle
echo -e "Oracle generation complete."

