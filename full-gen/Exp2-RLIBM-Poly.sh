#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for exp2."
./Exp2-RLIBM ../intervals/exp2_rlibm_uq ../polynomials/exp2_rlibm 0 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for exp2."


