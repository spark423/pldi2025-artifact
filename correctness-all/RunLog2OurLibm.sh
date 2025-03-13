#!/bin/bash
touch results/ourlibm_log2f.txt
touch results/ourlibm_log2f_rz.txt
echo -e "|  log2(x)  |"
./ourlibm/log2f results/ourlibm_log2f.txt
./ourlibm/log2f_rz results/ourlibm_log2f_rz.txt
