#!/bin/bash
touch results/rlibm/expf.txt
touch results/rlibm/expf_rne.txt
echo -e "|  exp(x)  |"
./rlibm/expf_rne_fp32 results/rlibm/expf_rne.txt
./rlibm/expf_fp32 results/rlibm/expf.txt
