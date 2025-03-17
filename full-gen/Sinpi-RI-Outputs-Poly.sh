#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for sinpi."
./Cos-RI-Outputs ../intervals/sinpicos_ri_outputs_uq ../polynomials/sinpicos_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for sinpi."
./Sin-RI-Outputs ../intervals/sinpisin_ri_outputs_uq ../polynomials/sinpisin_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinpi."


