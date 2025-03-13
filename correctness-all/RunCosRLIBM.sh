#!/bin/bash
touch results/rlibm_cosf.txt
touch results/rlibm_cosf_rne.txt
echo -e "|  cos(x)  |"
./core-math/cosf results/core_math_cosf.txt
./glibc/cos results/glibc_double_cos.txt
