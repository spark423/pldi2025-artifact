#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 2) using RLIBM method. Estimated time: approximately 60 mins."
./SinP2-RN ../intervals/sinsin_rlibm_p2 ../intervals/sincos_rlibm_p2 ../intervals/sin_rlibm_p2_oob ../oracles/Sin34RNOOracle
cd ../intervals
rm sinsin_rlibm_p2 sincos_rlibm_p2 sin_rlibm_p2_oob
echo -e "Interval generation complete."

