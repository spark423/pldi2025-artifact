#!/bin/bash

mkdir -p results
rm results/*logf*.txt
rm results/glibc_double_log.txt
touch results/rlibm_logf.txt
touch results/rlibm_logf_rz.txt
touch results/rlibm_logf_og.txt
touch results/core_math_logf.txt
touch results/glibc_double_log.txt
echo -e "|  log(x)  |"
./rlibm/logf results/rlibm_logf.txt
./rlibm/logf_rz results/rlibm_logf_rz.txt
./rlibm/logf_og results/rlibm_logf_og.txt
./core-math/cr_logf results/core_math_logf.txt
./glibc/log results/glibc_double_log.txt
