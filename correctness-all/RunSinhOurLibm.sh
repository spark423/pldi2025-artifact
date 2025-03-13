#!/bin/bash
touch results/ourlibm_sinhf.txt
touch results/ourlibm_sinhf_rz.txt
echo -e "|  sinh(x)  |"
./ourlibm/sinhf results/ourlibm_sinhf.txt
./ourlibm/sinhf_rz results/ourlibm_sinhf_rz.txt
