#!/bin/bash
touch results/ourlibm_ri_input_bounds_log2f.txt
touch results/ourlibm_ri_outputs_log2f.txt
echo -e "|  log2(x)  |"
./ourlibm/log2f results/ourlibm_ri_input_bounds_log2f.txt
./ourlibm/log2f_rz results/ourlibm_ri_outputs_log2f.txt
