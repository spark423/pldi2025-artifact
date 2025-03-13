#!/bin/bash
touch results/core_math_exp2f.txt
touch results/glibc_double_exp2.txt
echo -e "|  exp2(x)  |"
./core-math/exp2f results/core_math_exp2f.txt
./glibc/exp2 results/glibc_double_exp2.txt
