#!/bin/bash
touch results/ourlibm/ri_input_bounds_sinpif.txt
touch results/ourlibm/ri_outputs_sinpif.txt
echo -e "|  sinpi(x)  |"
./ourlibm/sinpif results/ourlibm/ri_input_bounds_sinpif.txt
./ourlibm/sinpif_rz results/ourlibm/ri_outputs_sinpif.txt
