#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp2 intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Exp2-RZ ../intervals/exp2_ri_outputs ../intervals/exp2_ri_outputs_oob ../oracles/Exp234RNOOracle
cd ../intervals
rm exp2_ri_outputs exp2_ri_outputs_oob
echo -e "Interval generation complete."

