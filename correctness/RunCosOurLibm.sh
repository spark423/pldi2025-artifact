#!/bin/bash
touch results/ourlibm_cosf.txt
touch results/ourlibm_cosf_rz.txt
echo -e "|  cos(x)  |"
./ourlibm/cosf results/ourlibm_cosf.txt
./ourlibm/cosf_rz results/ourlibm_cosf_rz.txt
