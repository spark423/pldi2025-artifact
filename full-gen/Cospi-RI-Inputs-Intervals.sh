#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cospi intervals using rounding-invariant inputs method. Estimated time: approximately 60 mins."
./Cospi-MULTI ../intervals/cospisin_ri_inputs ../intervals/cospicos_ri_inputs ../intervals/cospi_ri_inputs_oob ../oracles/Cospi34RNOOracle
cd ../intervals
rm cospisin_ri_inputs cospicos_ri_inputs cospi_ri_inputs_oob
echo -e "Interval generation complete."

