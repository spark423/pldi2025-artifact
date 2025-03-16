#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp intervals using RLIBM method. Estimated time: approximately 60 mins."
./Exp-RN ../intervals/exp_rlibm ../intervals/exp_rlibm_oob ../oracles/Exp34RNOOracle
cd ../intervals
rm exp_rlibm exp_rlibm_oob
touch exp_rlibm_p1_uq exp_rlibm_p2_uq
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/exp_rlibm_uq ../../intervals/exp_rlibm_p1_uq ../../intervals/exp_rlibm_p2_uq -0x1.9e76cap-24 
echo -e "Interval generation complete."

