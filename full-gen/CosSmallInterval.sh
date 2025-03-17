#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the small case intervals for cos. Estimated time: approximately 10 mins."
./CosSmall ../intervals/cos_small_p1 ../intervals/cos_small_p2 ../oracles/Cos34RNOOracle
echo -e "Interval generation complete."

