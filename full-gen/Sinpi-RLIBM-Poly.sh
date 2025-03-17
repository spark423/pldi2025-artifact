#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for sinpi."
./Cos-RLIBM ../intervals/sinpicos_rlibm_uq ../polynomials/sinpicos_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for sinpi."
./Sin-RLIBM ../intervals/sinpisin_rlibm_uq ../polynomials/sinpisin_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for sinpi."


