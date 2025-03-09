#include "mathhelper.h"

//y=0x1.71547652bd03ap+0 x^(1) + -0x1.7154769765806p-1 x^(2) + 0x1.ec719b5f3dbcfp-2 x^(3) + -0x1.7204a86330348p-2 x^(4) + 0x1.4f537b3462a72p-2 x^(5)
static double coeffs[] = {0x1.71547652bd03ap+0, -0x1.7154769765806p-1, 0x1.ec719b5f3dbcfp-2, -0x1.7204a86330348p-2, 0x1.4f537b3462a72p-2};

double ourlibm_log2f_fma(float x) {
  float_x fix = {.f=x};
  int m = 0;
  if (__builtin_expect(x == 1.0, 0)) return 0.0;
  if (fix.x < 0x800000 || fix.x >= 0x7F800000) {
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
  f = rz_multiply(f, oneByF[FIndex]);
  double f2 = f*f;
  double tmp1 = __builtin_fma(f, coeffs[4], coeffs[3]);
  double tmp2 = __builtin_fma(f, coeffs[2], coeffs[1]);
  double tmp3 = __builtin_fma(f2, tmp1, tmp2);
  double y = __builtin_fma(f2, tmp3, f*coeffs[0]);
  double extra = logBase2[FIndex]+m;
  return y+extra;
}
