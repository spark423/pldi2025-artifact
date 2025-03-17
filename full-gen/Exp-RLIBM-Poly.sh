#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st polynomial for exp."
./Exp-RLIBM ../intervals/exp_rlibm_p1_uq ../polynomials/exp_rlibm_p1 10
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd polynomial for exp."
./Exp-RLIBM ../intervals/exp_rlibm_p2_uq ../polynomials/exp_rlibm_p2 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for exp."


