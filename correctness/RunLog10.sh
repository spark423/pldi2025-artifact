#!/bin/bash
touch results/ourlibm_log10f.txt
touch results/ourlibm_log10f_rz.txt
touch results/rlibm_log10f.txt
touch results/rlibm_log10f_rne.txt
touch results/core_math_log10f.txt
touch results/glibc_double_log10.txt
echo -e "|  log10(x)  |"
./ourlibm/log10f results/ourlibm_log10f.txt
./ourlibm/log10f_rz results/ourlibm_log10f_rz.txt
./rlibm/log10f results/rlibm_log10f.txt
./rlibm/log10f_rne results/rlibm_log10f_rne.txt
./core-math/log10f results/core_math_log10f.txt
./glibc/log10 results/glibc_double_log10.txt
