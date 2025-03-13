#!/bin/bash
touch results/core_math_logf.txt
touch results/glibc_double_log.txt
echo -e "|  log(x)  |"
./core-math/logf results/core_math_logf.txt
./glibc/log results/glibc_double_log.txt
