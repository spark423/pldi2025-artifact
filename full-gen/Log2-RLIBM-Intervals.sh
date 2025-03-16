#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log2 intervals using RLIBM method. Estimated time: approximately 60 mins."
./Log2-RN ../intervals/log2_rlibm ../intervals/log2_rlibm_oob ../oracles/Log234RNOOracle
cd ../intervals
rm log2_rlibm log2_rlibm_oob
echo -e "Interval generation complete."

