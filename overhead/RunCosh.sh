#!/bin/bash
touch rounding_invariant_input_bounds_coshf.txt
touch rounding_invariant_outputs_coshf.txt
touch rlibm_coshf.txt
echo -e "Rounding-invariant input bounds coshf"
./ourlibm_coshf rounding_invariant_input_bounds_coshf.txt
echo -e "Rounding-invariant outputs coshf"
./ourlibm_coshf_rz rounding_invariant_outputs_coshf.txt
echo -e "RLIBM coshf with fesetround"
./rlibm_coshf rlibm_coshf.txt
