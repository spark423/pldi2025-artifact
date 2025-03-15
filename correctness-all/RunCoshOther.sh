#!/bin/bash
touch results/mlib/core_math_coshf.txt
touch results/mlib/glibc_double_cosh.txt
echo -e "|  cosh(x)  |"
./core-math/coshf results/mlib/core_math_coshf.txt
./glibc/cosh results/mlib/glibc_double_cosh.txt
