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

#ifdef FMA
  bool useFMA = true;
#else
  bool useFMA = false;
#endif

bool ComputeSpecialCase(float x) {
  float_x fx = {.f=x};
  if((fx.x & 0x7fffffff) == 0) return true;
  if(fx.x <= 0x3438aa3a) return true;
  if(fx.x >= 0x43000000 && fx.x <= 0xb3b8aa3b) return true;
  if(fx.x >= 0xc3160001) return true;
  double xp = x * 64;
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = x-N*0x1p-6;
  if(R == 0.0 && N2 == 0) return true;
  return false;
}

double RangeReduction(float x) {
  double xp = x * 64;
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = x - N*0x1p-6;
  return R;
}

double GuessInitialVal(double xp) {
  return exp2(xp);
}

double OutputCompensation(float x, double yp, bool useFMA) {
  double xp = x*64;
  int N = (int)xp;
  int N2 = N%64;
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

