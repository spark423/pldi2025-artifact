#!/bin/bash
touch results/ourlibm_ri_input_bounds_logf.txt
touch results/ourlibm_ri_outputs_logf.txt
echo -e "|  log(x)  |"
./ourlibm/logf results/ourlibm_ri_input_bounds_logf.txt
./ourlibm/logf_rz results/ourlibm_ri_outputs_logf.txt
