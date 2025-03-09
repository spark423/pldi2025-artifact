#!/bin/bash
touch cospif.txt
echo -e "Rounding-invariant input bounds cospif"
./ourlibm_cospif cospif.txt
echo -e "Rounding-invariant outputs cospif"
./ourlibm_cospif_rz cospif.txt
echo -e "RLIBM cospif with fesetround"
./rlibm_cospif cospif.txt
