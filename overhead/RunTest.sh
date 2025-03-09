#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)
echo "${bold}Testing overhead of Cos(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunCos.sh
echo "${bold}Testing overhead of Cosh(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunCosh.sh
echo "${bold}Testing overhead of Cospi(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunCospi.sh
echo "${bold}Testing overhead of Exp(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunExp.sh
echo "${bold}Testing overhead of Exp2(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunExp2.sh
echo "${bold}Testing overhead of Exp10(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunExp10.sh
echo "${bold}Testing overhead of Log(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunLog.sh
echo "${bold}Testing overhead of Log2(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunLog2.sh
echo "${bold}Testing overhead of Log10(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunLog10.sh
echo "${bold}Testing overhead of Sin(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunSin.sh
echo "${bold}Testing overhead of Sinh(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunSinh.sh
echo "${bold}Testing overhead of Sinpi(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
./RunSinpi.sh
