#!/bin/bash
touch results/rlibm_sinf.txt
touch results/rlibm_sinf_rne.txt
echo -e "|  sin(x)  |"
./rlibm/sinf results/rlibm_sinf.txt
./rlibm/sinf_rne results/rlibm_sinf_rne.txt
