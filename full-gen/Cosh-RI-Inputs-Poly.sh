#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st cos polynomial for cosh."
./Cos-RI-Inputs ../intervals/coshcos_ri_inputs_p1_uq ../polynomials/coshcos_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for cosh."
./Sin-RI-Inputs ../intervals/coshsin_ri_inputs_p1_uq ../polynomials/coshsin_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cosh."


