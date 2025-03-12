#!/bin/bash
touch results/ourlibm_sinhf.txt
touch results/ourlibm_sinhf_rz.txt
touch results/rlibm_sinhf.txt
touch results/rlibm_sinhf_rne.txt
touch results/core_math_sinhf.txt
touch results/glibc_double_sinh.txt
echo -e "|  sinh(x)  |"
./ourlibm/sinhf results/ourlibm_sinhf.txt
./ourlibm/sinhf_rz results/ourlibm_sinhf_rz.txt
./rlibm/sinhf results/rlibm_sinhf.txt
./rlibm/sinhf_rne results/rlibm_sinhf_rne.txt
./core-math/sinhf results/core_math_sinhf.txt
./glibc/sinh results/glibc_double_sinh.txt
