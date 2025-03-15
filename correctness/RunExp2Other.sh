#!/bin/bash
touch results/mlib/core_math_exp2f.txt
touch results/mlib/glibc_double_exp2.txt
echo -e "|  exp2(x)  |"
./core-math/exp2f results/mlib/core_math_exp2f.txt
./glibc/exp2 results/mlib/glibc_double_exp2.txt
