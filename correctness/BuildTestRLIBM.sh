#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../correctness
cd rlibm
make -s clean
make -s
cd ..
mkdir -p results
mkdir -p results/rlibm
