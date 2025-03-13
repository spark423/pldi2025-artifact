#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

echo "${bold}Testing correctness of Cos(x) for various FP representations${normal}"
./RunCosOurLibm.sh
echo "${bold}Testing correctness of Cosh(x) for various FP representations${normal}"
./RunCoshOurLibm.sh
echo "${bold}Testing correctness of Cospi(x) for various FP representations${normal}"
./RunCospiOurLibm.sh
echo "${bold}Testing correctness of Exp(x) for various FP representations${normal}"
./RunExpOurLibm.sh
echo "${bold}Testing correctness of Exp2(x) for various FP representations${normal}"
./RunExp2OurLibm.sh
echo "${bold}Testing correctness of Exp10(x) for various FP representations${normal}"
./RunExp10OurLibm.sh
echo "${bold}Testing correctness of Log(x) for various FP representations${normal}"
./RunLogOurLibm.sh
echo "${bold}Testing correctness of Log2(x) for various FP representations${normal}"
./RunLog2OurLibm.sh
echo "${bold}Testing correctness of Log10(x) for various FP representations${normal}"
./RunLog10OurLibm.sh
echo "${bold}Testing correctness of Sin(x) for various FP representations${normal}"
./RunSinOurLibm.sh
echo "${bold}Testing correctness of Sinh(x) for various FP representations${normal}"
./RunSinhOurLibm.sh
echo "${bold}Testing correctness of Sinpi(x) for various FP representations${normal}"
./RunSinpiOurLibm.sh
