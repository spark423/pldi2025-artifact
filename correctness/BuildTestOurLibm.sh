#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../correctness
cd ourlibm
make -s clean
make -s
cd ..
mkdir -p results
mkdir -p results/ourlibm
