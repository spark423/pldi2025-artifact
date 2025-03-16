#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the log10 intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Log10-RZ ../intervals/log10_ri_outputs ../intervals/log10_ri_outputs_oob ../oracles/Log1034RNOOracle
cd ../intervals
rm log10_ri_outputs log10_ri_outputs_oob
touch log10_ri_outputs_p1_uq log10_ri_outputs_p2_uq log10_ri_outputs_p3_uq log10_ri_outputs_ri_outputs_p4_uq log10_ri_outputs_half_p1 log10_ri_outputs_half_p2
cd ../interval-gen/interval-split
make -s
./Interval-Split ../../intervals/log10_ri_outputs_uq ../../intervals/log10_ri_outputs_half_p1 ../../intervals/log10_ri_outputs_half_p2 0x1.5ac30c30c30c2p-9 
./Interval-Split ../../intervals/log10_ri_outputs_half_p1 ../../intervals/log10_ri_outputs_p1_uq ../../intervals/log10_ri_outputs_p2_uq 0x1.5abffffffffffp-10  
./Interval-Split ../../intervals/log10_ri_outputs_half_p2 ../../intervals/log10_ri_outputs_p3_uq ../../intervals/log10_ri_outputs_p4_uq 0x1.038e9aa180dbep-8 
cd ../../intervals
rm log10_ri_outputs_half_p1 log10_ri_outputs_half_p2
echo -e "Interval generation complete."

