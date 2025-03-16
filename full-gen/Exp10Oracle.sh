#!/bin/bash
cd ../
mkdir -p oracles
touch Exp1034RNOOracle
cd oracle-gen
make -s
echo -e "Generating the 34RNO oracle for exp10. Estimated time: approximately 90 mins."
./Exp10 ../oracles/Exp1034NOOracle
echo -e "Oracle generation complete."

