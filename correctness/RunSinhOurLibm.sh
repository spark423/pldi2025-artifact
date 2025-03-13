#!/bin/bash
touch results/ourlibm_ri_input_bounds_sinhf.txt
touch results/ourlibm_ri_outputs_sinhf.txt
echo -e "|  sinh(x)  |"
./ourlibm/sinhf results/ourlibm_ri_input_bounds_sinhf.txt
./ourlibm/sinhf_rz results/ourlibm_ri_outputs_sinhf.txt
