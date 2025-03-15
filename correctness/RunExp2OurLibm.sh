#!/bin/bash
touch results/ourlibm/ri_input_bounds_exp2f.txt
touch results/ourlibm/ri_outputs_exp2f.txt
echo -e "|  exp2(x)  |"
./ourlibm/exp2f results/ourlibm/ri_input_bounds_exp2f.txt
./ourlibm/exp2f_rz results/ourlibm/ri_outputs_exp2f.txt
