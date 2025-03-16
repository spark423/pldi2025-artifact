#!/bin/bash
touch results/ourlibm/ri_input_bounds_cosf.txt
touch results/ourlibm/ri_outputs_cosf.txt
echo -e "|  cos(x)  |"
./ourlibm/cosf results/ourlibm/ri_input_bounds_cosf.txt
./ourlibm/cosf_rz results/ourlibm/ri_outputs_cosf_rz.txt
