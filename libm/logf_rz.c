#include "mathhelper.h"

double rlibm_logf_rz(float x) {
  float_x fix = {.f=x};
  int m = 0;
  if (__builtin_expect(x == 1.0, 0)) return 0.0;
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
  f = rz_multiply(f, oneByF[FIndex]);  
  double f2 = rz_multiply(f, f);
  double y = 0.0;
  if(f < 0x1.789107b0e4883p-9) {
    if (__builtin_expect(f == 0x1p-23, 0)) y = 0x1.fffffe8p-24;
    else if (__builtin_expect(f == 0x1.7096969696969p-11, 0)) y = 0x1.70756ba1d21p-11;
    else if (__builtin_expect(f == 0x1.67f6db6db6db6p-10, 0)) y = 0x1.67b7baa103ap-10;
    else if (__builtin_expect(f == 0x1.d6f7e432f7e42p-10, 0)) y = 0x1.d68bcd95e8ecp-10;
    else if (__builtin_expect(f == 0x1.129745d1745d1p-9, 0)) y = 0x1.124dbb69db408p-9;
    else if (__builtin_expect(f == 0x1.1f7a3bf6c657ap-9, 0)) y = 0x1.1f29a739d606p-9;
    else if (__builtin_expect(f == 0x1.3c7476a933a3bp-9, 0)) y = 0x1.3c12d8baf7efp-9;
    else if (__builtin_expect(f == 0x1.4f89898989898p-9, 0)) y = 0x1.4f1bc6eb117p-9;
    else if (__builtin_expect(f == 0x1.57497b425ed09p-9, 0)) y = 0x1.56d69b0762d8p-9;
    else if (__builtin_expect(f == 0x1.6ab366cd9b366p-9, 0)) y = 0x1.6a332a6237ap-9;
    else {
      //0x1p-23, 0x1.7096969696969p-11, 0x1.67f6db6db6db6p-10, 0x1.d6f7e432f7e42p-10, 0x1.129745d1745d1p-9, 0x1.1f7a3bf6c657ap-9, 0x1.3c7476a933a3bp-9, 0x1.4f89898989898p-9, 0x1.57497b425ed09p-9, 0x1.6ab366cd9b366p-9
      //y=0x1.fffffffffff4fp-1 x^(1) + -0x1.ffffffbae9d89p-2 x^(2) + 0x1.5553d4c14ee25p-2 x^(3) + -0x1.fb859fd17f8ecp-3 x^(4)
      double coeffs[4] = {0x1.fffffffffff4fp-1, -0x1.ffffffbae9d89p-2, 0x1.5553d4c14ee25p-2, -0x1.fb859fd17f8ecp-3};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    }
  } else {
    if (__builtin_expect(f == 0x1.78d3dcb08d3dcp-9, 0)) y = 0x1.784971c314p-9;
    else if (__builtin_expect(f == 0x1.7b4a2b10bf66dp-9, 0)) y = 0x1.7abdf7f04bcp-9;
    else if (__builtin_expect(f == 0x1.bab0df6b0df6ap-9, 0)) y = 0x1.b9f1e37721p-9;
    else if (__builtin_expect(f == 0x1.be41a41a41a41p-9, 0)) y = 0x1.bd7f9366fa9ap-9;
    else if (__builtin_expect(f == 0x1.e05c28f5c28f4p-9, 0)) y = 0x1.df7b5dbccabp-9;
    else if (__builtin_expect(f == 0x1.e8a1fd1b7af01p-9, 0)) y = 0x1.e7b96dc4a69p-9;
    else if (__builtin_expect(f == 0x1.1d085fb37072dp-8, 0)) y = 0x1.1c6a2ae3645p-8;
    else if (__builtin_expect(f == 0x1.3155555555555p-8, 0)) y = 0x1.309fd01ef88p-8;
    else if (__builtin_expect(f == 0x1.4e512bb512bb4p-8, 0)) y = 0x1.4d779e86d792p-8;
    else if (__builtin_expect(f == 0x1.9c0a2c145828bp-8, 0)) y = 0x1.9abff691ef8p-8;
    else if (__builtin_expect(f == 0x1.d5ca1af286bc9p-8, 0)) y = 0x1.d41d15b579a88p-8;
    else {
      //0x1.78d3dcb08d3dcp-9, 0x1.7b4a2b10bf66dp-9, 0x1.bab0df6b0df6ap-9, 0x1.be41a41a41a41p-9, 0x1.e05c28f5c28f4p-9, 0x1.e8a1fd1b7af01p-9, 0x1.1d085fb37072dp-8, 0x1.3155555555555p-8, 0x1.4e512bb512bb4p-8, 0x1.9c0a2c145828bp-8, 0x1.d5ca1af286bc9p-8
      //y=0x1.fffffffec9d08p-1 x^(1) + -0x1.fffff840b179p-2 x^(2) + 0x1.554c5d161b756p-2 x^(3) + -0x1.f71cde2468f32p-3 x^(4)
      double coeffs[4] = {0x1.fffffffec9d08p-1, -0x1.fffff840b179p-2, 0x1.554c5d161b756p-2, -0x1.f71cde2468f32p-3};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    }
  }
  double extra = rz_add(rz_multiply(m, LN2), lnF[FIndex]);
  return rz_add(y, extra);
}
