#!/bin/bash
touch results/ourlibm_sinf.txt
touch results/ourlibm_sinf_rz.txt
touch results/rlibm_sinf.txt
touch results/rlibm_sinf_rne.txt
touch results/core_math_sinf.txt
touch results/glibc_double_sin.txt
echo -e "|  sin(x)  |"
./ourlibm/sinf results/ourlibm_sinf.txt
./ourlibm/sinf_rz results/ourlibm_sinf_rz.txt
./rlibm/sinf results/rlibm_sinf.txt
./rlibm/sinf_rne results/rlibm_sinf_rne.txt
./core-math/sinf results/core_math_sinf.txt
./glibc/sin results/glibc_double_sin.txt
