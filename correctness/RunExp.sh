#!/bin/bash
touch results/ourlibm_expf.txt
touch results/ourlibm_expf_rz.txt
touch results/rlibm_expf.txt
touch results/rlibm_expf_rne.txt
touch results/core_math_expf.txt
touch results/glibc_double_exp.txt
echo -e "|  exp(x)  |"
./ourlibm/expf results/ourlibm_expf.txt
./ourlibm/expf_rz results/ourlibm_expf_rz.txt
./rlibm/expf results/rlibm_expf.txt
./rlibm/expf_rne results/rlibm_expf_rne.txt
./core-math/expf results/core_math_expf.txt
./glibc/exp results/glibc_double_exp.txt
