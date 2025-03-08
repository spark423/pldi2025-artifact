#!/bin/bash

mkdir -p results
rm results/*log2f*.txt
rm results/glibc_double_log2.txt
touch results/rlibm_log2f.txt
touch results/rlibm_log2f_rz.txt
touch results/rlibm_log2f_og.txt
touch results/core_math_log2f.txt
touch results/glibc_double_log2.txt
echo -e "|  log2(x)  |"
./rlibm/log2f results/rlibm_log2f.txt
./rlibm/log2f_rz results/rlibm_log2f_rz.txt
./rlibm/log2f_og results/rlibm_log2f_og.txt
./core-math/cr_log2f results/core_math_log2f.txt
./glibc/log2 results/glibc_double_log2.txt
