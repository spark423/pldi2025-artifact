#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log2 intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Log2-RZ ../intervals/log2_ri_outputs ../intervals/log2_ri_outputs_oob ../oracles/Log234RNOOracle
cd ../intervals
rm log2_ri_outputs log2_ri_outputs_oob
echo -e "Interval generation complete."

