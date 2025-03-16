#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 1) using RLIBM method. Estimated time: approximately 60 mins."
./SinP1-RN ../intervals/sinsin_rlibm_p1 ../intervals/sincos_rlibm_p1 ../intervals/sin_rlibm_p1_oob ../oracles/Sin34RNOOracle
cd ../intervals
rm sinsin_rlibm_p1 sincos_rlibm_p1 sin_rlibm_p1_oob
echo -e "Interval generation complete."

