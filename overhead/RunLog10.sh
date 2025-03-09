#!/bin/bash
touch rounding_invariant_input_bounds_log10f.txt
touch rounding_invariant_outputs_log10f.txt
touch rlibm_log10f.txt
echo -e "Rounding-invariant input bounds log10f"
./ourlibm_log10f rounding_invariant_input_bounds_log10f.txt
echo -e "Rounding-invariant outputs log10f"
./ourlibm_log10f_rz rounding_invariant_outputs_log10f.txt
echo -e "RLIBM log10f with fesetround"
./rlibm_log10f rlibm_log10f.txt
