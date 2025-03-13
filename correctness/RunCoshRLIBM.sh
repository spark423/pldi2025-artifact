#!/bin/bash
touch results/rlibm_coshf.txt
touch results/rlibm_coshf_rne.txt
echo -e "|  cosh(x)  |"
./rlibm/coshf results/rlibm_coshf.txt
./rlibm/coshf_rne results/rlibm_coshf_rne.txt
