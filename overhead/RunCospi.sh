#!/bin/bash
touch rounding_invariant_input_bounds_cospif.txt
touch rounding_invariant_outputs_cospif.txt
touch rlibm_cospif.txt
echo -e "Rounding-invariant input bounds cospif"
./ourlibm_cospif rounding_invariant_input_bounds_cospif.txt
echo -e "Rounding-invariant outputs cospif"
./ourlibm_cospif_rz rounding_invariant_outputs_cospif.txt
echo -e "RLIBM cospif with fesetround"
./rlibm_cospif rlibm_cospif.txt
