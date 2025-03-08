#!/bin/bash

mkdir -p results
rm results/*exp2f*.txt
rm results/glibc_double_exp2.txt
touch results/rlibm_exp2f.txt
touch results/rlibm_exp2f_rz.txt
touch results/rlibm_exp2f_og.txt
touch results/core_math_exp2f.txt
touch results/glibc_double_exp2.txt
echo -e "|  exp2(x)  |"
./rlibm/exp2f results/rlibm_exp2f.txt
./rlibm/exp2f_rz results/rlibm_exp2f_rz.txt
./rlibm/exp2f_og results/rlibm_exp2f_og.txt
./core-math/cr_exp2f results/core_math_exp2f.txt
./glibc/exp2 results/glibc_double_exp2.txt
