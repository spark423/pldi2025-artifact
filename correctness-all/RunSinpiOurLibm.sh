#!/bin/bash
touch results/ourlibm_sinpif.txt
touch results/ourlibm_sinpif_rz.txt
echo -e "|  sinpi(x)  |"
./ourlibm/sinpif results/ourlibm_sinpif.txt
./ourlibm/sinpif_rz results/ourlibm_sinpif_rz.txt
