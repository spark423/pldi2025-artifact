#!/bin/bash

mkdir -p results
rm results/*cospif*.txt
rm results/glibc_double_cos.txt
touch results/rlibm_cospif.txt
touch results/rlibm_cospif_rz.txt
touch results/rlibm_cospif_og.txt
touch results/core_math_cospif.txt
touch results/glibc_double_cospi.txt
echo -e "|  cospi(x)  |"
./rlibm/cospif results/rlibm_cospif.txt
./rlibm/cospif_rz results/rlibm_cospif_rz.txt
./rlibm/cospif_og results/rlibm_cospif_og.txt
./core-math/cr_cospif results/core_math_cospif.txt
