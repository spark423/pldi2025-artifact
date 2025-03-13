#!/bin/bash
touch results/ourlibm_ri_input_bounds_cosf.txt
touch results/ourlibm_ri_outputs_cosf.txt
echo -e "|  cos(x)  |"
./ourlibm/cosf results/ourlibm_ri_input_bounds_cosf.txt
./ourlibm/cosf_rz results/ourlibm_ri_outputs_cosf_rz.txt
