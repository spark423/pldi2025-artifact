#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st polynomial for log."
./Log-RI-Outputs ../intervals/log_ri_outputs_p1_uq ../polynomials/log_ri_outputs_p1 20
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd polynomial for log."
./Log-RI-Outputs ../intervals/log_ri_outputs_p2_uq ../polynomials/log_ri_outputs_p2 20
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for log."


