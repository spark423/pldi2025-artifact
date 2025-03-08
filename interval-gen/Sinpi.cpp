#include <math.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "IntervalGenSinCos.h"

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

mpfr_t sinpi, cospi, pi;

bool ComputeSpecialCase(float x) {
  float_x fx = {x};
  fx.x &= 0x7fffffff;
  if (fx.x<=0x33fc1537) return true;
  if (fx.x>=0x4b000000) return true;
  double xp;
  int N = RangeReduction(x, xp); 
  unsigned N2 = N&0x7f;
  if (xp == 0.0 && N2 == 0) return true;
  return false;
}

int RangeReduction(float x, double& xp) {
  double n_int = __builtin_roundeven(x * 256.0);
  xp = -n_int*0.00390625+x;
  double_x NX = {.d = 0x1.8p52 + n_int};
  int N = NX.x;
  return N; 
}

int SinGuessInitialVal(double xp, double sinpiK, double cospiK, double& sinLB, double& sinUB) {
  if (cospiK != 0.0) {
    mpfr_set_d(sinpi, xp, MPFR_RNDN);
    mpfr_mul(sinpi, sinpi, pi, MPFR_RNDN);
    mpfr_sin(sinpi, sinpi, MPFR_RNDN);
    double sinXP = mpfr_get_d(sinpi, MPFR_RNDN);
    sinLB = sinXP;
    sinUB = sinXP;
  } else {
    sinLB = -1.0e300;
    sinUB = 1.0e300;
  }
  return 0;
}

int CosGuessInitialVal(double xp, double sinpiK, double cospiK, double& cosLB, double& cosUB) {
  if (sinpiK != 0.0) {
    mpfr_set_d(cospi, xp, MPFR_RNDN);
    mpfr_mul(cospi, cospi, pi, MPFR_RNDN);
    mpfr_cos(cospi, cospi, MPFR_RNDN);
    double cosXP = mpfr_get_d(cospi, MPFR_RNDN);
    cosLB = cosXP;
    cosUB = cosXP;
  } else {
    cosLB = -1.0e300;
    cosUB = 1.e300;
  }
  return 0;
}

int GetConsts(int N, double& sinpiK, double& cospiK) {
  sinpiK = sinpiMBy256TwoPi[N&511];
  cospiK = sinpiMBy256TwoPi[(N+128)&511];
  return 0;
}

double OutputCompensationFMA(bool isOCLB, double sinpiK, double cospiK, double sinLB, double sinUB, double cosLB, double cosUB) {
  if (isOCLB) {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return __builtin_fma(sinpiK, cosLB, cospiK*sinLB);
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return __builtin_fma(sinpiK, cosLB, cospiK*sinUB);
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return __builtin_fma(sinpiK, cosUB, cospiK*sinLB);
    } else {
      return __builtin_fma(sinpiK, cosUB, cospiK*sinUB);
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return __builtin_fma(sinpiK, cosUB, cospiK*sinUB);
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return __builtin_fma(sinpiK, cosUB, cospiK*sinLB);
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return __builtin_fma(sinpiK, cosLB, cospiK*sinUB);
    } else {
      return __builtin_fma(sinpiK, cosLB, cospiK*sinLB);
    }
  }
}

double OutputCompensation(bool isOCLB, double sinpiK, double cospiK, double sinLB, double sinUB, double cosLB, double cosUB, bool useFMA) {
  if (useFMA) return OutputCompensationFMA(isOCLB, sinpiK, cospiK, sinLB, sinUB, cosLB, cosUB);
  if (isOCLB) {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return sinpiK*cosLB+cospiK*sinLB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return sinpiK*cosLB+cospiK*sinUB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return sinpiK*cosUB+cospiK*sinLB;
    } else {
      return sinpiK*cosUB+cospiK*sinUB;
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return sinpiK*cosUB+cospiK*sinUB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return sinpiK*cosUB+cospiK*sinLB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return sinpiK*cosLB+cospiK*sinUB;
    } else {
      return sinpiK*cosLB+cospiK*sinLB;
    }
  }
}

int UpdateIntervals(bool isOCLB, double sinpiK, double cospiK, double newSinLB, double newSinUB, double newCosLB, double newCosUB, double& sinLB, double& sinUB, double& cosLB, double& cosUB) {
  if (isOCLB) {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      cosLB = newCosLB, sinLB = newSinLB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      cosLB = newCosLB, sinUB = newSinUB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      cosUB = newCosUB, sinLB = newSinLB;
    } else {
      cosUB = newCosUB, sinUB = newSinUB;
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      cosUB = newCosUB, sinUB = newSinUB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      cosUB = newCosUB, sinLB = newSinLB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      cosLB = newCosLB, sinUB = newSinUB;
    } else {
      cosLB = newCosLB, sinLB = newSinLB;
    }
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 5) {
    printf("Usage: %s <Name of the Sin Interval File> <Name of the Cos Interval File> <Name of the Failed Input File> <Oracle File>\n", argv[0]);
    exit(0);
  }
  fesetround(rnd);
  mpfr_init2(sinpi, 600);
  mpfr_init2(cospi, 600);
  mpfr_init2(pi, 600);
  mpfr_const_pi(pi, MPFR_RNDN);
  CreateIntervalFile(argv[1], argv[2], argv[3], argv[4], 0x0, 0x80000000, multi, useFMA);
  mpfr_clears(sinpi, cospi, pi, (mpfr_ptr) 0);
  return 0;
}

