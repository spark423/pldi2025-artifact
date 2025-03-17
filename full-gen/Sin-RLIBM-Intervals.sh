#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 1) using RLIBM method. Estimated time: approximately 60 mins."
./SinP1-RN ../intervals/sinsin_rlibm_p1 ../intervals/sincos_rlibm_p1 ../intervals/sin_rlibm_p1_oob ../oracles/Sin34RNOOracle
echo -e "Interval generation complete."
echo -e "Generating the sin intervals (part 2) using RLIBM method. Estimated time: approximately 60 mins."
./SinP2-RN ../intervals/sinsin_rlibm_p2 ../intervals/sincos_rlibm_p2 ../intervals/sin_rlibm_p2_oob ../oracles/Sin34RNOOracle
echo -e "Interval generation complete."
cd ../intervals
rm sinsin_rlibm_p1 sincos_rlibm_p1 sin_rlibm_p1_oob
rm sinsin_rlibm_p2 sincos_rlibm_p2 sin_rlibm_p2_oob

