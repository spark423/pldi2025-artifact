#!/bin/bash
touch results/ourlibm/ri_input_bounds_logf.txt
touch results/ourlibm/ri_outputs_logf.txt
echo -e "|  log(x)  |"
./ourlibm/logf results/ourlibm/ri_input_bounds_logf.txt
./ourlibm/logf_rz results/ourlibm/ri_outputs_logf.txt
