#!/bin/bash
touch results/rlibm_exp2f.txt
touch results/rlibm_exp2f_rne.txt
echo -e "|  exp2(x)  |"
./rlibm/exp2f_fp32 results/rlibm_exp2f.txt
./rlibm/exp2f_rne_fp32 results/rlibm_exp2f_rne.txt
