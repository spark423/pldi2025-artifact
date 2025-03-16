#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 2) using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./SinP2-RZ ../intervals/sinsin_ri_outputs_p2 ../intervals/sincos_ri_outputs_p2 ../intervals/sin_ri_outputs_p2_oob ../oracles/Sin34RNOOracle
cd ../intervals
rm sinsin_ri_outputs_p2 sincos_ri_outputs_p2 sin_ri_outputs_p2_oob
echo -e "Interval generation complete."

