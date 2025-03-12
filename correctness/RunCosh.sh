#!/bin/bash
touch results/ourlibm_coshf.txt
touch results/ourlibm_coshf_rz.txt
touch results/rlibm_coshf.txt
touch results/rlibm_coshf_rne.txt
touch results/core_math_coshf.txt
touch results/glibc_double_cosh.txt
echo -e "|  cosh(x)  |"
./ourlibm/coshf results/ourlibm_coshf.txt
./ourlibm/coshf_rz results/ourlibm_coshf_rz.txt
./rlibm/coshf results/rlibm_coshf.txt
./rlibm/coshf_rne results/rlibm_coshf_rne.txt
./core-math/coshf results/core_math_coshf.txt
./glibc/cosh results/glibc_double_cosh.txt
