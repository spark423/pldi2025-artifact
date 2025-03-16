#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinpi intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Sinpi-MULTI ../intervals/sinpisin_ri_inputs ../intervals/sinpicos_ri_inputs ../intervals/sinpi_ri_inputs_oob ../oracles/Sinpi34RNOOracle
cd ../intervals
rm sinpisin_ri_inputs sinpicos_ri_inputs sinpi_ri_inputs_oob
echo -e "Interval generation complete."

