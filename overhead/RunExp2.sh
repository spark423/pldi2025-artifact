#!/bin/bash
touch exp2f.txt
echo -e "Rounding-invariant input bounds exp2f"
./ourlibm_exp2f exp2f.txt
echo -e "Rounding-invariant outputs exp2f"
./ourlibm_exp2f_rz exp2f.txt
echo -e "RLIBM exp2f with fesetround"
./rlibm_exp2f exp2f.txt
