#!/bin/bash
touch results/core_math_expf.txt
touch results/glibc_double_exp.txt
echo -e "|  exp(x)  |"
./core-math/expf results/core_math_expf.txt
./glibc/exp results/glibc_double_exp.txt
