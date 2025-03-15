#!/bin/bash
touch results/rlibm/sinpif.txt
touch results/rlibm/sinpif_rne.txt
echo -e "|  sinpi(x)  |"
./rlibm/sinpif_rne results/rlibm/sinpif_rne.txt
./rlibm/sinpif results/rlibm/sinpif.txt
