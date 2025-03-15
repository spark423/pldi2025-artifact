#!/bin/bash
touch results/mlib/core_math_exp10f.txt
touch results/mlib/glibc_double_exp10.txt
echo -e "|  exp10(x)  |"
./core-math/exp10f results/mlib/core_math_exp10f.txt
./glibc/exp10 results/mlib/glibc_double_exp10.txt
