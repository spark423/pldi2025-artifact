#!/bin/bash
touch results/ourlibm_exp10f.txt
touch results/ourlibm_exp10f_rz.txt
echo -e "|  exp10(x)  |"
./ourlibm/exp10f results/ourlibm_exp10f.txt
./ourlibm/exp10f_rz results/ourlibm_exp10f_rz.txt
