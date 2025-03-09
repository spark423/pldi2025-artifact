#!/bin/bash
cd ../libm
make -s clean
make -s
cd ../overhead
make -s clean
make -s
