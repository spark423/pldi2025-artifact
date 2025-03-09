#!/bin/bash
touch rounding_invariant_input_bounds_logf.txt
touch rounding_invariant_outputs_logf.txt
touch rlibm_logf.txt
echo -e "Rounding-invariant input bounds logf"
./ourlibm_logf rounding_invariant_input_bounds_logf.txt
echo -e "Rounding-invariant outputs logf"
./ourlibm_logf_rz rounding_invariant_outputs_logf.txt
echo -e "RLIBM logf with fesetround"
./rlibm_logf rlibm_logf.txt
