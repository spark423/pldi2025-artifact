#include "rlibm.h"

double rlibm_sinhf_og(float x) {
  float_x fx;
  fx.f = x;
  unsigned long sign = (fx.x & 0x80000000) == 0 ? 0x0 : 0x8000000000000000;
  fx.x &= 0x7FFFFFFF;

  if (fx.x == 0) return x;
  
  // Take care of special cases
  if (fx.x <= 971544424) {
    double_x dX;
    dX.d = (double)fx.f;
    long exp = (dX.x & 0x7FF0000000000000UL) >> 52UL;
    exp -= 1023L;
    long mantissaCount = exp + 149L;
    if (mantissaCount > 23) mantissaCount = 23;
    mantissaCount += 2L;
    unsigned long shiftAmount = (52L - mantissaCount);
    unsigned long sticky = 1UL << shiftAmount;
    dX.x |= sticky;
    dX.x |= sign;
    return dX.d;
  }
  
  if (fx.x >= 1119016189) {
    if (fx.x > 0x7F800000) return 0.0/0.0;
    if (fx.x == 0x7F800000) {
      if (x > 0.0f) return 1.0 / 0.0;
      else return -1.0 / 0.0;
    }

    if (x > 0.0f) return 0x1.ffffff8p+127;
    else return -0x1.ffffff8p+127;
  }
  
  // Perform range reduction
  double xp = fx.f * CONST64BYLN2;
  int N = (int)xp;
  int N2 = N % 64;
  if (N2 < 0) N2 += 64;
  int N1 = N - N2;
  int I = N1 / 64;
  double R = fx.f - N * LN2BY64;
  double R2 = R * R;
  
  double sinhHigh = sinhKLn2[I];
  double coshHigh = coshKLn2[I];
  double sinhMid = sinhKLn2By64[N2];
  double coshMid = coshKLn2By64[N2];
  
  double sinhHM = sinhHigh * coshMid + coshHigh * sinhMid;
  double coshHM = sinhHigh * sinhMid + coshHigh * coshMid;
  
  // Compute sinh  and coshL component
  double sinhL;
  double coshL;
                           
  if(__builtin_expect(R == 0x1.113e28d466p-7, 0)){
    sinhL = 0x1.113ef7cf95d0cp-7;
    coshL = 0x1.000246c8ff9eep+0;
  }
  else {
    /* sinhL =0x1.ffffffffffffep-1 x^(1) + 0x1.55555554d50dap-3 x^(3) + 0x1.1111b01851046p-7 x^(5) */
    double temp1 = fma(R2,  0x1.1111b01851046p-7,0x1.55555554d50dap-3);
    double temp2 = fma(R2, temp1, 0x1.ffffffffffffep-1);
    sinhL = R * temp2;

    /* coshL =0x1p+0 x^(0) + 0x1.ffffffff997cp-2 x^(2) + 0x1.5555e5da9087ap-5 x^(4) */
    double temp3 = fma (R2, 0x1.5555e5da9087ap-5, 0x1.ffffffff997cp-2);
    coshL = fma(R2, temp3, 0x1p+0);    
  }

  // Perform output compensation
  double_x dX;
  dX.d = sinhHM * coshL + coshHM * sinhL;
  dX.x |= sign;
  return dX.d;
}
