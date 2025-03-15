#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../correctness
cd ourlibm
make -s clean
make -s
mkdir -p results
mkdir -p results/ourlibm
