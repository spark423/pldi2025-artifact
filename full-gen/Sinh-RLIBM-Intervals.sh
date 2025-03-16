#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinh intervals using RLIBM method. Estimated time: approximately 60 mins."
./Sinh-RN ../intervals/sinhsin_rlibm ../intervals/sinhcos_rlibm ../intervals/sinh_rlibm_oob ../oracles/Sinh34RNOOracle
cd ../intervals
rm sinhsin_rlibm sinhcos_rlibm sinh_rlibm_oob
echo -e "Interval generation complete."

