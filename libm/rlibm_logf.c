#include "libm.h"

double rlibm_logf(float x) {
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
  m+= fix.x >> 23;
  m -= 127;
  fix.x &= 0x007fffff;
  fix.x |= 0x3f800000;
  float_x fit = {.x = fix.x & 0x007f0000};
  int FIndex = fit.x >> 16;
  fit.x |= 0x3f800000;
  double f = fix.f - fit.f;
  f = f*oneByF[FIndex];
  double y;
  if (__builtin_expect(f == 0x1.7096969696969p-11, 0)) y = 0x1.70756ba1d408p-11;
  else if (__builtin_expect(f == 0x1.67f6db6db6db7p-10, 0)) y = 0x1.67b7baa100bp-10;
  else if (__builtin_expect(f == 0x1.d6f7e432f7e42p-10, 0)) y = 0x1.d68bcd95e5eep-10;
  else if (__builtin_expect(f == 0x1.f96p-10, 0)) y = 0x1.f8e3733e3bp-10;
  else if (__builtin_expect(f == 0x1.23624dd2f1a9fp-9, 0)) y = 0x1.230f838d1d24p-9;
  else if (__builtin_expect(f == 0x1.57497b425ed09p-9, 0)) y = 0x1.56d69b075fdcp-9;
  else if (__builtin_expect(f == 0x1.bab0df6b0df6bp-9, 0)) y = 0x1.b9f1e6d90cp-9;
  else if (__builtin_expect(f == 0x1.e8a1fd1b7af01p-9, 0)) y = 0x1.e7b96dc4a088p-9;
  else if (__builtin_expect(f == 0x1.3155555555555p-8, 0)) y = 0x1.309fcf6bbd106p-8;
  else if (__builtin_expect(f == 0x1.740a7ac29eb0ap-8, 0)) y = 0x1.72fd18f1eff5p-8;
  else if (__builtin_expect(f == 0x1.a486d6f63aa04p-8, 0)) y = 0x1.a32ee974a95cbp-8;
  else if (__builtin_expect(f == 0x1.d5ca1af286bcap-8, 0)) y = 0x1.d41d15b578e86p-8;
  else if (__builtin_expect(f == 0x1.d88cb3c9484e2p-8, 0)) y = 0x1.d6daa602bf9cbp-8;
  else {
    //0x1.7096969696969p-11, 0x1.67f6db6db6db7p-10, 0x1.d6f7e432f7e42p-10, 0x1.f96p-10, 0x1.23624dd2f1a9fp-9, 0x1.57497b425ed09p-9, 0x1.bab0df6b0df6bp-9, 0x1.e8a1fd1b7af01p-9, 0x1.3155555555555p-8, 0x1.740a7ac29eb0ap-8, 0x1.a486d6f63aa04p-8, 0x1.d5ca1af286bcap-8, 0x1.d88cb3c9484e2p-8                                                                  
    //y=0x1.fffffffffffd6p-1 x^(1) + -0x1.ffffffff9c26fp-2 x^(2) + 0x1.5555705097a9fp-2 x^(3) + -0x1.00564f869484fp-2 x^(4) + 0x1.1b779fd0fecc3p-2 x^(5) + -0x1.5a809eb729701p+2 x^(6)
    static double coeffs[] = {0x1.fffffffffffd6p-1, -0x1.ffffffff9c26fp-2, 0x1.5555705097a9fp-2, -0x1.00564f869484fp-2, 0x1.1b779fd0fecc3p-2, -0x1.5a809eb729701p+2};
    double f2 = f*f;
    double f4 = f2*f2;  
    double tmp1 = coeffs[1]*f+coeffs[0];
    double tmp2 = coeffs[3]*f+coeffs[2];
    double tmp3 = coeffs[5]*f+coeffs[4];
    double tmp4 = tmp2*f2+tmp1;
    double tmp5 = tmp3*f4+tmp4;
    y = f*tmp5;
  }
  double extra = lnF[FIndex]+m*LN2;
  y += extra;
  return y;
}
