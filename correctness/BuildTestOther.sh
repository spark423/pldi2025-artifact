#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../correctness
cd core-math
make -s clean
make -s
cd ..
cd glibc
make -s clean
make -s
cd ..
