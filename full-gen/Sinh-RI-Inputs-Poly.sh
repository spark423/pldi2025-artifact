#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st cos polynomial for sinh."
./Cos-RI-Inputs ../intervals/sinhcos_ri_inputs_p1_uq ../polynomials/sinhcos_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for sinh."
./Sin-RI-Inputs ../intervals/sinhsin_ri_inputs_p1_uq ../polynomials/sinhsin_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinh."


