#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "interval-gen/IntervalGen.h"

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

bool ComputeSpecialCase(float x) {
  float_x fx = {.f=x};
  if (fx.f == 0.0) {
    return true;
  } else if (fx.x == 0x7F800000) {
    return true;
  } else if (fx.x > 0x7F800000) {
    fx.x = 0x7FFFFFFF;
    return true;
   }
  int exp;
  float remainder = frexpf(x, &exp);
  if (remainder == 0.5 || remainder == -0.5) return true;
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
  return log1p(xp)*ONEBYLN2;
}

double OutputCompensation(float x, double yp, bool useFMA) {  
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
  double extra = logBase2[FIndex]+m;
  return yp+extra;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: %s <Name of the Interval File> <Name of the Failed Input File> <Oracle File>\n", argv[0]);
    exit(0);
  }
  fesetround(rnd);
  CreateIntervalFile(argv[1], argv[2], argv[3], 0x3f800000, 0x40000000, multi);
  return 0;
}

