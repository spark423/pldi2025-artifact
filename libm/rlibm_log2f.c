#include "libm.h"

double rlibm_log2f(float x) {
  float_x fix = {.f=x};
  int m = 0;
  if(fix.x < 0x800000 || fix.x >= 0x7F800000) {
    if((fix.x & 0x7FFFFFFF) == 0) {
      fix.x = 0xFF800000;
      return fix.f;
    }
    if(fix.x > 0x7FFFFFFF) {
      return (x-x)/0.0;
    }
    if(fix.x >= 0x7F800000) {
      return x;
    }
    fix.f *= 8388608.0;
    m-=23;
  }
  m+= fix.x >> 23;
  m -= 127;
  fix.x &= 0x007fffff;
  fix.x |= 0x3f800000;
  float_x fit = {.x = fix.x & 0x007f0000};
  int FIndex = fit.x >> 16;
  fit.x |= 0x3f800000;
  double f = fix.f - fit.f;
  f = f*oneByF[FIndex];
  //y=0x1.71547652bd4e6p+0 x^(1) + -0x1.7154769b8f767p-1 x^(2) + 0x1.ec71a980667dp-2 x^(3) + -0x1.720d7c1b8807cp-2 x^(4) + 0x1.512e028fac533p-2 x^(5)
  static double coeffs[] = {0x1.71547652bd4e6p+0, -0x1.7154769b8f767p-1, 0x1.ec71a980667dp-2, -0x1.720d7c1b8807cp-2, 0x1.512e028fac533p-2};
  double f2 = f*f;
  double tmp1 = f*coeffs[2]+coeffs[1];
  double tmp2 = f*coeffs[4]+coeffs[3];
  double tmp3 = f2*tmp2+tmp1;
  double tmp4 = f2*tmp3;
  double tmp5 = f*coeffs[0];
  double y = tmp4+tmp5;
  double extra = logBase2[FIndex]+m;
  return y+extra;
}
