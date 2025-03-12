#!/bin/bash
touch results/ourlibm_logf.txt
touch results/ourlibm_logf_rz.txt
touch results/rlibm_logf.txt
touch results/rlibm_logf_rne.txt
touch results/core_math_logf.txt
touch results/glibc_double_log.txt
echo -e "|  log(x)  |"
./ourlibm/logf results/ourlibm_logf.txt
./ourlibm/logf_rz results/ourlibm_logf_rz.txt
./rlibm/logf results/rlibm_logf.txt
./rlibm/logf_rne results/rlibm_logf_rne.txt
./core-math/logf results/core_math_logf.txt
./glibc/log results/glibc_double_log.txt
