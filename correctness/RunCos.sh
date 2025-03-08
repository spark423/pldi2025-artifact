#!/bin/bash

mkdir -p results
rm results/*cosf*.txt
rm results/glibc_double_cos.txt
touch results/rlibm_cosf.txt
touch results/rlibm_cosf_rz.txt
touch results/rlibm_cosf_og.txt
touch results/core_math_cosf.txt
touch results/glibc_double_cos.txt
echo -e "|  cos(x)  |"
./rlibm/cosf results/rlibm_cosf.txt
./rlibm/cosf_rz results/rlibm_cosf_rz.txt
./rlibm/cosf_og results/rlibm_cosf_og.txt
./core-math/cr_cosf results/core_math_cosf.txt
./glibc/cos results/glibc_double_cos.txt
