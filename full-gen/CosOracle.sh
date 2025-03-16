#!/bin/bash
cd ../
mkdir -p oracles
touch Cos34RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for cos. Estimated time: approximately 90 mins."
./Cos ../oracles/Cos34RNOOracle
echo -e "Oracle generation complete."

