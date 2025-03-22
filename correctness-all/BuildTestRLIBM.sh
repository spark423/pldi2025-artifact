#!/bin/bash
cd ../libm
make -s
cd ../correctness-all
cd rlibm
make -s clean
make -s
cd ..
mkdir -p results
mkdir -p results/rlibm
