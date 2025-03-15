#!/bin/bash
touch results/rlibm/logf.txt
touch results/rlibm/logf_rne.txt
echo -e "|  log(x)  |"
./rlibm/logf_rne_fp32 results/rlibm/logf_rne.txt
./rlibm/logf_fp32 results/rlibm/logf.txt
