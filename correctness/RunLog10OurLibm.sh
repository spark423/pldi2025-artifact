#!/bin/bash
touch results/ourlibm_log10f.txt
touch results/ourlibm_log10f_rz.txt
echo -e "|  log10(x)  |"
./ourlibm/log10f results/ourlibm_log10f.txt
./ourlibm/log10f_rz results/ourlibm_log10f_rz.txt
