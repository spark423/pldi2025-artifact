#!/bin/bash
touch results/ourlibm_cospif.txt
touch results/ourlibm_cospif_rz.txt
echo -e "|  cospi(x)  |"
./ourlibm/cospif results/ourlibm_cospif.txt
./ourlibm/cospif_rz results/ourlibm_cospif_rz.txt
