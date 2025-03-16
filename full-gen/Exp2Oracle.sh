#!/bin/bash
cd ../
mkdir -p oracles
touch Exp234RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for exp2. Estimated time: approximately 90 mins."
./Exp2 ../oracles/Exp234RNOOracle
echo -e "Oracle generation complete."

