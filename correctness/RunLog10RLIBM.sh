#!/bin/bash
touch results/rlibm_log10f.txt
touch results/rlibm_log10f_rne.txt
echo -e "|  log10(x)  |"
./rlibm/log10f_rne_fp32 results/rlibm_log10f_rne.txt
./rlibm/log10f_fp32 results/rlibm_log10f.txt
