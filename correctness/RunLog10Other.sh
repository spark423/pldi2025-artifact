#!/bin/bash
touch results/core_math_log10f.txt
touch results/glibc_double_log10.txt
echo -e "|  log10(x)  |"
./core-math/log10f results/core_math_log10f.txt
./glibc/log10 results/glibc_double_log10.txt
