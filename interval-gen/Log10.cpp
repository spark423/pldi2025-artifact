#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "IntervalGen.h"

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

bool ComputeSpecialCase(float x) {
  float_x fx = {.f=x};
  if (fx.f == 0.0) {
    return true;
  } else if (fx.f == 1.0) {
    return true;
  } else if (fx.x >= 0x7F800000) {
    return true;
  } 
  switch (fx.x) {
    case 0x3f800000 : return true;
    case 0x41200000 : return true;
    case 0x42c80000 : return true;
    case 0x447a0000 : return true;
    case 0x461c4000 : return true;
    case 0x47c35000 : return true;
    case 0x49742400 : return true;
    case 0x4b189680 : return true;
    case 0x4cbebc20 : return true;
    case 0x4e6e6b28 : return true;
    case 0x501502f9 : return true;
  }
  return false;
}

double RangeReduction(float x) {
  float_x fix, fit;
  int m = 0;
  fix.f = x;
  if(fix.x < 0x800000) {
    fix.f *= 8388608.0;
    m-=23;
  }
  m+=fix.x>>23;
  m-=127;
  fix.x &= 0x007FFFFF;
  fix.x |= 0x3F800000;
  fit.x = fix.x & 0x007F0000;
  int FIndex = fit.x >> 16;
  fit.x |= 0x3F800000;
  double F = fit.f;
  double f = fix.f-F;
  return f*oneByF[FIndex];
}

double GuessInitialVal(double xp) {
  return log10(1.0+xp);
}

double OutputCompensationFMA(float x, double yp) {
  float_x fix, fit;
  int m = 0;
  fix.f = x;
  if(fix.x < 0x800000) {
    fix.f *= 8388608.0;
    m-=23;
  }
  m+=fix.x>>23;
  m-=127;
  fix.x &= 0x007FFFFF;
  fix.x |= 0x3F800000;
  fit.x = fix.x & 0x007F0000;
  int FIndex = fit.x >> 16;
  yp = __builtin_fma(m, LOG102LOW, yp);
  double extra = __builtin_fma(m, LOG102HIGH, log10F[FIndex]);
  return yp+extra;
}

double OutputCompensation(float x, double yp, bool useFMA) {
  if (useFMA) return OutputCompensationFMA(x, yp);
  float_x fix, fit;
  int m = 0;
  fix.f = x;
  if(fix.x < 0x800000) {
    fix.f *= 8388608.0;
    m-=23;
  }
  m+=fix.x>>23;
  m-=127;
  fix.x &= 0x007FFFFF;
  fix.x |= 0x3F800000;
  fit.x = fix.x & 0x007F0000;
  int FIndex = fit.x >> 16;	
  yp += m*LOG102LOW; 
  yp += log10F[FIndex];
  yp += m*LOG102HIGH;
  return yp;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: %s <Name of the Interval File> <Name of the Failed Input File> <Oracle File>\n", argv[0]);
    exit(0);
  }
  fesetround(rnd);
  CreateIntervalFile(argv[1], argv[2], argv[3], 0x0, 0x80000000, multi, useFMA);
  return 0;
}

