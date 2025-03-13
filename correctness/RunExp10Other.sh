#!/bin/bash
touch results/core_math_exp10f.txt
touch results/glibc_double_exp10.txt
echo -e "|  exp10(x)  |"
./core-math/exp10f results/core_math_exp10f.txt
./glibc/exp10 results/glibc_double_exp10.txt
