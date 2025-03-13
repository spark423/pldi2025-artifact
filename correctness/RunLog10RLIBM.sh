#!/bin/bash
touch results/rlibm_log10f.txt
touch results/rlibm_log10f_rne.txt
echo -e "|  log10(x)  |"
./rlibm/log10f results/rlibm_log10f.txt
./rlibm/log10f_rne results/rlibm_log10f_rne.txt
