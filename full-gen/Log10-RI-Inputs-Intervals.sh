#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log10 intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Log10-MULTI ../intervals/log10_ri_inputs ../intervals/log10_ri_inputs_oob ../oracles/Log1034RNOOracle
cd ../intervals
rm log10_ri_inputs log10_ri_inputs_oob
touch log10_ri_inputs_p1_uq log10_ri_inputs_p2_uq log10_ri_inputs_p3_uq log10_ri_inputs_p4_uq log10_ri_inputs_half_p1 log10_ri_inputs_half_p2
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/log10_ri_inputs_uq ../../intervals/log10_ri_inputs_half_p1 ../../intervals/log10_ri_inputs_half_p2 0x1.5ac30c30c30c2p-9 
./Interval-Split ../../intervals/log10_ri_inputs_half_p1 ../../intervals/log10_ri_inputs_p1_uq ../../intervals/log10_ri_inputs_p2_uq 0x1.5abffffffffffp-10  
./Interval-Split ../../intervals/log10_ri_inputs_half_p2 ../../intervals/log10_ri_inputs_p3_uq ../../intervals/log10_ri_inputs_p4_uq 0x1.038e9aa180dbep-8 
cd ../../intervals
rm log10_ri_inputs_half_p1 log10_ri_inputs_half_p2
echo -e "Interval generation complete."

