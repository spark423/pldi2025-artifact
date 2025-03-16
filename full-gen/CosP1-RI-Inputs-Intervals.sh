#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cos intervals (part 1) using rounding-invariant input bounds method. Estimated time: approximately 60 mins."
./CosP1-MULTI ../intervals/cossin_ri_inputs_p1 ../intervals/coscos_ri_inputs_p1 ../intervals/cos_ri_inputs_p1_oob ../oracles/Cos34RNOOracle
cd ../intervals
rm cossin_ri_inputs_p1 coscos_ri_inputs_p1 cos_ri_inputs_p1_oob
echo -e "Interval generation complete."

