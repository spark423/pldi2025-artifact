#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the exp intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Exp-RZ ../intervals/exp_ri_outputs ../intervals/exp_ri_outputs_oob ../oracles/Exp34RNOOracle
cd ../intervals
rm exp_ri_outputs exp_ri_outputs_oob
touch exp_ri_outputs_p1_uq exp_ri_outputs_p2_uq
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/exp_ri_outputs_uq ../../intervals/exp_ri_outputs_p1_uq ../../intervals/exp_ri_outputs_p2_uq -0x1.9e76cap-24 
echo -e "Interval generation complete."

