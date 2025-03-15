#!/bin/bash
touch results/rlibm/log2f.txt
touch results/rlibm/log2f_rne.txt
echo -e "|  log2(x)  |"
./rlibm/log2f_rne results/rlibm/log2f_rne.txt
./rlibm/log2f results/rlibm/log2f.txt
