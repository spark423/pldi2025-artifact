#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for log10."
./Log10-RLIBM ../intervals/log10_rlibm_uq ../polynomials/log10_rlibm 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log10."


