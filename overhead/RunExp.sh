#!/bin/bash
touch rounding_invariant_input_bounds_expf.txt
touch rounding_invariant_outputs_expf.txt
touch rlibm_expf.txt
echo -e "Rounding-invariant input bounds expf"
./ourlibm_expf rounding_invariant_input_bounds_expf.txt
echo -e "Rounding-invariant outputs expf"
./ourlibm_expf_rz rounding_invariant_outputs_expf.txt
echo -e "RLIBM expf with fesetround"
./rlibm_expf rlibm_expf.txt
