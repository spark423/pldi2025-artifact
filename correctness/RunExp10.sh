#!/bin/bash

mkdir -p results
rm results/*exp10f*.txt
rm results/glibc_double_exp10.txt
touch results/rlibm_exp10f.txt
touch results/rlibm_exp10f_rz.txt
touch results/rlibm_exp10f_og.txt
touch results/core_math_exp10f.txt
touch results/glibc_double_exp10.txt
echo -e "|  exp10(x)  |"
./rlibm/exp10f results/rlibm_exp10f.txt
./rlibm/exp10f_rz results/rlibm_exp10f_rz.txt
./rlibm/exp10f_og results/rlibm_exp10f_og.txt
./core-math/cr_exp10f results/core_math_exp10f.txt
./glibc/exp10 results/glibc_double_exp10.txt
