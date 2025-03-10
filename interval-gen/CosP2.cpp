#include <math.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interval-gen/IntervalGenSinCos.h"

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

#ifdef FILTER
  bool filter = true;
#else
  bool filter = false;
#endif

mpfr_t sinpi, cospi, pi;

bool ComputeSpecialCase(float x) {
  float_x fx = {x};
  unsigned long b = fx.x<<1;
  if (b<0x99000000) return true;
  if (b>=0xff000000) return true;
  return false;
}

int RangeReduction(float x, double& xp) {
  float_x fx = {x};
  unsigned long b = fx.x<<1;
  int s = ((fx.x>>23)&0xff) - 150;
  uint64_t m = (fx.x&0x7FFFFF)|1<<23;
  static const uint64_t ipi[] = {0xdb6295993c439041, 0xfc2757d1f534ddc0, 0xa2f9836e4e441529};
  uint128_t p1 = (uint128_t)m*ipi[0];
  uint128_t p2 = (uint128_t)m*ipi[1]; p2 += p1>>64;
  uint128_t p3 = (uint128_t)m*ipi[2]; p3 += p2>>64;
  uint64_t p3h = p3>>64, p3l = p3, p2l = p2, p1l = p1;
  int N;
  long long a;
  if (s < 57) {
    N = (p3h<<(7+s))|(p3l>>(57-s));
    a = (p3l<<(7+s))|(p2l>>(57-s));
  } else if (s == 57) {
    N = p3l;
    a = p2l;
  } else {
    N = (p3l<<(s-57))|(p2l>>(121-s));
    a = (p2l<<(s-57))|(p1l>>(121-s));
  }
  long sm = a>>63;
  N -= sm;
  xp = ((a>>10)<<10)*0x1p-64;
  return N;
}

int SinGuessInitialVal(double xp, double sinpiK, double cospiK, double& sinLB, double& sinUB) {
  if (sinpiK != 0.0) {
    mpfr_set_d(sinpi, xp, MPFR_RNDN);
    mpfr_mul(sinpi, sinpi, pi, MPFR_RNDN);
    mpfr_div_d(sinpi, sinpi, 256, MPFR_RNDN);
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
  if (cospiK != 0.0) {
    mpfr_set_d(cospi, xp, MPFR_RNDN);
    mpfr_mul(cospi, cospi, pi, MPFR_RNDN);
    mpfr_div_d(cospi, cospi, 256, MPFR_RNDN);
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
      return __builtin_fma(cospiK, cosLB, -sinpiK*sinUB);
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return __builtin_fma(cospiK, cosUB, -sinpiK*sinUB);
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return __builtin_fma(cospiK, cosLB, -sinpiK*sinLB);
    } else {
      return __builtin_fma(cospiK, cosUB, -sinpiK*sinLB);
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return __builtin_fma(cospiK, cosUB, -sinpiK*sinLB);
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return __builtin_fma(cospiK, cosLB, -sinpiK*sinLB);
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return __builtin_fma(cospiK, cosUB, -sinpiK*sinUB);
    } else {
      return __builtin_fma(cospiK, cosLB, -sinpiK*sinUB);
    }
  }
}

double OutputCompensation(bool isOCLB, double sinpiK, double cospiK, double sinLB, double sinUB, double cosLB, double cosUB, bool useFMA) {
  if (useFMA) return OutputCompensationFMA(isOCLB, sinpiK, cospiK, sinLB, sinUB, cosLB, cosUB);
  if (isOCLB) {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return cospiK*cosLB-sinpiK*sinUB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return cospiK*cosUB-sinpiK*sinUB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return cospiK*cosLB-sinpiK*sinLB;
    } else {
      return cospiK*cosUB-sinpiK*sinLB;
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      return cospiK*cosUB-sinpiK*sinLB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      return cospiK*cosLB-sinpiK*sinLB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      return cospiK*cosUB-sinpiK*sinUB;
    } else {
      return cospiK*cosLB-sinpiK*sinUB;
    }
  }
}

int UpdateIntervals(bool isOCLB, double sinpiK, double cospiK, double newSinLB, double newSinUB, double newCosLB, double newCosUB, double& sinLB, double& sinUB, double& cosLB, double& cosUB) {
  if (isOCLB) {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      cosLB = newCosLB, sinUB = newSinUB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      cosUB = newCosUB, sinUB = newSinUB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      cosLB = newCosLB, sinLB = newSinLB;
    } else {
      cosUB = newCosUB, sinLB = newSinLB;
    }
  } else {
    if (0.0<=sinpiK && 0.0<=cospiK) {
      cosUB = newCosUB, sinLB = newSinLB;
    } else if (0.0<=sinpiK && cospiK<0.0) {
      cosLB = newCosLB, sinLB = newSinLB;
    } else if (sinpiK<0.0 && 0.0<=cospiK) {
      cosUB = newCosUB, sinUB = newSinUB;
    } else {
      cosLB = newCosLB, sinUB = newSinUB;
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

