#!/bin/bash
touch exp10f.txt
echo -e "Rounding-invariant input bounds exp10f"
./ourlibm_exp10f exp10f.txt
echo -e "Rounding-invariant outputs exp10f"
./ourlibm_exp10f_rz exp10f.txt
echo -e "RLIBM exp10f with fesetround"
./rlibm_exp10f exp10f.txt
