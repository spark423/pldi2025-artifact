#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log10 intervals using RLIBM method. Estimated time: approximately 60 mins."
./Log10-RN ../intervals/log10_rlibm ../intervals/log10_rlibm_oob ../oracles/Log1034RNOOracle
cd ../intervals
rm log10_rlibm log10_rlibm_oob
echo -e "Interval generation complete."

