#!/bin/bash
touch results/rlibm_log2f.txt
touch results/rlibm_log2f_rne.txt
echo -e "|  log2(x)  |"
./rlibm/log2f_rne_fp32 results/rlibm_log2f_rne.txt
./rlibm/log2f_fp32 results/rlibm_log2f.txt
