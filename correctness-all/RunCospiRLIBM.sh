#!/bin/bash
touch results/rlibm/cospif.txt
touch results/rlibm/cospif_rne.txt
echo -e "|  cospi(x)  |"
./rlibm/cospif_rne results/rlibm/cospif_rne.txt
./rlibm/cospif results/rlibm/cospif.txt
