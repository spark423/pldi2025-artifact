#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st polynomial for log10."
./Log10-RI-Inputs ../intervals/log10_ri_inputs_p1_uq ../polynomials/log10_ri_inputs_p1 20
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd polynomial for log10."
./Log10-RI-Inputs ../intervals/log10_ri_inputs_p2_uq ../polynomials/log10_ri_inputs_p2 20
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log10."


