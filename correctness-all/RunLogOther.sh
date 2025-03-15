#!/bin/bash
touch results/mlib/core_math_logf.txt
touch results/mlib/glibc_double_log.txt
echo -e "|  log(x)  |"
./core-math/logf results/mlib/core_math_logf.txt
./glibc/log results/mlib/glibc_double_log.txt
