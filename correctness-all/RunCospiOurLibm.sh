#!/bin/bash
touch results/ourlibm_ri_input_bounds_cospif.txt
touch results/ourlibm_ri_outputs_cospif.txt
echo -e "|  cospi(x)  |"
./ourlibm/cospif results/ourlibm_ri_input_bounds_cospif.txt
./ourlibm/cospif_rz results/ourlibm_ri_outputs_cospif.txt
