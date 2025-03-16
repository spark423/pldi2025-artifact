#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log2 intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Log2-MULTI ../intervals/log2_ri_inputs ../intervals/log2_ri_inputs_oob ../oracles/Log234RNOOracle
cd ../intervals
rm log2_ri_inputs log2_ri_inputs_oob
echo -e "Interval generation complete."

