#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st small case polynomial for cos."
./CosSmall-RI-Outputs ../intervals/cos_small_p1 ../polynomials/cos_small_ri_outputs_p1 0
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd small case polynomial for cos."
./Cos-RI-Outputs ../intervals/cos_small_p2 ../polynomials/cos_small_ri_outputs_p2 0
echo -e "Polynomial generation complete."
echo -e "Generating the 1st cos polynomial for cos."
./Cos-RI-Outputs ../intervals/coscos_ri_outputs_p1_uq ../polynomials/coscos_ri_outputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for cos."
./Sin-RI-Outputs ../intervals/cossin_ri_outputs_p1_uq ../polynomials/cossin_ri_outputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd cos polynomial for cos."
./Cos-RI-Outputs ../intervals/coscos_ri_outputs_p2_uq ../polynomials/coscos_ri_outputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd sin polynomial for cos."
./Sin-RI-Outputs ../intervals/cossin_ri_outputs_p2_uq ../polynomials/cossin_ri_outputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cos."


