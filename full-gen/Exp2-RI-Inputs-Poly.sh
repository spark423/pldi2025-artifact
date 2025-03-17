#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for exp2."
./Exp2-RI-Inputs ../intervals/exp2_ri_inputs_uq ../polynomials/exp2_ri_inputs 5 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for exp2."


