#!/bin/bash
touch results/ourlibm/ri_input_bounds_cospif.txt
touch results/ourlibm/ri_outputs_cospif.txt
echo -e "|  cospi(x)  |"
./ourlibm/cospif results/ourlibm/ri_input_bounds_cospif.txt
./ourlibm/cospif_rz results/ourlibm/ri_outputs_cospif.txt
