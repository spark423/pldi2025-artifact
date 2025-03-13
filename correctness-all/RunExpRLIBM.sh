#!/bin/bash
touch results/rlibm_expf.txt
touch results/rlibm_expf_rne.txt
echo -e "|  exp(x)  |"
./rlibm/expf results/rlibm_expf.txt
./rlibm/expf_rne results/rlibm_expf_rne.txt
