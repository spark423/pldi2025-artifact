#!/bin/bash
touch results/ourlibm_log2f.txt
touch results/ourlibm_log2f_rz.txt
touch results/rlibm_log2f_og.txt
touch results/core_math_log2f.txt
touch results/glibc_double_log2.txt
echo -e "|  log2(x)  |"
./ourlibm/log2f results/ourlibm_log2f.txt
./ourlibm/log2f_rz results/ourlibm_log2f_rz.txt
./rlibm/log2f results/rlibm_log2f.txt
./core-math/log2f results/core_math_log2f.txt
./glibc/log2 results/glibc_double_log2.txt
