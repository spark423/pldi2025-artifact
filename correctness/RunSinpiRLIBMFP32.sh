#!/bin/bash
touch results/rlibm/sinpif.txt
touch results/rlibm/sinpif_rne.txt
echo -e "|  sinpi(x)  |"
./rlibm/sinpif_rne_fp32 results/rlibm/sinpif_rne.txt
./rlibm/sinpif_fp32 results/rlibm/sinpif.txt
