#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cos intervals (part 2) using rounding-invariant input bounds method. Estimated time: approximately 60 mins."
./CosP2-MULTI ../intervals/cossin_ri_inputs_p2 ../intervals/coscos_ri_inputs_p2 ../intervals/cos_ri_inputs_p2_oob ../oracles/Cos34RNOOracle
cd ../intervals
rm cossin_ri_inputs_p2 coscos_ri_inputs_p2 cos_ri_inputs_p2_oob
echo -e "Interval generation complete."

