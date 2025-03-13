#!/bin/bash
touch results/rlibm_cospif.txt
touch results/rlibm_cospif_rne.txt
echo -e "|  cospi(x)  |"
./rlibm/cospif results/rlibm_cospif.txt
./rlibm/cospif_rne results/rlibm_cospif_rne.txt
