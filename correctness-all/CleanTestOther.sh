#!/bin/bash
cd core-math
make -s clean
..
cd glibc
make -s clean
cd ..
rm -rf results/mlib/*
rm -rf results/mlib

