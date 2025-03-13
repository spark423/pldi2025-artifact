#!/bin/bash
touch results/rlibm_cosf.txt
touch results/rlibm_cosf_rne.txt
echo -e "|  cos(x)  |"
./rlibm/cosf results/rlibm_cosf.txt
./rlibm/cosf_rne results/rlibm_cosf_rne.txt
