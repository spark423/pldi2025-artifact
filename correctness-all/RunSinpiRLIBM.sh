#!/bin/bash
touch results/rlibm_sinpif.txt
touch results/rlibm_sinpif_rne.txt
echo -e "|  sinpi(x)  |"
./ourlibm/sinpif results/ourlibm_sinpif.txt
./ourlibm/sinpif_rz results/ourlibm_sinpif_rz.txt
