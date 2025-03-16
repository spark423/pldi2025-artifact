#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 1) using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./SinP1-RZ ../intervals/sinsin_ri_outputs_p1 ../intervals/sincos_ri_outputs_p1 ../intervals/sin_ri_outputs_p1_oob ../oracles/Sin34RNOOracle
cd ../intervals
rm sinsin_ri_outputs_p1 sincos_ri_outputs_p1 sin_ri_outputs_p1_oob
echo -e "Interval generation complete."

