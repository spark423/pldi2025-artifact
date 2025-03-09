#!/bin/bash
touch logf.txt
echo -e "Rounding-invariant input bounds logf"
./ourlibm_logf logf.txt
echo -e "Rounding-invariant outputs logf"
./ourlibm_logf_rz logf.txt
echo -e "RLIBM logf with fesetround"
./rlibm_logf logf.txt
