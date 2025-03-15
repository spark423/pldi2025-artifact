#!/bin/bash
touch results/ourlibm/ri_input_bounds_expf.txt
touch results/ourlibm/ri_outputs_expf.txt
echo -e "|  exp(x)  |"
./ourlibm/expf results/ourlibm/ri_input_bounds_expf.txt
./ourlibm/expf_rz results/ourlibm/ri_outputs_expf.txt
