#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp2 intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Exp2-MULTI ../intervals/exp2_ri_inputs ../intervals/exp2_ri_inputs_oob ../oracles/Exp234RNOOracle
cd ../intervals
rm exp2_ri_inputs exp2_ri_inputs_oob
echo -e "Interval generation complete."

