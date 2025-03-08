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
  float_x inp = {.f = x};
  uint32_t ux = inp.x;
  uint64_t m = ux & 0x7FFFFF;
  m = m << 29;
  int exp = (ux >> 23) - 127;
  if(__builtin_expect(ux < 0x800000 || ux >= 0x7F800000, 0)){
    if (ux==0||ux==(1u<<31)) return true;
    uint32_t inf_or_nan = ((ux>>23)&0xff) == 0xff, nan = inf_or_nan && (ux<<9);
    if (ux>>31 && !nan) return true;
    if (inf_or_nan) return true;
    int nz = __builtin_clzll(m);
    m <<= nz-11;
    m &= ~0ul>>12;
    exp = exp - (nz - 12);
  }
  if(__builtin_expect(!m, 0)) return true;
  return false;
}

double RangeReduction(float x) {
  float_x fx = {.f = x}, ft;
  if(fx.x < 0x800000) {
    fx.f *= 8388608.0;
  }
  fx.x &= 0x7FFFFF;
  int FIndex = fx.x>>16;
  ft.x = fx.x & 0x7F0000;
  fx.x |= 0x3F800000;
  ft.x |= 0x3F800000;
  double f = fx.f-ft.f;
  return f*oneByF[FIndex];
}

double GuessInitialVal(double xp) {
  return log1p(xp);
}

double OutputCompensationFMA(float x, double yp) {
  float_x fx = {.f = x};
  int m = 0;
  if (fx.x < 0x800000) {
    fx.f *= 8388608.0;
    m -= 23;
  }
  m += (fx.x >> 23);
  m -= 127;
  fx.x &= 0x7FFFFF;
  int FIndex = fx.x >> 16; 
  double extra = __builtin_fma(m, LN2, lnF[FIndex]);
  return yp + extra;
}

double OutputCompensation(float x, double yp, bool useFMA) {
  if (useFMA) return OutputCompensationFMA(x, yp); 
  float_x fx = {.f = x};
  int m = 0;
  if (fx.x < 0x800000) {
    fx.f *= 8388608.0;
    m -= 23;
  }
  m += (fx.x >> 23);
  m -= 127;
  fx.x &= 0x7FFFFF;
  int FIndex = fx.x >> 16; 
  double extra = m*LN2+lnF[FIndex];
  return yp + extra;
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

