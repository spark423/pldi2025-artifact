#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

echo -e "${bold}Testing correctness of Cos(x) for various FP representations${normal}"
bash RunCos.sh
echo -e "${bold}Testing correctness of Cosh(x) for various FP representations${normal}"
bash RunCosh.sh
echo -e "${bold}Testing correctness of Cospi(x) for various FP representations${normal}"
bash RunCospi.sh
echo -e "${bold}Testing correctness of Exp(x) for various FP representations${normal}"
bash RunExp.sh
echo -e "${bold}Testing correctness of Exp2(x) for various FP representations${normal}"
bash RunExp2.sh
echo -e "${bold}Testing correctness of Exp10(x) for various FP representations${normal}"
bash RunExp10.sh
echo -e "${bold}Testing correctness of Log(x) for various FP representations${normal}"
bash RunLog.sh
echo -e "${bold}Testing correctness of Log2(x) for various FP representations${normal}"
bash RunLog2.sh
echo -e "${bold}Testing correctness of Log10(x) for various FP representations${normal}"
bash RunLog10.sh
echo -e "${bold}Testing correctness of Sin(x) for various FP representations${normal}"
bash RunSin.sh
echo -e "${bold}Testing correctness of Sinh(x) for various FP representations${normal}"
bash RunSinh.sh
echo -e "${bold}Testing correctness of Sinpi(x) for various FP representations${normal}"
bash RunSinpi.sh
