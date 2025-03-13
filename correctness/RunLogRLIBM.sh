#!/bin/bash
touch results/rlibm_logf.txt
touch results/rlibm_logf_rne.txt
echo -e "|  log(x)  |"
./rlibm/logf_fp32 results/rlibm_logf.txt
./rlibm/logf_rne_fp32 results/rlibm_logf_rne.txt
