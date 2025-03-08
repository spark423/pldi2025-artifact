#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "IntervalGen.h"
#include "constants.h"

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
  if((fx.x & 0x7FFFFFFF) == 0) return true;
  if(fx.x <= 0x335E5BD7) return true;
  if(fx.x >= 0x421A209B && fx.x <= 0xB2DE5BD9) return true;
  if(fx.x >= 0xC2349E36) return true;
  switch(fx.x) {
    case 0x00000000: return true; // 1.0
    case 0x80000000: return true; // 1.0
    case 0x3f800000: return true; // 10.0
    case 0x40000000: return true; // 100.0
    case 0x40400000: return true; // 1000.0
    case 0x40800000: return true; // 10000.0
    case 0x40a00000: return true; // 100000.0
    case 0x40c00000: return true; // 1000000.0
    case 0x40e00000: return true; // 10000000.0
    case 0x41000000: return true; // 100000000.0
    case 0x41100000: return true; // 1000000000.0
    case 0x41200000: return true; // 10000000000.0
  }
  return false;
}

double RangeReduction(float x) {
  double xp = x * LG10X64;
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = __builtin_fma(-N,ONEBY64LG10,x);
  return R;
}

double GuessInitialVal(double xp) {
  return exp10(xp);
}

double OutputCompensation(float x, double yp, bool useFMA) {
  double xp = x * LG10X64;
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double_x dY = {.d=exp2JBy64[J]};
  dY.x += ((uint64_t)M<<52);
  yp *= dY.d;
  return yp;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: %s <Name of the Interval File> <Name of the Failed Input File> <Oracle File>\n", argv[0]);
    exit(0);
  }
  fesetround(rnd);
  CreateIntervalFile(argv[1], argv[2], argv[3], 0x0, 0x100000000, multi, useFMA);
  return 0;
}

