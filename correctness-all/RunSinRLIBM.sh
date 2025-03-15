#!/bin/bash
touch results/rlibm/sinf.txt
touch results/rlibm/sinf_rne.txt
echo -e "|  sin(x)  |"
./rlibm/sinf_rne results/rlibm/sinf_rne.txt
./rlibm/sinf results/rlibm/sinf.txt
