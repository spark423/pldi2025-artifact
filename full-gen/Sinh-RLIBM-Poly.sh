#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for sinh."
./Cos-RLIBM ../intervals/sinhcos_rlibm_uq ../polynomials/sinhcos_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for sinh."
./Sin-RLIBM ../intervals/sinhsin_rlibm_uq ../polynomials/sinhsin_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinh."


