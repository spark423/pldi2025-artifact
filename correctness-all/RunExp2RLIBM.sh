#!/bin/bash
touch results/rlibm/exp2f.txt
touch results/rlibm/exp2f_rne.txt
echo -e "|  exp2(x)  |"
./rlibm/exp2f_rne results/rlibm/exp2f_rne.txt
./rlibm/exp2f results/rlibm/exp2f.txt
