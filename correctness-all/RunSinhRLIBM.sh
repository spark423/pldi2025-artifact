#!/bin/bash
touch results/rlibm/sinhf.txt
touch results/rlibm/sinhf_rne.txt
echo -e "|  sinh(x)  |"
./rlibm/sinhf_rne results/rlibm/sinhf_rne.txt
./rlibm/sinhf results/rlibm/sinhf.txt
