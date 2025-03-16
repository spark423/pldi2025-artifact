#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinh intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Sinh-MULTI ../intervals/sinhsin_ri_inputs ../intervals/sinhcos_ri_inputs ../intervals/sinh_ri_inputs_oob ../oracles/Sinh34RNOOracle
cd ../intervals
rm sinhsin_ri_inputs sinhcos_ri_inputs sinh_ri_inputs_oob
echo -e "Interval generation complete."

