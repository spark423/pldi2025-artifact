#!/bin/bash
cd ../
mkdir -p polynomials
cd helper/polynomial-gen
make -s
cd ../../polynomial-gen
make -s
echo -e "Generating the cos polynomial for cospi."
./Cos-RLIBM ../intervals/cospicos_rlibm_uq ../polynomials/cospicos_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Generating the sin polynomial for cospi."
./Sin-RLIBM ../intervals/cospisin_rlibm_uq ../polynomials/cospisin_rlibm 5
echo -e "Polynomial generation complete."
echo -e "Finished generating all polynomials for cospi."


