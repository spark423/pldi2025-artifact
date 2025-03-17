#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for cosh."
./Cos-RLIBM ../intervals/coshcos_rlibm_uq ../polynomials/coshcos_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for cosh."
./Sin-RLIBM ../intervals/coshsin_rlibm_uq ../polynomials/coshsin_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cosh."


