#!/bin/bash
touch results/core_math_log2f.txt
touch results/glibc_double_log2.txt
echo -e "|  log2(x)  |"
./core-math/log2f results/core_math_log2f.txt
./glibc/log2 results/glibc_double_log2.txt
