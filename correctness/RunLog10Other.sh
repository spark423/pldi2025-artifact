#!/bin/bash
touch results/mlib/core_math_log10f.txt
touch results/mlib/glibc_double_log10.txt
echo -e "|  log10(x)  |"
./core-math/log10f results/mlib/core_math_log10f.txt
./glibc/log10 results/mlib/glibc_double_log10.txt
