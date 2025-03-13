#!/bin/bash
touch results/ourlibm_ri_input_bounds_expf.txt
touch results/ourlibm_ri_outputs_expf.txt
echo -e "|  exp(x)  |"
./ourlibm/expf results/ourlibm_ri_input_bounds_expf.txt
./ourlibm/expf_rz results/ourlibm_ri_outputs_expf.txt
