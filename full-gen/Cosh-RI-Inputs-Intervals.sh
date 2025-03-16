#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cosh intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Cosh-MULTI ../intervals/coshsin_ri_inputs ../intervals/coshcos_ri_inputs ../intervals/cosh_ri_inputs_oob ../oracles/Cosh34RNOOracle
cd ../intervals
rm coshsin_ri_inputs coshcos_ri_inputs cosh_ri_inputs_oob
echo -e "Interval generation complete."

