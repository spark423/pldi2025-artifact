#!/bin/bash
touch results/core_math_coshf.txt
touch results/glibc_double_cosh.txt
echo -e "|  cosh(x)  |"
./core-math/coshf results/core_math_coshf.txt
./glibc/cosh results/glibc_double_cosh.txt
