#!/bin/bash
touch rounding_invariant_input_bounds_sinpif.txt
touch rounding_invariant_outputs_sinpif.txt
touch rlibm_sinpif.txt
echo -e "Rounding-invariant input bounds sinpif"
./ourlibm_sinpif rounding_invariant_input_bounds_sinpif.txt
echo -e "Rounding-invariant outputs sinpif"
./ourlibm_sinpif_rz rounding_invariant_outputs_sinpif.txt
echo -e "RLIBM sinpif with fesetround"
./rlibm_sinpif rlibm_sinpif.txt
