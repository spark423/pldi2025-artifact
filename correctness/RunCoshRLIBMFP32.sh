#!/bin/bash
touch results/rlibm/coshf.txt
touch results/rlibm/coshf_rne.txt
echo -e "|  cosh(x)  |"
./rlibm/coshf_rne_fp32 results/rlibm/coshf_rne.txt
./rlibm/coshf_fp32 results/rlibm/coshf.txt
