#!/bin/bash
touch results/ourlibm_logf.txt
touch results/ourlibm_logf_rz.txt
echo -e "|  log(x)  |"
./ourlibm/logf results/ourlibm_logf.txt
./ourlibm/logf_rz results/ourlibm_logf_rz.txt
