#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st small case polynomial for cos."
./CosSmall-RI-Inputs ../intervals/sin_small_p1 ../polynomials/cos_small_ri_inputs_p1 0
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd small case polynomial for cos."
./Cos-RI-Inputs ../intervals/cos_small_p2 ../polynomials/cos_small_ri_inputs_p2 0
echo -e "Polynomial generation complete."
echo -e "Generating the 1st cos polynomial for cos."
./Cos-RI-Inputs ../intervals/coscos_ri_inputs_p1_uq ../polynomials/coscos_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for cos."
./Sin-RI-Inputs ../intervals/cossin_ri_inputs_p1_uq ../polynomials/cossin_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd cos polynomial for cos."
./Cos-RI-Inputs ../intervals/coscos_ri_inputs_p2_uq ../polynomials/coscos_ri_inputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd sin polynomial for cos."
./Sin-RI-Inputs ../intervals/cossin_ri_inputs_p2_uq ../polynomials/cossin_ri_inputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cos."


