#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp10 intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Exp10-MULTI ../intervals/exp10_ri_inputs ../intervals/exp10_ri_inputs_oob ../oracles/Exp1034RNOOracle
cd ../intervals
rm exp10_ri_inputs exp10_ri_inputs_oob
echo -e "Interval generation complete."

