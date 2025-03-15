#!/bin/bash
touch results/ourlibm/ri_input_bounds_coshf.txt
touch results/ourlibm/ri_outputs_coshf.txt
echo -e "|  cosh(x)  |"
./ourlibm/coshf results/ourlibm/ri_input_bounds_coshf.txt
./ourlibm/coshf_rz results/ourlibm/ri_outputs_coshf.txt
