#!/bin/bash
touch results/ourlibm_cosf.txt
touch results/ourlibm_cosf_rz.txt
touch results/rlibm_cosf.txt
touch results/rlibm_cosf_rne.txt
touch results/core_math_cosf.txt
touch results/glibc_double_cos.txt
echo -e "|  cos(x)  |"
./ourlibm/cosf results/ourlibm_cosf.txt
./ourlibm/cosf_rz results/ourlibm_cosf_rz.txt
./rlibm/cosf results/rlibm_cosf.txt
./rlibm/cosf_rne results/rlibm_cosf_rne.txt
./core-math/cosf results/core_math_cosf.txt
./glibc/cos results/glibc_double_cos.txt
