#!/bin/bash
cd ../
mkdir -p intervals
touch cos_small_p1 cos_small_p2 
cd interval-gen
make -s
echo -e "Generating the small case intervals for cos. Estimated time: approximately 60 mins."
./CosSmall ../intervals/cos_small_p1 ../intervals/cos_small_p2 ../oracles/Cos34RNOOracle
echo -e "Interval generation complete."

