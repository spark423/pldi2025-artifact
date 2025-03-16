#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cos intervals (part 2) using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./CosP2-RZ ../intervals/cossin_ri_outputs_p2 ../intervals/coscos_ri_outputs_p2 ../intervals/sin_ri_outputs_p2_oob ../oracles/Cos34RNOOracle
cd ../intervals
rm cossin_ri_outputs_p2 coscos_ri_outputs_p2 cos_ri_outputs_p2_oob
echo -e "Interval generation complete."

