#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 1) using rounding-invariant input bounds method. Estimated time: approximately 60 mins."
./SinP1-MULTI ../intervals/sinsin_ri_inputs_p1 ../intervals/sincos_ri_inputs_p1 ../intervals/sin_ri_inputs_p1_oob ../oracles/Sin34RNOOracle
cd ../intervals
rm sinsin_ri_inputs_p1 sincos_ri_inputs_p1 sin_ri_inputs_p1_oob
echo -e "Interval generation complete."

