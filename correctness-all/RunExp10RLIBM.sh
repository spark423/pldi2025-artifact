#!/bin/bash
touch results/rlibm_exp10f.txt
touch results/rlibm_exp10f_rne.txt
echo -e "|  exp10(x)  |"
./rlibm/exp10f results/rlibm_exp10f.txt
./rlibm/exp10f_rne results/rlibm_exp10f_rne.txt
