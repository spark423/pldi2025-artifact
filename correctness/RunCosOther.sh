#!/bin/bash
touch results/mlib/core_math_cosf.txt
touch results/mlib/glibc_double_cos.txt
echo -e "|  cos(x)  |"
./core-math/cosf results/mlib/core_math_cosf.txt
./glibc/cos results/mlib/glibc_double_cos.txt
