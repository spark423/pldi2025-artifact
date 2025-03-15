#!/bin/bash
touch results/rlibm/cosf.txt
touch results/rlibm/cosf_rne.txt
echo -e "|  cos(x)  |"
./rlibm/cosf_rne_fp32 results/rlibm/cosf_rne.txt
./rlibm/cosf_fp32 results/rlibm/cosf.txt
