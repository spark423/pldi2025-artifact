#!/bin/bash

mkdir -p results
rm results/*expf*.txt
rm results/glibc_double_exp.txt
touch results/rlibm_expf.txt
touch results/rlibm_expf_rz.txt
touch results/rlibm_expf_og.txt
touch results/core_math_expf.txt
touch results/glibc_double_exp.txt
echo -e "|  exp(x)  |"
./rlibm/expf results/rlibm_expf.txt
./rlibm/expf_rz results/rlibm_expf_rz.txt
./rlibm/expf_og results/rlibm_expf_og.txt
./core-math/cr_expf results/core_math_expf.txt
./glibc/exp results/glibc_double_exp.txt
