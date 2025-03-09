#!/bin/bash
touch rounding_invariant_input_bounds_cosf.txt
touch rounding_invariant_outputs_cosf.txt
touch rlibm_cosf.txt
echo -e "Rounding-invariant input bounds cosf"
./ourlibm_cosf rounding_invariant_input_bounds_cosf.txt
echo -e "Rounding-invariant outputs cosf"
./ourlibm_cosf_rz rounding_invariant_outputs_cosf.txt
echo -e "RLIBM cosf with fesetround"
./rlibm_cosf rlibm_cosf.txt
