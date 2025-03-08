#include "mathhelper.h"

//y=0x1.71547652bd04ep+0 x^(1) + -0x1.71547697769fcp-1 x^(2) + 0x1.ec719b9ca88efp-2 x^(3) + -0x1.7204d1b62d1e3p-2 x^(4) + 0x1.4f5cdeeca214ep-2 x^(5)
static double coeffs[] = {0x1.71547652bd04ep+0, -0x1.71547697769fcp-1, 0x1.ec719b9ca88efp-2, -0x1.7204d1b62d1e3p-2, 0x1.4f5cdeeca214ep-2};

double rlibm_log2f_rz(float x) {
  float_x fix = {.f=x};
  int m = 0;
  if (__builtin_expect(x == 1.0, 0)) return 0.0;
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
  f = rz_multiply(f, oneByF[FIndex]);
  double f2 = rz_multiply(f, f);
  double tmp1 = rz_add(rz_multiply(coeffs[4], f), coeffs[3]);
  double tmp2 = rz_add(rz_multiply(coeffs[2], f), coeffs[1]);
  double tmp3 = rz_add(rz_multiply(tmp1, f2), tmp2);
  double tmp4 = rz_multiply(tmp3, f2);
  double tmp5 = rz_multiply(coeffs[0], f);
  double y = rz_add(tmp4, tmp5);
  double extra = rz_add(logBase2[FIndex], m);
  return rz_add(y, extra);
}
