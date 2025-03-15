#include "libm.h"

double rlibm_log10f(float x) {
  float_x fix = {.f=x};
  int m = 0;

  if(fix.x < 0x800000 || fix.x >= 0x7F800000) {
    if((fix.x & 0x7FFFFFFF) == 0) { // log(0)= -infty
      fix.x = 0xFF800000;
      return fix.f;
    }
    if(fix.x > 0x7FFFFFFF) { // log(negative) = NaN
      return (x-x)/0.0;
    }
    if(fix.x >= 0x7F800000) {// log(NaN)=NaN, log
      return x;
    }
    fix.f *= 8388608.0;
    m-=23;
  }
  switch (fix.x) {
    case 0x3f800000 : return 0.0;
    case 0x41200000 : return 1.0;
    case 0x42c80000 : return 2.0;
    case 0x447a0000 : return 3.0;
    case 0x461c4000 : return 4.0;
    case 0x47c35000 : return 5.0;
    case 0x49742400 : return 6.0;
    case 0x4b189680 : return 7.0;
    case 0x4cbebc20 : return 8.0;
    case 0x4e6e6b28 : return 9.0;
    case 0x501502f9 : return 10.0;
  }
  m+= fix.x >> 23;
  m -= 127;
  fix.x &= 0x007fffff;
  fix.x |= 0x3f800000;
  float_x fit = {.x = fix.x & 0x007f0000};
  int FIndex = fit.x >> 16;
  fit.x |= 0x3f800000;
  double f = fix.f - fit.f; // exact
  f = f*oneByF[FIndex];
  double y;
  if (__builtin_expect(f == 0x1.f1d1d1d1d1d1dp-10, 0)) y = 0x1.affd952fb39e6p-11;
  else if (__builtin_expect(f == 0x1.1fddb0d3224f3p-9, 0)) y = 0x1.f386a1793e162p-11;
  else if (__builtin_expect(f == 0x1.8ff099fc267fp-9, 0)) y = 0x1.5adab9d4248c1p-10;
  else if (__builtin_expect(f == 0x1.bde34a2b10bf6p-9, 0)) y = 0x1.82a2d2e7a8461p-10;
  else if (__builtin_expect(f == 0x1.e0b56ad5ab56bp-9, 0)) y = 0x1.a0c6415935fp-10;
  else if (__builtin_expect(f == 0x1.fdf239662b9f9p-9, 0)) y = 0x1.ba12f06b7a773p-10;
  else if (__builtin_expect(f == 0x1.2af84a062b2e4p-8, 0)) y = 0x1.031766776d10cp-9;
  else if (__builtin_expect(f == 0x1.2bec04fec04ffp-8, 0)) y = 0x1.03ea19944d2f8p-9;
  else if (__builtin_expect(f == 0x1.c7d4p-8, 0)) y = 0x1.8a8e84fde7fddp-9;
  else {
    //0x1.f1d1d1d1d1d1dp-10, 0x1.1fddb0d3224f3p-9, 0x1.8ff099fc267fp-9, 0x1.bde34a2b10bf6p-9, 0x1.e0b56ad5ab56bp-9, 0x1.fdf239662b9f9p-9, 0x1.2af84a062b2e4p-8, 0x1.2bec04fec04ffp-8, 0x1.c7d4p-8
    //y=0x1.bcb7b152655eep-2 x^(1) + -0x1.bcb7b0b181b6dp-3 x^(2) + 0x1.2878b16892c2ap-3 x^(3) + -0x1.b86234772a62dp-4 x^(4) + -0x1.047c46209eec9p-4 x^(5) + 0x1.f621787c74f64p+2 x^(6)
    static double coeffs[] = {0x1.bcb7b152655eep-2, -0x1.bcb7b0b181b6dp-3, 0x1.2878b16892c2ap-3, -0x1.b86234772a62dp-4, -0x1.047c46209eec9p-4, 0x1.f621787c74f64p+2};
    double f2 = f*f;
    double f4 = f2*f2; 
    double tmp1 = coeffs[1]*f+coeffs[0];
    double tmp2 = coeffs[3]*f+coeffs[2];
    double tmp3 = coeffs[5]*f+coeffs[4];
    double tmp4 = tmp2*f2+tmp1;
    double tmp5 = tmp3*f4+tmp4;
    y = f*tmp5;
  }
  y += m*LOG102LOW;
  y += log10F[FIndex];
  y += m*LOG102HIGH;
  return y;
}
