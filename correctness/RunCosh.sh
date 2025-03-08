#!/bin/bash

mkdir -p results
rm results/*coshf*.txt
rm results/glibc_double_cos.txt
touch results/rlibm_coshf.txt
touch results/rlibm_coshf_rz.txt
touch results/rlibm_coshf_og.txt
touch results/core_math_coshf.txt
touch results/glibc_double_cosh.txt
echo -e "|  cosh(x)  |"
./rlibm/coshf results/rlibm_coshf.txt
./rlibm/coshf_rz results/rlibm_coshf_rz.txt
./rlibm/coshf_og results/rlibm_coshf_og.txt
./core-math/cr_coshf results/core_math_coshf.txt
./glibc/cosh results/glibc_double_cosh.txt
