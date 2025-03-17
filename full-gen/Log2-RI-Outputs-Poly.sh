#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for log2."
./Log2-RI-Outputs ../intervals/log2_ri_outputs_uq ../polynomials/log2_ri_outputs 0 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log2."


