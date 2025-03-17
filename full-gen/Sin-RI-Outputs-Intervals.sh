#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sin intervals (part 1) using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./SinP1-RZ ../intervals/sinsin_ri_outputs_p1 ../intervals/sincos_ri_outputs_p1 ../intervals/sin_ri_outputs_p1_oob ../oracles/Sin34RNOOracle
echo -e "Interval generation complete."
echo -e "Generating the sin intervals (part 2) using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./SinP2-RZ ../intervals/sinsin_ri_outputs_p2 ../intervals/sincos_ri_outputs_p2 ../intervals/sin_ri_outputs_p2_oob ../oracles/Sin34RNOOracle
echo -e "Interval generation complete."
cd ../intervals
rm sinsin_ri_outputs_p1 sincos_ri_outputs_p1 sin_ri_outputs_p1_oob
rm sinsin_ri_outputs_p2 sincos_ri_outputs_p2 sin_ri_outputs_p2_oob

