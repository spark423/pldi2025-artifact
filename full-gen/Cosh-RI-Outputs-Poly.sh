#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for cosh."
./Cos-RI-Outputs ../intervals/coshcos_ri_outputs_uq ../polynomials/coshcos_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for cosh."
./Sin-RI-Outputs ../intervals/coshsin_ri_outputs_uq ../polynomials/coshsin_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cosh."


