#!/bin/bash
touch results/rlibm_sinpif.txt
touch results/rlibm_sinpif_rne.txt
echo -e "|  sinpi(x)  |"
./rlibm/sinpif results/rlibm_sinpif.txt
./rlibm/sinpif_rne results/rlibm_sinpif_rne.txt
