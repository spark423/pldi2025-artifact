#!/bin/bash

mkdir -p results
rm results/*sinhf*.txt
rm results/glibc_double_sinh.txt
touch results/rlibm_sinhf.txt
touch results/rlibm_sinhf_rz.txt
touch results/rlibm_sinhf_og.txt
touch results/core_math_sinhf.txt
touch results/glibc_double_sinh.txt
echo -e "|  sinh(x)  |"
./rlibm/sinhf results/rlibm_sinhf.txt
./rlibm/sinhf_rz results/rlibm_sinhf_rz.txt
./rlibm/sinhf_og results/rlibm_sinhf_og.txt
./core-math/cr_sinhf results/core_math_sinhf.txt
./glibc/sinh results/glibc_double_sinh.txt
