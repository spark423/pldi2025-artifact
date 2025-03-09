#!/bin/bash
touch log2f.txt
echo -e "Rounding-invariant input bounds log2f"
./ourlibm_log2f log2f.txt
echo -e "Rounding-invariant outputs log2f"
./ourlibm_log2f_rz log2f.txt
echo -e "RLIBM log2f with fesetround"
./rlibm_log2f log2f.txt
