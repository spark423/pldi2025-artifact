#!/bin/bash
touch results/ourlibm_exp2f.txt
touch results/ourlibm_exp2f_rz.txt
echo -e "|  exp2(x)  |"
./ourlibm/exp2f results/ourlibm_exp2f.txt
./ourlibm/exp2f_rz results/ourlibm_exp2f_rz.txt
