#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Log-MULTI ../intervals/log_ri_inputs ../intervals/log_ri_inputs_oob ../oracles/Log34RNOOracle
cd ../intervals
rm log_ri_inputs log_ri_inputs_oob
touch log_ri_inputs_p1_uq log_ri_inputs_p2_uq
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/log_ri_inputs_uq ../../intervals/log_ri_inputs_p1_uq ../../intervals/log_ri_inputs_p2_uq 0x1.789107b0e4883p-9 
echo -e "Interval generation complete."

