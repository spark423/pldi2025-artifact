#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for log2."
./Log2-RLIBM ../intervals/log2_rlibm_uq ../polynomials/log2_rlibm 0 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log2."


