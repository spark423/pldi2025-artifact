#!/bin/bash
touch results/ourlibm_ri_input_bounds_log10f.txt
touch results/ourlibm_ri_outputs_log10f.txt
echo -e "|  log10(x)  |"
./ourlibm/log10f results/ourlibm_ri_input_bounds_log10f.txt
./ourlibm/log10f_rz results/ourlibm_ri_outputs_log10f.txt
