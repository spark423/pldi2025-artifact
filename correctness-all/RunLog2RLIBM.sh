#!/bin/bash
touch results/rlibm_log2f.txt
touch results/rlibm_log2f_rne.txt
echo -e "|  log2(x)  |"
./rlibm/log2f results/rlibm_log2f.txt
./rlibm/log2f_rne results/rlibm_log2f_rne.txt
