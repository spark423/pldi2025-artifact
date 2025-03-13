#!/bin/bash
touch results/core_math_sinhf.txt
touch results/glibc_double_sinh.txt
echo -e "|  sinh(x)  |"
./core-math/sinhf results/core_math_sinhf.txt
./glibc/sinh results/glibc_double_sinh.txt
