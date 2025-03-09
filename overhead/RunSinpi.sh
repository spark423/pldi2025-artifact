#!/bin/bash
touch sinpif.txt
echo -e "Rounding-invariant input bounds sinpif"
./ourlibm_sinpif sinpif.txt
echo -e "Rounding-invariant outputs sinpif"
./ourlibm_sinpif_rz sinpif.txt
echo -e "RLIBM sinpif with fesetround"
./rlibm_sinpif sinpif.txt
