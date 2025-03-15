#!/bin/bash
touch results/rlibm/cosf.txt
touch results/rlibm/cosf_rne.txt
echo -e "|  cos(x)  |"
./rlibm/cosf_rne results/rlibm/cosf_rne.txt
./rlibm/cosf results/rlibm/cosf.txt
