#include <math.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interval-gen/IntervalGenSinhCosh.h"

#ifdef RNDZ
  int rnd = FE_TOWARDZERO;
#else
  int rnd = FE_TONEAREST;
#endif

#ifdef MULTI
  bool multi = true;
#else
  bool multi = false;
#endif

#ifdef FMA
  bool useFMA = true;
#else
  bool useFMA = false;
#endif

mpfr_t sinh_val, cosh_val, pi;

bool ComputeSpecialCase(float x) {
  float_x fx = {x};
  fx.x &= 0x7fffffff;
  if (fx.x<=0x39e89768) return true;
  if (fx.x>=0x42b2d4fd) return true;
  return false;
}

int RangeReduction(float x, double& xp) {
  float_x fx = {x};
  fx.x &= 0x7fffffff;
  double n_int = __builtin_trunc((double)fx.f * CONST64BYLN2);
  double_x NX = {.d = 0x1p52 + n_int};
  int N = (int)NX.x; 
  xp = __builtin_fma(-n_int, LN2BY64, fx.f);
  return N;
}

int SinGuessInitialVal(double xp, double sinhM, double sinhH, double coshM, double coshH, double& sinLB, double& sinUB) {
  double coshHM = sinhH*sinhM+coshH*coshM;
  if (coshHM != 0.0) {
    mpfr_set_d(sinh_val, xp, MPFR_RNDN);
    mpfr_sinh(sinh_val, sinh_val, MPFR_RNDN);
    double sinXP = mpfr_get_d(sinh_val, MPFR_RNDN);
    sinLB = sinXP;
    sinUB = sinXP;
  } else {
    sinLB = -1.0e300;
    sinUB = 1.0e300;
  }
  return 0;
}

int CosGuessInitialVal(double xp, double sinhM, double sinhH, double coshM, double coshH, double& cosLB, double& cosUB) {
  double sinhHM = sinhH*coshM+coshH*sinhM;
  if (sinhHM != 0.0) {
    mpfr_set_d(cosh_val, xp, MPFR_RNDN);
    mpfr_cosh(cosh_val, cosh_val, MPFR_RNDN);
    double cosXP = mpfr_get_d(cosh_val, MPFR_RNDN);
    cosLB = cosXP;
    cosUB = cosXP;
  } else {
    cosLB = -1.0e300;
    cosUB = 1.e300;
  }
  return 0;
}

int GetConsts(int N, double& sinhM, double& sinhH, double& coshM, double& coshH) {
  int N2 = N&0x3f;
  int N1 = N - N2;
  int I = N1 >> 6; 
  sinhM = sinhKLn2By64[N2], sinhH = sinhKLn2[I], coshM = coshKLn2By64[N2], coshH = coshKLn2[I];
  return 0;
}

double OutputCompensationFMA(bool isOCLB, double sinhM, double sinhH, double coshM, double coshH, double sinLB, double sinUB, double cosLB, double cosUB) {
  double sinhHM = __builtin_fma(sinhH, coshM, coshH*sinhM);
  double coshHM = __builtin_fma(sinhH, sinhM, coshH*coshM);
  if (isOCLB) {
    return __builtin_fma(sinhHM, cosLB, coshHM*sinLB);
  } else {
    return __builtin_fma(sinhHM, cosUB, coshHM*sinUB);
  }
}

double OutputCompensation(bool isOCLB, double sinhM, double sinhH, double coshM, double coshH, double sinLB, double sinUB, double cosLB, double cosUB, bool useFMA) {
  if (useFMA) return OutputCompensationFMA(isOCLB, sinhM, sinhH, coshM, coshH, sinLB, sinUB, cosLB, cosUB);
  double sinhHM = sinhH*coshM+coshH*sinhM;
  double coshHM = sinhH*sinhM+coshH*coshM;
  if (isOCLB) {
    return sinhHM*cosLB+coshHM*sinLB;
  } else {
    return sinhHM*cosUB+coshHM*sinUB;
  }
}

int UpdateIntervals(bool isOCLB, double newSinLB, double newSinUB, double newCosLB, double newCosUB, double& sinLB, double& sinUB, double& cosLB, double& cosUB) {
  if (isOCLB) {
    cosLB = newCosLB, sinLB = newSinLB;
  } else {
    cosUB = newCosUB, sinUB = newSinUB;
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 5) {
    printf("Usage: %s <Name of the Sin Interval File> <Name of the Cos Interval File> <Name of the Failed Input File> <Oracle File>\n", argv[0]);
    exit(0);
  }
  fesetround(rnd);
  mpfr_init2(sinh_val, 600);
  mpfr_init2(cosh_val, 600);
  mpfr_init2(pi, 600);
  mpfr_const_pi(pi, MPFR_RNDN);
  CreateIntervalFile(argv[1], argv[2], argv[3], argv[4], 0x0, 0x80000000, multi, useFMA);
  mpfr_clears(sinh_val, cosh_val, pi, (mpfr_ptr) 0);
  return 0;
}

