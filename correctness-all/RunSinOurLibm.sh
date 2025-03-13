#!/bin/bash
touch results/ourlibm_ri_input_bounds_sinf.txt
touch results/ourlibm_ri_outputs_sinf.txt
echo -e "|  sin(x)  |"
./ourlibm/sinf results/ourlibm_ri_input_bounds_sinf.txt
./ourlibm/sinf_rz results/ourlibm_ri_outputs_sinf.txt
