#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../correctness-all
cd ourlibm
make -s clean
make -s
cd ..
cd rlibm
make -s clean
make -s
cd ..
cd core-math
make -s clean
make -s
cd ..
cd glibc
make -s clean
make -s
cd ..
mkdir -p results
