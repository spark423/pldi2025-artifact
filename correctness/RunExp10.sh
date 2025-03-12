#!/bin/bash
touch results/ourlibm_exp10f.txt
touch results/ourlibm_exp10f_rz.txt
touch results/rlibm_exp10f.txt
touch results/rlibm_exp10f_rne.txt
touch results/core_math_exp10f.txt
touch results/glibc_double_exp10.txt
echo -e "|  exp10(x)  |"
./ourlibm/exp10f results/ourlibm_exp10f.txt
./ourlibm/exp10f_rz results/ourlibm_exp10f_rz.txt
./rlibm/exp10f results/rlibm_exp10f.txt
./rlibm/exp10f_rne results/rlibm_exp10f_rne.txt
./core-math/exp10f results/core_math_exp10f.txt
./glibc/exp10 results/glibc_double_exp10.txt
