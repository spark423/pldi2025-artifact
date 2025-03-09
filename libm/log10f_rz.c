#include "mathhelper.h"

double ourlibm_log10f_rz(float x) {
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
  double f = fix.f - fit.f;
  f = rz_multiply(f, oneByF[FIndex]);
  double f2 = rz_multiply(f, f);
  double y = 0.0;
  if(f < 0x1.5ac30c30c30c2p-9) {
    if (__builtin_expect(f == 0x1.a17982f305e6p-11, 0)) y = 0x1.6a784ede377e9p-12;
    else if (__builtin_expect(f == 0x1.8027f6027f602p-10, 0)) y = 0x1.4d6de75f6cdd5p-11;
    else if (__builtin_expect(f == 0x1.b2ce38e38e38dp-10, 0)) y = 0x1.795ac8e55e169p-11;
    else if (__builtin_expect(f == 0x1.1fddb0d3224f2p-9, 0)) y = 0x1.f386a179401e2p-11;
    else if(f < 0x1.5abffffffffffp-10) {
      //0x1.a17982f305e6p-11
      //y=0x1.bcb7b1527ceccp-2 x^(1) + -0x1.bcb7b1b949169p-3 x^(2) + 0x1.28776aaea8942p-3 x^(3) + -0x1.a7acff226b581p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b1527ceccp-2, -0x1.bcb7b1b949169p-3, 0x1.28776aaea8942p-3, -0x1.a7acff226b581p-4};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    } else {
      //0x1.8027f6027f602p-10, 0x1.b2ce38e38e38dp-10, 0x1.1fddb0d3224f2p-9
      //y=0x1.bcb7b1515a119p-2 x^(1) + -0x1.bcb7a3c9a62c8p-3 x^(2) + 0x1.285ec2ca15fa9p-3 x^(3) + -0x1.96f602d3ab6p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b1515a119p-2, -0x1.bcb7a3c9a62c8p-3, 0x1.285ec2ca15fa9p-3, -0x1.96f602d3ab6p-4};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    }
  } else {
    if (__builtin_expect(f == 0x1.8abe0f83e0f83p-9, 0)) y = 0x1.565a8ca764384p-10;
    else if (__builtin_expect(f == 0x1.bde34a2b10bf5p-9, 0)) y = 0x1.82a2d2e7aa461p-10;
    else if (__builtin_expect(f == 0x1.e0b56ad5ab56ap-9, 0)) y = 0x1.a0c6415933p-10;
    else if (__builtin_expect(f == 0x1.f95306eb3e452p-9, 0)) y = 0x1.b6133cb3ccaaap-10;
    else if (__builtin_expect(f == 0x1.fdf239662b9f8p-9, 0)) y = 0x1.ba12f06b7a7b4p-10;
    else if(f < 0x1.038e9aa180dbep-8) {
      //0x1.8abe0f83e0f83p-9, 0x1.bde34a2b10bf5p-9, 0x1.e0b56ad5ab56ap-9, 0x1.f95306eb3e452p-9, 0x1.fdf239662b9f8p-9
      //y=0x1.bcb7b150b1d89p-2 x^(1) + -0x1.bcb7a564bd679p-3 x^(2) + 0x1.286c46418d0b3p-3 x^(3) + -0x1.afde4216b68c9p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b150b1d89p-2, -0x1.bcb7a564bd679p-3, 0x1.286c46418d0b3p-3, -0x1.afde4216b68c9p-4};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    } else {
      //y=0x1.bcb7b150f58afp-2 x^(1) + -0x1.bcb7a900247fbp-3 x^(2) + 0x1.2871be7639e6ap-3 x^(3) + -0x1.b4abed1000d48p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b150f58afp-2, -0x1.bcb7a900247fbp-3, 0x1.2871be7639e6ap-3, -0x1.b4abed1000d48p-4};
      double tmp1 = rz_multiply(coeffs[1], f);
      double tmp2 = rz_multiply(coeffs[3], f);
      double tmp3 = rz_add(tmp1, coeffs[0]);
      double tmp4 = rz_add(tmp2, coeffs[2]);
      double tmp5 = rz_multiply(tmp4, f2);
      double tmp6 = rz_add(tmp3, tmp5);
      y = rz_multiply(tmp6, f);
    }
  }
  double extra1 = rz_multiply(m, LOG102LOW);
  double extra2 = rz_multiply(m, LOG102HIGH);
  y = rz_add(y, extra1);
  y = rz_add(y, log10F[FIndex]);
  y = rz_add(y, extra2);
  return y;
}
