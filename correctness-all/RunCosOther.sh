#!/bin/bash
touch results/core_math_cosf.txt
touch results/glibc_double_cos.txt
echo -e "|  cos(x)  |"
./core-math/cosf results/core_math_cosf.txt
./glibc/cos results/glibc_double_cos.txt
