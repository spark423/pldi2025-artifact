#!/bin/bash

mkdir -p results
rm results/*log10f*.txt
rm results/glibc_double_log10.txt
touch results/rlibm_log10f.txt
touch results/rlibm_log10f_rz.txt
touch results/rlibm_log10f_og.txt
touch results/core_math_log10f.txt
touch results/glibc_double_log10.txt
echo -e "|  log10(x)  |"
./rlibm/log10f results/rlibm_log10f.txt
./rlibm/log10f_rz results/rlibm_log10f_rz.txt
./rlibm/log10f_og results/rlibm_log10f_og.txt
./core-math/cr_log10f results/core_math_log10f.txt
./glibc/log10 results/glibc_double_log10.txt
