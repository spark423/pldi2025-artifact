#!/bin/bash
touch results/rlibm_sinpif.txt
touch results/rlibm_sinpif_rne.txt
echo -e "|  sinpi(x)  |"
./rlibm/sinpif_rne_fp32 results/rlibm_sinpif_rne.txt
./rlibm/sinpif_fp32 results/rlibm_sinpif.txt
