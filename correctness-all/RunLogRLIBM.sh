#!/bin/bash
touch results/rlibm/logf.txt
touch results/rlibm/logf_rne.txt
echo -e "|  log(x)  |"
./rlibm/logf_rne results/rlibm/logf_rne.txt
./rlibm/logf results/rlibm/logf.txt
