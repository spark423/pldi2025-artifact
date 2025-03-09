#!/bin/bash
touch expf.txt
echo -e "Rounding-invariant input bounds expf"
./ourlibm_expf expf.txt
echo -e "Rounding-invariant outputs expf"
./ourlibm_expf_rz expf.txt
echo -e "RLIBM expf with fesetround"
./rlibm_expf expf.txt
