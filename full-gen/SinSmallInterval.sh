#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the small case intervals for sin. Estimated time: approximately 60 mins."
./SinSmall ../intervals/sin_small_p1 ../intervals/sin_small_p2 ../oracles/Sin34RNOOracle
echo -e "Interval generation complete."

