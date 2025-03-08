#!/bin/bash

mkdir -p results
rm results/*sinpif*.txt
rm results/glibc_double_sinpi.txt
touch results/rlibm_sinpif.txt
touch results/rlibm_sinpif_rz.txt
touch results/rlibm_sinpif_og.txt
touch results/core_math_sinpif.txt
touch results/glibc_double_sinpi.txt
echo -e "|  sinpi(x)  |"
./rlibm/sinpif results/rlibm_sinpif.txt
./rlibm/sinpif_rz results/rlibm_sinpif_rz.txt
./rlibm/sinpif_og results/rlibm_sinpif_og.txt
./core-math/cr_sinpif results/core_math_sinpif.txt
./glibc/sinpi results/glibc_double_sinpi.txt
