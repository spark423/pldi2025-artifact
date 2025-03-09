#!/bin/bash
touch log10f.txt
echo -e "Rounding-invariant input bounds log10f"
./ourlibm_log10f log10f.txt
echo -e "Rounding-invariant outputs log10f"
./ourlibm_log10f_rz log10f.txt
echo -e "RLIBM log10f with fesetround"
./rlibm_log10f log10f.txt
