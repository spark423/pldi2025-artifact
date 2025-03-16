#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinpi intervals using rounding-invariant outputs method. Estimated time: approximately 60 mins."
./Sinpi-RZ ../intervals/sinpisin_ri_outputs ../intervals/sinpicos_ri_outputs ../intervals/sinpi_ri_outputs_oob ../oracles/Sinpi34RNOOracle
cd ../intervals
rm sinpisin_ri_outputs sinpicos_ri_outputs sinpi_ri_outputs_oob
echo -e "Interval generation complete."

