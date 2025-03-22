#!/bin/bash
cd ../libm
make -s
cd ../correctness
cd rlibm
make -s clean
make -s
cd ..
