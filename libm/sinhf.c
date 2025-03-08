#include "rlibm.h"

double rlibm_sinhf(float x) {
  float_x fx;
  fx.f = x;
  int s = fx.x>>31;
  double sgns[2] = {1.0, -1.0};
  fx.x &= 0x7fffffff;
 
  if (fx.x <= 0x39e89768) {
    if (x == 0.0) return x;
    double_x dX;
    dX.d = (double)x;
    long exp = (dX.x & 0x7FF0000000000000UL) >> 52UL;
    exp -= 1023L;
    long mantissaCount = exp + 149L;
    if (mantissaCount > 23) mantissaCount = 23;
    mantissaCount += 2L;
    unsigned long shiftAmount = (52L - mantissaCount);
    unsigned long sticky = 1UL << shiftAmount;
    dX.x |= sticky;
    return dX.d;
  }
  
  if (fx.x >= 0x42b2d4fd) {
    if (fx.x > 0x7f800000) return 0.0/0.0;
    if (fx.x == 0x7f800000) {
      if (x > 0.0f) return 1.0 / 0.0;
      else return -1.0f / 0.0;
    }

    if (x > 0.0f) return 0x1.ffffff8p+127;
    else return -0x1.ffffff8p+127;
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
  double sinhHM = sinhH*coshM+coshH*sinhM;
  double coshHM = sinhH*sinhM+coshH*coshM;
  
  double R = __builtin_fma(-n_int, LN2BY64, fx.f);
  double R2 = R*R;

  //y=0x1.ffffffffffffcp-1 x^(1) + 0x1.5555555685be8p-3 x^(3) + 0x1.11130857ba3b8p-7 x^(5)
  double sinhL = R2*0x1.11130857ba3b8p-7+0x1.5555555685be8p-3;
  sinhL = R*(sinhL*R2+0x1.ffffffffffffcp-1);
  double coshL;
  if (__builtin_expect(R == 0x1.d2fd8bccca2c4p-9, 0)) coshL = 0x1.00006a22acbp+0;
  else if (__builtin_expect(R == 0x1.28e70f8380c3fp-7, 0)) coshL = 0x1.0002b04387034p+0;
  else {
    // 0x1.d2fd8bccca2c4p-9, 0x1.28e70f8380c3fp-7
    // y=0x1.fffffffffffffp-1 x^(0) + 0x1.ffffffffcb529p-2 x^(2) + 0x1.5555e45cddbf5p-5 x^(4)
    coshL = R2*0x1.5555e45cddbf5p-5+0x1.ffffffffcb529p-2;
    coshL = coshL*R2+0x1.fffffffffffffp-1;
  }
  return (sinhHM*coshL+coshHM*sinhL)*sgns[s];
}
