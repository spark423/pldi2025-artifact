#include "mathhelper.h"

double ourlibm_coshf_rz(float x) {
  float_x fx;
  fx.f = x;
  fx.x &= 0x7fffffff;
  
  // Take care of special cases
  if (fx.x <= 0x39ffffff) {
    if (fx.x == 0) return 1.0;
    if (fx.x <= 0x39b504f3) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  
  if (fx.x >= 0x42b2d4fd) {
      if (fx.x > 0x7f800000) return 0.0/0.0;
      if (fx.x == 0x7f800000) return 1.0 / 0.0;
      return 0x1.ffffff8p+127;
  }

  double n_int = __builtin_trunc((double)fx.f * CONST64BYLN2);
  double_x NX = {.d = 0x1p52 + n_int};
  int N = (int)NX.x; 
  int N2 = N&0x3f;
  int N1 = N - N2;
  int I = N1 >> 6; 
  double sinhH = sinhKLn2[I];
  double coshH = coshKLn2[I];
  double sinhM = sinhKLn2By64[N2];
  double coshM = coshKLn2By64[N2];  
  double sinhHM = rz_add(rz_multiply(sinhH, coshM), rz_multiply(coshH, sinhM));
  double coshHM = rz_add(rz_multiply(sinhH, sinhM), rz_multiply(coshH, coshM));
  
  double R = __builtin_fma(-n_int, LN2BY64, fx.f);
  double R2 = rz_multiply(R, R);

  //y=0x1.0000000000068p+0 x^(1) + 0x1.55555528fdcdfp-3 x^(3) + 0x1.116bdfa3eebf6p-7 x^(5)
  double sinhL = rz_add(rz_multiply(R2, 0x1.116bdfa3eebf6p-7), 0x1.55555528fdcdfp-3);
  sinhL = rz_multiply(R, rz_add(rz_multiply(sinhL, R2), 0x1.0000000000068p+0));
  //y=0x1.0000000000002p+0 x^(0) + 0x1.fffffffdb8028p-2 x^(2) + 0x1.55585b7066e88p-5 x^(4)
  double coshL = rz_add(rz_multiply(R2, 0x1.55585b7066e88p-5), 0x1.fffffffdb8028p-2);
  coshL = rz_add(rz_multiply(coshL, R2), 0x1.0000000000002p+0);
  
  return rz_add(rz_multiply(sinhHM, sinhL), rz_multiply(coshHM, coshL));
}
