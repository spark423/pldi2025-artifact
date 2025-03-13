#!/bin/bash
touch results/ourlibm_expf.txt
touch results/ourlibm_expf_rz.txt
echo -e "|  exp(x)  |"
./ourlibm/expf results/ourlibm_expf.txt
./ourlibm/expf_rz results/ourlibm_expf_rz.txt
