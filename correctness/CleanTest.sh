#!/bin/bash
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
