#!/bin/bash
touch results/mlib/core_math_log2f.txt
touch results/mlib/glibc_double_log2.txt
echo -e "|  log2(x)  |"
./core-math/log2f results/mlib/core_math_log2f.txt
./glibc/log2 results/mlib/glibc_double_log2.txt
