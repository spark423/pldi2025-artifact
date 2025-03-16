#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log intervals using RLIBM method. Estimated time: approximately 60 mins."
./Log-RN ../intervals/log_rlibm ../intervals/log_rlibm_oob ../oracles/Log34RNOOracle
cd ../intervals
rm log_rlibm log_rlibm_oob
echo -e "Interval generation complete."

