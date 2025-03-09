#!/bin/bash
touch rounding_invariant_input_bounds_sinhf.txt
touch rounding_invariant_outputs_sinhf.txt
touch rlibm_sinhf.txt
echo -e "Rounding-invariant input bounds sinhf"
./ourlibm_sinhf rounding_invariant_input_bounds_sinhf.txt
echo -e "Rounding-invariant outputs sinhf"
./ourlibm_sinhf_rz rounding_invariant_outputs_sinhf.txt
echo -e "RLIBM sinhf with fesetround"
./rlibm_sinhf rlibm_sinhf.txt
