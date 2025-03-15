#!/bin/bash
touch results/mlib/core_math_sinhf.txt
touch results/mlib/glibc_double_sinh.txt
echo -e "|  sinh(x)  |"
./core-math/sinhf results/mlib/core_math_sinhf.txt
./glibc/sinh results/mlib/glibc_double_sinh.txt
