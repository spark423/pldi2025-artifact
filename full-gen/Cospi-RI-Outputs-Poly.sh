#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for cospi."
./Cos-RI-Outputs ../intervals/cospicos_ri_outputs_uq ../polynomials/cospicos_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for cospi."
./Sin-RI-Outputs ../intervals/cospisin_ri_outputs_uq ../polynomials/cospisin_ri_inputs 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cospi."


