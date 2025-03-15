#!/bin/bash
touch results/rlibm/sinf.txt
touch results/rlibm/sinf_rne.txt
echo -e "|  sin(x)  |"
./rlibm/sinf_rne_fp32 results/rlibm/sinf_rne.txt
./rlibm/sinf_fp32 results/rlibm/sinf.txt
