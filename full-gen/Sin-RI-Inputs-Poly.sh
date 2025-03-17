#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st small case polynomial for sin."
./SinSmall-RI-Inputs ../intervals/sin_small_p1 ../polynomials/sin_small_ri_inputs_p1 0
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd small case polynomial for sin."
./Sin-RI-Inputs ../intervals/sin_small_p2 ../polynomials/sin_small_ri_inputs_p2 0
echo -e "Polynomial generation complete."
echo -e "Generating the 1st cos polynomial for sin."
./Cos-RI-Inputs ../intervals/sincos_ri_inputs_p1_uq ../polynomials/sincos_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for sin."
./Sin-RI-Inputs ../intervals/sinsin_ri_inputs_p1_uq ../polynomials/sinsin_ri_inputs_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd cos polynomial for sin."
./Cos-RI-Inputs ../intervals/sincos_ri_inputs_p2_uq ../polynomials/sincos_ri_inputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd sin polynomial for sin."
./Sin-RI-Inputs ../intervals/sinsin_ri_inputs_p2_uq ../polynomials/sinsin_ri_inputs_p2 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sin."


