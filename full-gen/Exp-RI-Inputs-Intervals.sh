#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Exp-MULTI ../intervals/exp_ri_inputs ../intervals/exp_ri_inputs_oob ../oracles/Exp34RNOOracle
cd ../intervals
rm exp_ri_inputs exp_ri_inputs_oob
touch exp_ri_inputs_p1_uq exp_ri_inputs_p2_uq
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/exp_ri_inputs_uq ../../intervals/exp_ri_inputs_p1_uq ../../intervals/exp_ri_inputs_p2_uq -0x1.9e76cap-24 
echo -e "Interval generation complete."

