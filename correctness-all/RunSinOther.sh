#!/bin/bash
touch results/mlib/core_math_sinf.txt
touch results/mlib/glibc_double_sin.txt
echo -e "|  sin(x)  |"
./core-math/sinf results/mlib/core_math_sinf.txt
./glibc/sin results/mlib/glibc_double_sin.txt
