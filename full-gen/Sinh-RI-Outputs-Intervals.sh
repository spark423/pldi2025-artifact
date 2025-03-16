#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinh intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Sinh-RZ ../intervals/sinhsin_ri_outputs ../intervals/sinhcos_ri_outputs ../intervals/sinh_ri_outputs_oob ../oracles/Sinh34RNOOracle
cd ../intervals
rm sinhsin_ri_outputs sinhcos_ri_outputs sinh_ri_outputs_oob
echo -e "Interval generation complete."

