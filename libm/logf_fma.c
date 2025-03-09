#include "mathhelper.h"

double ourlibm_logf_fma(float x) {
  float_x fix = {.f=x};
  int m = 0;
  if (__builtin_expect(x == 1.0, 0)) return 0.0;
  if (fix.x < 0x800000 || fix.x >= 0x7F800000) {
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
  f = rz_multiply(f, oneByF[FIndex]); 
  double f2 = f*f;
  double y = 0.0;
  if (f < 0x1.789107b0e4883p-9) {
    if (__builtin_expect(f == 0x1.7096969696969p-11, 0)) y = 0x1.70756ba1d21p-11;
    else if (__builtin_expect(f == 0x1.a701460cbc7f5p-11, 0)) y = 0x1.a6d575462f38p-11;
    else if (__builtin_expect(f == 0x1.44d9889f2bc59p-10, 0)) y = 0x1.44a61cf362p-10;
    else if (__builtin_expect(f == 0x1.67f6db6db6db6p-10, 0)) y = 0x1.67b7baa101ap-10;
    else if (__builtin_expect(f == 0x1.d6f7e432f7e42p-10, 0)) y = 0x1.d68bcd95e8ecp-10;
    else if (__builtin_expect(f == 0x1.f96p-10, 0)) y = 0x1.f8e3733e3ap-10;
    else if (__builtin_expect(f == 0x1.fbd2361d2361cp-10, 0)) y = 0x1.fb547e607fefp-10;
    else if (__builtin_expect(f == 0x1.046d2d2d2d2d2p-9, 0)) y = 0x1.042b0b7b8aep-9;
    else if (__builtin_expect(f == 0x1.129745d1745d1p-9, 0)) y = 0x1.124dbb69db408p-9;
    else if (__builtin_expect(f == 0x1.1f7a3bf6c657ap-9, 0)) y = 0x1.1f29a739d406p-9;
    else if (__builtin_expect(f == 0x1.23624dd2f1a9ep-9, 0)) y = 0x1.230f838d1e2p-9;
    else if (__builtin_expect(f == 0x1.4f89898989898p-9, 0)) y = 0x1.4f1bc6eb117p-9;
    else if (__builtin_expect(f == 0x1.501ee58469ee5p-9, 0)) y = 0x1.4fb0be108189p-9;
    else if (__builtin_expect(f == 0x1.57497b425ed09p-9, 0)) y = 0x1.56d69b0762d8p-9;
    else if (__builtin_expect(f == 0x1.6ab366cd9b366p-9, 0)) y = 0x1.6a332a6237ap-9;
    else {
      //0x1.7096969696969p-11, 0x1.a701460cbc7f5p-11, 0x1.44d9889f2bc59p-10, 0x1.67f6db6db6db6p-10, 0x1.d6f7e432f7e42p-10, 0x1.f96p-10, 0x1.fbd2361d2361cp-10, 0x1.046d2d2d2d2d2p-9, 0x1.129745d1745d1p-9, 0x1.1f7a3bf6c657ap-9, 0x1.23624dd2f1a9ep-9, 0x1.4f89898989898p-9, 0x1.501ee58469ee5p-9, 0x1.57497b425ed09p-9, 0x1.6ab366cd9b366p-9
      //y=0x1.fffffffffffdp-1 x^(1) + -0x1.ffffff8f12378p-2 x^(2) + 0x1.55533be5787d9p-2 x^(3) + -0x1.fa864df94a72bp-3 x^(4)
      double coeffs[4] = {0x1.fffffffffffdp-1, -0x1.ffffff8f12378p-2, 0x1.55533be5787d9p-2, -0x1.fa864df94a72bp-3};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      y = f*__builtin_fma(f2, tmp2, tmp1);
    }
  } else {
    if (__builtin_expect(f == 0x1.78d3dcb08d3dcp-9, 0)) y = 0x1.784971c31ap-9;
    else if (__builtin_expect(f == 0x1.7b4a2b10bf66dp-9, 0)) y = 0x1.7abdf7f04bcp-9;
    else if (__builtin_expect(f == 0x1.bab0df6b0df6ap-9, 0)) y = 0x1.b9f1e37722p-9;
    else if (__builtin_expect(f == 0x1.be41a41a41a41p-9, 0)) y = 0x1.bd7f9366fe9ap-9;
    else if (__builtin_expect(f == 0x1.e05c28f5c28f4p-9, 0)) y = 0x1.df7b5dbcceb04p-9;
    else if (__builtin_expect(f == 0x1.e7fc9bf937f26p-9, 0)) y = 0x1.e7149a6021cp-9;
    else if (__builtin_expect(f == 0x1.e8a1fd1b7af01p-9, 0)) y = 0x1.e7b96dc4a28p-9;
    else if (__builtin_expect(f == 0x1.05c77b03531dep-8, 0)) y = 0x1.0541fcd618f8p-8;
    else if (__builtin_expect(f == 0x1.3155555555555p-8, 0)) y = 0x1.309fd01ef7p-8;
    else if (__builtin_expect(f == 0x1.740a7ac29eb0ap-8, 0)) y = 0x1.72fd18f1f074p-8;
    else if (__builtin_expect(f == 0x1.a486d6f63aa03p-8, 0)) y = 0x1.a32ee974a9dcap-8;
    else if (__builtin_expect(f == 0x1.a6d8787878787p-8, 0)) y = 0x1.a57cb8257f3ep-8;
    else if (__builtin_expect(f == 0x1.d5ca1af286bc9p-8, 0)) y = 0x1.d41d15b578a88p-8;
    else if (__builtin_expect(f == 0x1.d88cb3c9484e2p-8, 0)) y = 0x1.d6daa602c05cap-8;
    else {
      //0x1.78d3dcb08d3dcp-9, 0x1.7b4a2b10bf66dp-9, 0x1.bab0df6b0df6ap-9, 0x1.be41a41a41a41p-9, 0x1.e05c28f5c28f4p-9, 0x1.e7fc9bf937f26p-9, 0x1.e8a1fd1b7af01p-9, 0x1.05c77b03531dep-8, 0x1.3155555555555p-8, 0x1.740a7ac29eb0ap-8, 0x1.a486d6f63aa03p-8, 0x1.a6d8787878787p-8, 0x1.d5ca1af286bc9p-8, 0x1.d88cb3c9484e2p-8
      //y=0x1.ffffffff406ffp-1 x^(1) + -0x1.fffffaaab4ccep-2 x^(2) + 0x1.554e5f93d509p-2 x^(3) + -0x1.f828641cca14fp-3 x^(4)
      double coeffs[4] = {0x1.ffffffff406ffp-1, -0x1.fffffaaab4ccep-2, 0x1.554e5f93d509p-2, -0x1.f828641cca14fp-3};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      y = f*__builtin_fma(f2, tmp2, tmp1);
    }
  }
  double extra = __builtin_fma(m, LN2, lnF[FIndex]);
  return y+extra;
}
