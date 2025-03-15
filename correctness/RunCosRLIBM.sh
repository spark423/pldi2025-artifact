#!/bin/bash
touch results/rlibm_cosf.txt
touch results/rlibm_cosf_rne.txt
echo -e "|  cos(x)  |"
./rlibm/cosf_rne_fp32 results/rlibm_cosf_rne.txt
./rlibm/cosf_fp32 results/rlibm_cosf.txt
