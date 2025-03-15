#!/bin/bash
touch results/ourlibm/ri_input_bounds_log2f.txt
touch results/ourlibm/ri_outputs_log2f.txt
echo -e "|  log2(x)  |"
./ourlibm/log2f results/ourlibm/ri_input_bounds_log2f.txt
./ourlibm/log2f_rz results/ourlibm/ri_outputs_log2f.txt
