#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cos intervals (part 2) using RLIBM method. Estimated time: approximately 60 mins."
./CosP2-RN ../intervals/cossin_rlibm_p2 ../intervals/coscos_rlibm_p2 ../intervals/cos_rlibm_p2_oob ../oracles/Cos34RNOOracle
cd ../intervals
rm cossin_rlibm_p2 coscos_rlibm_p2 cos_rlibm_p2_oob
echo -e "Interval generation complete."

