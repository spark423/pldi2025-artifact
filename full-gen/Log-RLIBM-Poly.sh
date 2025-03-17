#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for log."
./Log-RLIBM ../intervals/log_rlibm_uq ../polynomials/log_rlibm 15
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log."


