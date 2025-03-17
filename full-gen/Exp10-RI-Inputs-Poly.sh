#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the polynomial for exp10."
./Exp10-RI-Inputs ../intervals/exp10_ri_inputs_uq ../polynomials/exp10_ri_inputs 12 
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for exp10."


