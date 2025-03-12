#!/bin/bash
touch results/ourlibm_cospif.txt
touch results/ourlibm_cospif_rz.txt
touch results/rlibm_cospif.txt
touch results/rlibm_cospif_rne.txt
touch results/core_math_cospif.txt
touch results/glibc_double_cospi.txt
echo -e "|  cospi(x)  |"
./ourlibm/cospif results/ourlibm_cospif.txt
./ourlibm/cospif_rz results/ourlibm_cospif_rz.txt
./rlibm/cospif results/rlibm_cospif.txt
./rlibm/cospif_rne results/rlibm_cospif_rne.txt
./core-math/cospif results/core_math_cospif.txt
