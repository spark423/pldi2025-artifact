#!/bin/bash
touch results/ourlibm/ri_input_bounds_sinf.txt
touch results/ourlibm/ri_outputs_sinf.txt
echo -e "|  sin(x)  |"
./ourlibm/sinf results/ourlibm/ri_input_bounds_sinf.txt
./ourlibm/sinf_rz results/ourlibm/ri_outputs_sinf.txt
