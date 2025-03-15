#!/bin/bash
touch results/rlibm/cospif.txt
touch results/rlibm/cospif_rne.txt
echo -e "|  cospi(x)  |"
./rlibm/cospif_rne_fp32 results/rlibm/cospif_rne.txt
./rlibm/cospif_fp32 results/rlibm/cospif.txt
