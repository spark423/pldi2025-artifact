#!/bin/bash
touch results/ourlibm_ri_input_bounds_sinpif.txt
touch results/ourlibm_ri_outputs_sinpif.txt
echo -e "|  sinpi(x)  |"
./ourlibm/sinpif results/ourlibm_ri_input_bounds_sinpif.txt
./ourlibm/sinpif_rz results/ourlibm_ri_outputs_sinpif.txt
