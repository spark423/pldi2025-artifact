#!/bin/bash
touch results/core_math_sinf.txt
touch results/glibc_double_sin.txt
echo -e "|  sin(x)  |"
./core-math/sinf results/core_math_sinf.txt
./glibc/sin results/glibc_double_sin.txt
