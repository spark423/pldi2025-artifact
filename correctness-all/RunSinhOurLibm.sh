#!/bin/bash
touch results/ourlibm/ri_input_bounds_sinhf.txt
touch results/ourlibm/ri_outputs_sinhf.txt
echo -e "|  sinh(x)  |"
./ourlibm/sinhf results/ourlibm/ri_input_bounds_sinhf.txt
./ourlibm/sinhf_rz results/ourlibm/ri_outputs_sinhf.txt
