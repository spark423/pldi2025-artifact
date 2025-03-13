#!/bin/bash
touch results/rlibm_sinhf.txt
touch results/rlibm_sinhf_rne.txt
echo -e "|  sinh(x)  |"
./rlibm/sinhf results/rlibm_sinhf.txt
./rlibm/sinhf_rne results/rlibm_sinhf_rne.txt
