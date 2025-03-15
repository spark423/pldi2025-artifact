#!/bin/bash
touch results/ourlibm/ri_input_bounds_log10f.txt
touch results/ourlibm/ri_outputs_log10f.txt
echo -e "|  log10(x)  |"
./ourlibm/log10f results/ourlibm/ri_input_bounds_log10f.txt
./ourlibm/log10f_rz results/ourlibm/ri_outputs_log10f.txt
