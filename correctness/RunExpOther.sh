#!/bin/bash
touch results/mlib/core_math_expf.txt
touch results/mlib/glibc_double_exp.txt
echo -e "|  exp(x)  |"
./core-math/expf results/mlib/core_math_expf.txt
./glibc/exp results/mlib/glibc_double_exp.txt
