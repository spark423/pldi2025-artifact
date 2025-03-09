#!/bin/bash
touch rounding_invariant_input_bounds_log2f.txt
touch rounding_invariant_outputs_log2f.txt
touch rlibm_log2f.txt
echo -e "Rounding-invariant input bounds log2f"
./ourlibm_log2f rounding_invariant_input_bounds_log2f.txt
echo -e "Rounding-invariant outputs log2f"
./ourlibm_log2f_rz rounding_invariant_outputs_log2f.txt
echo -e "RLIBM log2f with fesetround"
./rlibm_log2f rlibm_log2f.txt
