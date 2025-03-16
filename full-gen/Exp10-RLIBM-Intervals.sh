#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp10 intervals using RLIBM method. Estimated time: approximately 60 mins."
./Exp10-RN ../intervals/exp10_rlibm ../intervals/exp10_rlibm_oob ../oracles/Exp1034RNOOracle
cd ../intervals
rm exp10_rlibm exp10_rlibm_oob
echo -e "Interval generation complete."

