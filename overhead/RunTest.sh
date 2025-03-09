#!/bin/bash
bold=$(tput bold)
normal=$(tput sgr0)

echo -e "${bold}Testing overhead of Cos(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunCos.sh
echo -e "${bold}Testing overhead of Cosh(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunCosh.sh
echo -e "${bold}Testing overhead of Cospi(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunCospi.sh
echo -e "${bold}Testing overhead of Exp(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunExp.sh
echo -e "${bold}Testing overhead of Exp2(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunExp2.sh
echo -e "${bold}Testing overhead of Exp10(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunExp10.sh
echo -e "${bold}Testing overhead of Log(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunLog.sh
echo -e "${bold}Testing overhead of Log2(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunLog2.sh
echo -e "${bold}Testing overhead of Log10(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunLog10.sh
echo -e "${bold}Testing overhead of Sin(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunSin.sh
echo -e "${bold}Testing overhead of Sinh(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunSinh.sh
echo -e "${bold}Testing overhead of Sinpi(x) (Rounding-invariant input bounds vs Rounding-invariant outputs vs RLIBM with fesetround)${normal}"
bash RunSinpi.sh
