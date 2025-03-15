#!/bin/bash
touch results/rlibm_coshf.txt
touch results/rlibm_coshf_rne.txt
echo -e "|  cosh(x)  |"
./rlibm/coshf_rne_fp32 results/rlibm_coshf_rne.txt
./rlibm/coshf_fp32 results/rlibm_coshf.txt
