#!/bin/bash
touch rounding_invariant_input_bounds_exp2f.txt
touch rounding_invariant_outputs_exp2f.txt
touch rlibm_exp2f.txt
echo -e "Rounding-invariant input bounds exp2f"
./ourlibm_exp2f rounding_invariant_input_bounds_exp2f.txt
echo -e "Rounding-invariant outputs exp2f"
./ourlibm_exp2f_rz rounding_invariant_outputs_exp2f.txt
echo -e "RLIBM exp2f with fesetround"
./rlibm_exp2f rlibm_exp2f.txt
