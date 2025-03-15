#!/bin/bash
touch results/rlibm/coshf.txt
touch results/rlibm/coshf_rne.txt
echo -e "|  cosh(x)  |"
./rlibm/coshf_rne results/rlibm/coshf_rne.txt
./rlibm/coshf results/rlibm/coshf.txt
