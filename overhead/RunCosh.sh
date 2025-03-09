#!/bin/bash
touch coshf.txt
echo -e "Rounding-invariant input bounds coshf"
./ourlibm_coshf coshf.txt
echo -e "Rounding-invariant outputs coshf"
./ourlibm_coshf_rz coshf.txt
echo -e "RLIBM coshf with fesetround"
./rlibm_coshf coshf.txt
