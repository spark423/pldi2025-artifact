#!/bin/bash
touch results/rlibm_sinhf.txt
touch results/rlibm_sinhf_rne.txt
echo -e "|  sinh(x)  |"
./rlibm/sinhf_rne_fp32 results/rlibm_sinhf_rne.txt
./rlibm/sinhf_fp32 results/rlibm_sinhf.txt
