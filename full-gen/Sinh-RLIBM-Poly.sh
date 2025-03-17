#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st cos polynomial for sinh."
./Cos-RLIBM ../intervals/sinhcos_rlibm_p1_uq ../polynomials/sinhcos_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for sinh."
./Sin-RLIBM ../intervals/sinhsin_rlibm_p1_uq ../polynomials/sinhsin_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinh."


