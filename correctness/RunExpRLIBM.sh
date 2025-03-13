#!/bin/bash
touch results/rlibm_expf.txt
touch results/rlibm_expf_rne.txt
echo -e "|  exp(x)  |"
./rlibm/expf_fp32 results/rlibm_expf.txt
./rlibm/expf_rne_fp32 results/rlibm_expf_rne.txt
