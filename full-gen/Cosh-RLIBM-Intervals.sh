#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cosh intervals using RLIBM method. Estimated time: approximately 60 mins."
./Cosh-RN ../intervals/coshsin_rlibm ../intervals/coshcos_rlibm ../intervals/cosh_rlibm_oob ../oracles/Cosh34RNOOracle
cd ../intervals
rm coshsin_rlibm coshcos_rlibm cosh_rlibm_oob
echo -e "Interval generation complete."

