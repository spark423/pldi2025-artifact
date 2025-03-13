#!/bin/bash
touch results/rlibm_logf.txt
touch results/rlibm_logf_rne.txt
echo -e "|  log(x)  |"
./rlibm/logf results/rlibm_logf.txt
./rlibm/logf_rne results/rlibm_logf_rne.txt
