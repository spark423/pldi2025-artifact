#!/bin/bash
touch results/ourlibm_ri_input_bounds_coshf.txt
touch results/ourlibm_ri_outputs_coshf.txt
echo -e "|  cosh(x)  |"
./ourlibm/coshf results/ourlibm_ri_input_bounds_coshf.txt
./ourlibm/coshf_rz results/ourlibm_ri_outputs_coshf.txt
