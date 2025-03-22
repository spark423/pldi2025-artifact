#!/bin/bash
cd ../libm
make -s
cd ../correctness
cd ourlibm
make -s clean
make -s
cd ..
