#!/bin/bash
touch results/ourlibm_coshf.txt
touch results/ourlibm_coshf_rz.txt
echo -e "|  cosh(x)  |"
./ourlibm/coshf results/ourlibm_coshf.txt
./ourlibm/coshf_rz results/ourlibm_coshf_rz.txt
