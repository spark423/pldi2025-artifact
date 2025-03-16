#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp2 intervals using RLIBM method. Estimated time: approximately 60 mins."
./Exp2-RN ../intervals/exp2_rlibm ../intervals/exp2_rlibm_oob ../oracles/Exp234RNOOracle
cd ../intervals
rm exp2_rlibm exp2_rlibm_oob
echo -e "Interval generation complete."

