#!/bin/bash
touch results/rlibm/sinhf.txt
touch results/rlibm/sinhf_rne.txt
echo -e "|  sinh(x)  |"
./rlibm/sinhf_rne_fp32 results/rlibm/sinhf_rne.txt
./rlibm/sinhf_fp32 results/rlibm/sinhf.txt
