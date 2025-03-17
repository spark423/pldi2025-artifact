#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for sinh."
./Cos-RI-Outputs ../intervals/sinhcos_ri_outputs_uq ../polynomials/sinhcos_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for sinh."
./Sin-RI-Outputs ../intervals/sinhsin_ri_outputs_uq ../polynomials/sinhsin_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinh."


