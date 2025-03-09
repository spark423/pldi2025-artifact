#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

echo "${bold}Testing correctness of Cos(x) for various FP representations${normal}"
./RunCos.sh
echo "${bold}Testing correctness of Cosh(x) for various FP representations${normal}"
./RunCosh.sh
echo "${bold}Testing correctness of Cospi(x) for various FP representations${normal}"
./RunCospi.sh
echo "${bold}Testing correctness of Exp(x) for various FP representations${normal}"
./RunExp.sh
echo "${bold}Testing correctness of Exp2(x) for various FP representations${normal}"
./RunExp2.sh
echo "${bold}Testing correctness of Exp10(x) for various FP representations${normal}"
./RunExp10.sh
echo "${bold}Testing correctness of Log(x) for various FP representations${normal}"
./RunLog.sh
echo "${bold}Testing correctness of Log2(x) for various FP representations${normal}"
./RunLog2.sh
echo "${bold}Testing correctness of Log10(x) for various FP representations${normal}"
./RunLog10.sh
echo "${bold}Testing correctness of Sin(x) for various FP representations${normal}"
./RunSin.sh
echo "${bold}Testing correctness of Sinh(x) for various FP representations${normal}"
./RunSinh.sh
echo "${bold}Testing correctness of Sinpi(x) for various FP representations${normal}"
./RunSinpi.sh
