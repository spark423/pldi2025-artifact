#!/bin/bash
touch sinhf.txt
echo -e "Rounding-invariant input bounds sinhf"
./ourlibm_sinhf sinhf.txt
echo -e "Rounding-invariant outputs sinhf"
./ourlibm_sinhf_rz sinhf.txt
echo -e "RLIBM sinhf with fesetround"
./rlibm_sinhf sinhf.txt
