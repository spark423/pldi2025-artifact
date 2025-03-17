#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st small case polynomial for sin."
./SinSmall-RLIBM ../intervals/sin_small_p1 ../polynomials/sin_small_rlibm_p1 0
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd small case polynomial for sin."
./Sin-RLIBM ../intervals/sin_small_p2 ../polynomials/sin_small_rlibm_p2 0
echo -e "Polynomial generation complete."
echo -e "Generating the 1st cos polynomial for sin."
./Cos-RLIBM ../intervals/sincos_rlibm_p1_uq ../polynomials/sincos_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for sin."
./Sin-RLIBM ../intervals/sinsin_rlibm_p1_uq ../polynomials/sinsin_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd cos polynomial for sin."
./Cos-RLIBM ../intervals/sincos_rlibm_p2_uq ../polynomials/sincos_rlibm_p2 10
echo -e "Polynomial generation complete."
echo -e "Generating the 2nd sin polynomial for sin."
./Sin-RLIBM ../intervals/sinsin_rlibm_p2_uq ../polynomials/sinsin_rlibm_p2 10
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sin."


