#!/bin/bash
touch rounding_invariant_input_bounds_sinf.txt
touch rounding_invariant_outputs_sinf.txt
touch rlibm_sinf.txt
echo -e "Rounding-invariant input bounds sinf"
./ourlibm_sinf rounding_invariant_input_bounds_sinf.txt
echo -e "Rounding-invariant outputs sinf"
./ourlibm_sinf_rz rounding_invariant_outputs_sinf.txt
echo -e "RLIBM sinf with fesetround"
./rlibm_sinf rlibm_sinf.txt
