#!/bin/bash

mkdir -p results
rm results/*sinf*.txt
rm results/glibc_double_sin.txt
touch results/rlibm_sinf.txt
touch results/rlibm_sinf_rz.txt
touch results/rlibm_sinf_og.txt
touch results/core_math_sinf.txt
touch results/glibc_double_sin.txt
echo -e "|  sin(x)  |"
./rlibm/sinf results/rlibm_sinf.txt
./rlibm/sinf_rz results/rlibm_sinf_rz.txt
./rlibm/sinf_og results/rlibm_sinf_og.txt
./core-math/cr_sinf results/core_math_sinf.txt
./glibc/sin results/glibc_double_sin.txt
