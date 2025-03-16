#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Log-RZ ../intervals/log_ri_outputs ../intervals/log_ri_outputs_oob ../oracles/Log34RNOOracle
cd ../intervals
rm log_ri_outputs log_ri_outputs_oob
touch log_ri_outputs_p1_uq log_ri_outputs_p2_uq
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/log_ri_outputs_uq ../../intervals/log_ri_outputs_p1_uq ../../intervals/log_ri_outputs_p2_uq 0x1.789107b0e4883p-9 
echo -e "Interval generation complete."

