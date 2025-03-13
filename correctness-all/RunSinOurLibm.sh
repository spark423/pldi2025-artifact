#!/bin/bash
touch results/ourlibm_sinf.txt
touch results/ourlibm_sinf_rz.txt
echo -e "|  sin(x)  |"
./ourlibm/sinf results/ourlibm_sinf.txt
./ourlibm/sinf_rz results/ourlibm_sinf_rz.txt
