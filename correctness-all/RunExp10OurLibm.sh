#!/bin/bash
touch results/ourlibm/ri_input_bounds_exp10f.txt
touch results/ourlibm/ri_outputs_exp10f.txt
echo -e "|  exp10(x)  |"
./ourlibm/exp10f results/ourlibm/ri_input_bounds_exp10f.txt
./ourlibm/exp10f_rz results/ourlibm/ri_outputs_exp10f.txt
