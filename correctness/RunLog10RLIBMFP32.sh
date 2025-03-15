#!/bin/bash
touch results/rlibm/log10f.txt
touch results/rlibm/log10f_rne.txt
echo -e "|  log10(x)  |"
./rlibm/log10f_rne_fp32 results/rlibm/log10f_rne.txt
./rlibm/log10f_fp32 results/rlibm/log10f.txt
