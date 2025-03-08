#include "mathhelper.h"

double rlibm_logf(float x) {
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
    else if (__builtin_expect(f == 0x1.44d9889f2bc59p-10, 0)) y = 0x1.44a61cf3624p-10;
    else if (__builtin_expect(f == 0x1.67f6db6db6db6p-10, 0)) y = 0x1.67b7baa103ap-10;
    else if (__builtin_expect(f == 0x1.d6f7e432f7e42p-10, 0)) y = 0x1.d68bcd95e8ecp-10;
    else if (__builtin_expect(f == 0x1.e024242424242p-10, 0)) y = 0x1.dfb3b75622ep-10;
    else if (__builtin_expect(f == 0x1.ebdfbf7efdfbfp-10, 0)) y = 0x1.eb69c4c46f4p-10;
    else if (__builtin_expect(f == 0x1.fbd2361d2361cp-10, 0)) y = 0x1.fb547e6083efp-10;
    else if (__builtin_expect(f == 0x1.046d2d2d2d2d2p-9, 0)) y = 0x1.042b0b7b8cep-9;
    else if (__builtin_expect(f == 0x1.1f7a3bf6c657ap-9, 0)) y = 0x1.1f29a739d606p-9;
    else if (__builtin_expect(f == 0x1.23624dd2f1a9ep-9, 0)) y = 0x1.230f838d1e2p-9;
    else if (__builtin_expect(f == 0x1.3c7476a933a3bp-9, 0)) y = 0x1.3c12d8baf7efp-9;
    else if (__builtin_expect(f == 0x1.4d3dafcea68ddp-9, 0)) y = 0x1.4cd16dd4fcb8p-9;
    else if (__builtin_expect(f == 0x1.501ee58469ee5p-9, 0)) y = 0x1.4fb0be108189p-9;
    else if (__builtin_expect(f == 0x1.57497b425ed09p-9, 0)) y = 0x1.56d69b0762d8p-9;
    else if (__builtin_expect(f == 0x1.6ab366cd9b366p-9, 0)) y = 0x1.6a332a6237ap-9;
    else {
      //0x1.7096969696969p-11, 0x1.a701460cbc7f5p-11, 0x1.44d9889f2bc59p-10, 0x1.67f6db6db6db6p-10, 0x1.d6f7e432f7e42p-10, 0x1.e024242424242p-10, 0x1.ebdfbf7efdfbfp-10, 0x1.fbd2361d2361cp-10, 0x1.046d2d2d2d2d2p-9, 0x1.1f7a3bf6c657ap-9, 0x1.23624dd2f1a9ep-9, 0x1.3c7476a933a3bp-9, 0x1.4d3dafcea68ddp-9, 0x1.501ee58469ee5p-9, 0x1.57497b425ed09p-9, 0x1.6ab366cd9b366p-9
      //y=0x1.fffffffffffcap-1 x^(1) + -0x1.ffffff241b33p-2 x^(2) + 0x1.5551723e5b1abp-2 x^(3) + -0x1.f72aac73e0f21p-3 x^(4)
      double coeffs[4] = {0x1.fffffffffffcap-1, -0x1.ffffff241b33p-2, 0x1.5551723e5b1abp-2, -0x1.f72aac73e0f21p-3};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      y = f*(f2*tmp2+tmp1);
    }
  } else {
    if (__builtin_expect(f == 0x1.78d3dcb08d3dcp-9, 0)) y = 0x1.784971c31ap-9;
    else if (__builtin_expect(f == 0x1.7b4a2b10bf66dp-9, 0)) y = 0x1.7abdf7f04bcp-9;
    else if (__builtin_expect(f == 0x1.925aaaaaaaaaap-9, 0)) y = 0x1.91bce873354p-9;
    else if (__builtin_expect(f == 0x1.bab0df6b0df6ap-9, 0)) y = 0x1.b9f1e377228p-9;
    else if (__builtin_expect(f == 0x1.be41a41a41a41p-9, 0)) y = 0x1.bd7f9366fa9ap-9;
    else if (__builtin_expect(f == 0x1.e05c28f5c28f4p-9, 0)) y = 0x1.df7b5dbccab04p-9;
    else if (__builtin_expect(f == 0x1.e7fc9bf937f26p-9, 0)) y = 0x1.e7149a6021ap-9;
    else if (__builtin_expect(f == 0x1.e8a1fd1b7af01p-9, 0)) y = 0x1.e7b96dc4a68p-9;
    else if (__builtin_expect(f == 0x1.05c77b03531dep-8, 0)) y = 0x1.0541fcd618f8p-8;
    else if (__builtin_expect(f == 0x1.1d085fb37072dp-8, 0)) y = 0x1.1c6a2ae3645p-8;
    else if (__builtin_expect(f == 0x1.3155555555555p-8, 0)) y = 0x1.309fd01ef7p-8;
    else if (__builtin_expect(f == 0x1.4e512bb512bb4p-8, 0)) y = 0x1.4d779e86d6d4p-8;
    else if (__builtin_expect(f == 0x1.710edd50edd5p-8, 0)) y = 0x1.7005de2a778p-8;
    else if (__builtin_expect(f == 0x1.9c0a2c145828bp-8, 0)) y = 0x1.9abff691ef8p-8;
    else if (__builtin_expect(f == 0x1.d5ca1af286bc9p-8, 0)) y = 0x1.d41d15b578288p-8;
    else {
      //0x1.78d3dcb08d3dcp-9, 0x1.7b4a2b10bf66dp-9, 0x1.925aaaaaaaaaap-9, 0x1.bab0df6b0df6ap-9, 0x1.be41a41a41a41p-9, 0x1.e05c28f5c28f4p-9, 0x1.e7fc9bf937f26p-9, 0x1.e8a1fd1b7af01p-9, 0x1.05c77b03531dep-8, 0x1.1d085fb37072dp-8, 0x1.3155555555555p-8, 0x1.4e512bb512bb4p-8, 0x1.710edd50edd5p-8, 0x1.9c0a2c145828bp-8, 0x1.d5ca1af286bc9p-8
      //y=0x1.fffffffecb4cep-1 x^(1) + -0x1.fffff8488ac4ap-2 x^(2) + 0x1.554c63a959817p-2 x^(3) + -0x1.f72044e45128p-3 x^(4)
      double coeffs[4] = {0x1.fffffffecb4cep-1, -0x1.fffff8488ac4ap-2, 0x1.554c63a959817p-2, -0x1.f72044e45128p-3};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      y = f*(f2*tmp2+tmp1);
    }
  }
  double extra = m*LN2+lnF[FIndex]; 
  return y+extra;
}
