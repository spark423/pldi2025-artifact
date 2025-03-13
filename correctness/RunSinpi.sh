#!/bin/bash
touch results/ourlibm_sinpif.txt
touch results/ourlibm_sinpif_rz.txt
touch results/rlibm_sinpif.txt
touch results/rlibm_sinpif_rne.txt
touch results/core_math_sinpif.txt
echo -e "|  sinpi(x)  |"
./ourlibm/sinpif results/ourlibm_sinpif.txt
./ourlibm/sinpif_rz results/ourlibm_sinpif_rz.txt
./rlibm/sinpif results/rlibm_sinpif.txt
./rlibm/sinpif_rne results/rlibm_sinpif_rne.txt
./core-math/sinpif results/core_math_sinpif.txt
