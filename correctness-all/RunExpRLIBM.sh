#!/bin/bash
touch results/rlibm/expf.txt
touch results/rlibm/expf_rne.txt
echo -e "|  exp(x)  |"
./rlibm/expf_rne results/rlibm/expf_rne.txt
./rlibm/expf results/rlibm/expf.txt
