#!/bin/bash
cd ../
mkdir -p intervals
cd interval-gen
make -s
echo -e "Generating the cospi intervals using RLIBM method. Estimated time: approximately 60 mins."
./Cospi-RN ../intervals/cospisin_rlibm ../intervals/cospicos_rlibm ../intervals/cospi_rlibm_oob ../oracles/Cospi34RNOOracle
cd ../intervals
rm cospisin_rlibm cospicos_rlibm cospi_rlibm_oob
echo -e "Interval generation complete."

