#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the 1st cos polynomial for sinpi."
./Cos-RLIBM ../intervals/sinpicos_rlibm_p1_uq ../polynomials/sinpicos_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Generating the 1st sin polynomial for sinpi."
./Sin-RLIBM ../intervals/sinpisin_rlibm_p1_uq ../polynomials/sinpisin_rlibm_p1 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinpi."


