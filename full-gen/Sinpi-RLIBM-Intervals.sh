#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the sinpi intervals using RLIBM method. Estimated time: approximately 60 mins."
./Sinpi-RN ../intervals/sinpisin_rlibm ../intervals/sinpicos_rlibm ../intervals/sinpi_rlibm_oob ../oracles/Sinpi34RNOOracle
cd ../intervals
rm sinpisin_rlibm sinpicos_rlibm sinpi_rlibm_oob
echo -e "Interval generation complete."

