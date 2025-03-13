#!/bin/bash
touch results/rlibm_sinf.txt
touch results/rlibm_sinf_rne.txt
echo -e "|  sin(x)  |"
./rlibm/sinf_fp32 results/rlibm_sinf.txt
./rlibm/sinf_rne_fp32 results/rlibm_sinf_rne.txt
