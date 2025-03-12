#!/bin/bash
touch results/ourlibm_exp2f.txt
touch results/ourlibm_exp2f_rz.txt
touch results/rlibm_exp2f.txt
touch results/rlibm_exp2f_rne.txt
touch results/core_math_exp2f.txt
touch results/glibc_double_exp2.txt
echo -e "|  exp2(x)  |"
./ourlibm/exp2f results/ourlibm_exp2f.txt
./ourlibm/exp2f_rz results/ourlibm_exp2f_rz.txt
./rlibm/exp2f results/rlibm_exp2f.txt
./rlibm/exp2f_rne results/rlibm_exp2f_rne.txt
./core-math/exp2f results/core_math_exp2f.txt
./glibc/exp2 results/glibc_double_exp2.txt
