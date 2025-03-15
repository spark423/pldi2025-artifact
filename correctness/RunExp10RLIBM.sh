#!/bin/bash
touch results/rlibm_exp10f.txt
touch results/rlibm_exp10f_rne.txt
echo -e "|  exp10(x)  |"
./rlibm/exp10f_rne_fp32 results/rlibm_exp10f_rne.txt
./rlibm/exp10f_fp32 results/rlibm_exp10f.txt
