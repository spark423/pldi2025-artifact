#!/bin/bash
touch rounding_invariant_input_bounds_exp10f.txt
touch rounding_invariant_outputs_exp10f.txt
touch rlibm_exp10f.txt
echo -e "Rounding-invariant input bounds exp10f"
./ourlibm_exp10f rounding_invariant_input_bounds_exp10f.txt
echo -e "Rounding-invariant outputs exp10f"
./ourlibm_exp10f_rz rounding_invariant_outputs_exp10f.txt
echo -e "RLIBM exp10f with fesetround"
./rlibm_exp10f rlibm_exp10f.txt
