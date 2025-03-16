#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cospi intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Cospi-RZ ../intervals/cospisin_ri_outputs ../intervals/cospicos_ri_outputs ../intervals/cospi_ri_outputs_oob ../oracles/Cospi34RNOOracle
cd ../intervals
rm cospisin_ri_outputs cospicos_ri_outputs cospi_ri_outputs_oob
echo -e "Interval generation complete."

