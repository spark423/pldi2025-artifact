#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for exp2."
./Exp2-RI-Outputs ../intervals/exp2_ri_outputs_uq ../polynomials/exp2_ri_outputs 3 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for exp2."


