#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp10 intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Exp10-RZ ../intervals/exp10_ri_outputs ../intervals/exp10_ri_outputs_oob ../oracles/Exp1034RNOOracle
cd ../intervals
rm exp10_ri_outputs exp10_ri_outputs_oob
echo -e "Interval generation complete."

