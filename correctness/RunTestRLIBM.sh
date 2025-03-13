#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

echo "${bold}Testing correctness of Cos(x) for various FP representations${normal}"
./RunCosRLIBM.sh
echo "${bold}Testing correctness of Cosh(x) for various FP representations${normal}"
./RunCoshRLIBM.sh
echo "${bold}Testing correctness of Cospi(x) for various FP representations${normal}"
./RunCospiRLIBM.sh
echo "${bold}Testing correctness of Exp(x) for various FP representations${normal}"
./RunExpRLIBM.sh
echo "${bold}Testing correctness of Exp2(x) for various FP representations${normal}"
./RunExp2RLIBM.sh
echo "${bold}Testing correctness of Exp10(x) for various FP representations${normal}"
./RunExp10RLIBM.sh
echo "${bold}Testing correctness of Log(x) for various FP representations${normal}"
./RunLogRLIBM.sh
echo "${bold}Testing correctness of Log2(x) for various FP representations${normal}"
./RunLog2RLIBM.sh
echo "${bold}Testing correctness of Log10(x) for various FP representations${normal}"
./RunLog10RLIBM.sh
echo "${bold}Testing correctness of Sin(x) for various FP representations${normal}"
./RunSinRLIBM.sh
echo "${bold}Testing correctness of Sinh(x) for various FP representations${normal}"
./RunSinhRLIBM.sh
echo "${bold}Testing correctness of Sinpi(x) for various FP representations${normal}"
./RunSinpiRLIBM.sh
