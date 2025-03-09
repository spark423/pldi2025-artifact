#!/bin/bash
touch sinf.txt
echo -e "Rounding-invariant input bounds sinf"
./ourlibm_sinf sinf.txt
echo -e "Rounding-invariant outputs sinf"
./ourlibm_sinf_rz sinf.txt
echo -e "RLIBM sinf with fesetround"
./rlibm_sinf sinf.txt
