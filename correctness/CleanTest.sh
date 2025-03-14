#!/bin/bash
cd ../libm
make -s clean
cd ../correctness
cd ourlibm
make -s clean
cd ..
cd rlibm
make -s clean
cd ..
cd core-math
make -s clean
cd ..
cd glibc
make -s clean
cd ..
rm -rf results/*
rm -rf results
