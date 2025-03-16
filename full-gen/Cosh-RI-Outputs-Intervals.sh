#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cosh intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Cosh-RZ ../intervals/coshsin_ri_outputs ../intervals/coshcos_ri_outputs ../intervals/cosh_ri_outputs_oob ../oracles/Cosh34RNOOracle
cd ../intervals
rm coshsin_ri_outputs coshcos_ri_outputs cosh_ri_outputs_oob
echo -e "Interval generation complete."

