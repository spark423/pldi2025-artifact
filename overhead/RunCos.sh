#!/bin/bash
touch cosf.txt
echo -e "Rounding-invariant input bounds cosf"
./ourlibm_cosf cosf.txt
echo -e "Rounding-invariant outputs cosf"
./ourlibm_cosf_rz cosf.txt
echo -e "RLIBM cosf with fesetround"
./rlibm_cosf cosf.txt
