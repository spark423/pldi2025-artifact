#include "mathhelper.h"

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
  double f = fix.f - fit.f;
  f = rz_multiply(f, oneByF[FIndex]);
  double f2 = f*f;
  double y = 0.0;
  if (f < 0x1.5ac30c30c30c2p-9) {
    if (__builtin_expect(f == 0x1.91a3971a3971ap-13, 0)) y = 0x1.5cd27e169342ap-14;
    else if (__builtin_expect(f == 0x1.cd28ac42fd9b7p-12, 0)) y = 0x1.90785e9e80d6p-13;
    else if (__builtin_expect(f == 0x1.a17982f305e6p-11, 0)) y = 0x1.6a784ede376e9p-12;
    else if (__builtin_expect(f == 0x1.38a8a8a8a8a8ap-10, 0)) y = 0x1.0f6900a29215ep-11;
    else if (__builtin_expect(f == 0x1.8027f6027f602p-10, 0)) y = 0x1.4d6de75f6cd55p-11;
    else if (__builtin_expect(f == 0x1.b2ce38e38e38dp-10, 0)) y = 0x1.795ac8e55e149p-11;
    else if (__builtin_expect(f == 0x1.14f05397829cbp-9, 0)) y = 0x1.e095991a1dc84p-11;
    else if (__builtin_expect(f == 0x1.1fddb0d3224f2p-9, 0)) y = 0x1.f386a17940162p-11;
    else if (__builtin_expect(f == 0x1.4a4ce6b41c54fp-9, 0)) y = 0x1.1e88cf68242aep-10;
    else if (f < 0x1.5abffffffffffp-10) {
      //0x1.91a3971a3971ap-13, 0x1.cd28ac42fd9b7p-12, 0x1.a17982f305e6p-11, 0x1.38a8a8a8a8a8ap-10
      //y=0x1.bcb7b1525a613p-2 x^(1) + -0x1.bcb7aec3ba13ap-3 x^(2) + 0x1.286ccb2210a36p-3 x^(3) + -0x1.8eb6a7e10116ep-4 x^(4) 
      double coeffs[4] = {0x1.bcb7b1525a613p-2, -0x1.bcb7aec3ba13ap-3, 0x1.286ccb2210a36p-3, -0x1.8eb6a7e10116ep-4};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    } else {
      //0x1.8027f6027f602p-10, 0x1.b2ce38e38e38dp-10, 0x1.14f05397829cbp-9, 0x1.1fddb0d3224f2p-9, 0x1.4a4ce6b41c54fp-9
      //y=0x1.bcb7b15166d7ap-2 x^(1) + -0x1.bcb7a45debdc6p-3 x^(2) + 0x1.285fd99ae5a13p-3 x^(3) + -0x1.984b80774fa36p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b15166d7ap-2, -0x1.bcb7a45debdc6p-3, 0x1.285fd99ae5a13p-3, -0x1.984b80774fa36p-4};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    }
  } else {
    if (__builtin_expect(f == 0x1.63875b37e875bp-9, 0)) y = 0x1.3463f286e5e88p-10;
    else if (__builtin_expect(f == 0x1.8ff099fc267fp-9, 0)) y = 0x1.5adab9d4238c9p-10;
    else if (__builtin_expect(f == 0x1.bde34a2b10bf5p-9, 0)) y = 0x1.82a2d2e7aa421p-10;
    else if (__builtin_expect(f == 0x1.c36p-9, 0)) y = 0x1.8762c48p-10;
    else if (__builtin_expect(f == 0x1.e09ee58469ee5p-9, 0)) y = 0x1.a0b2c8b1d8839p-10;
    else if (__builtin_expect(f == 0x1.e0b56ad5ab56ap-9, 0)) y = 0x1.a0c6415932f8p-10;
    else if (__builtin_expect(f == 0x1.f95306eb3e452p-9, 0)) y = 0x1.b6133cb3cca8ap-10;
    else if (__builtin_expect(f == 0x1.f9a147ae147acp-9, 0)) y = 0x1.b656e25b8fce6p-10;
    else if (__builtin_expect(f == 0x1.fbf5f5f5f5f5fp-9, 0)) y = 0x1.b85b3cbdd9cf4p-10;
    else if (__builtin_expect(f == 0x1.2959203cae758p-8, 0)) y = 0x1.01b06af117e9ap-9;
    else if (__builtin_expect(f == 0x1.29ee62a46756dp-8, 0)) y = 0x1.0231755f6b307p-9;
    else if (__builtin_expect(f == 0x1.2af84a062b2e3p-8, 0)) y = 0x1.031766776cb8cp-9;
    else if (__builtin_expect(f == 0x1.2bec04fec04fep-8, 0)) y = 0x1.03ea19944cbf8p-9;
    else if (f < 0x1.038e9aa180dbep-8) {
      //0x1.63875b37e875bp-9, 0x1.8ff099fc267fp-9, 0x1.bde34a2b10bf5p-9, 0x1.c36p-9, 0x1.e09ee58469ee5p-9, 0x1.e0b56ad5ab56ap-9, 0x1.f95306eb3e452p-9, 0x1.f9a147ae147acp-9, 0x1.fbf5f5f5f5f5fp-9
      //y=0x1.bcb7b14e835fp-2 x^(1) + -0x1.bcb795d0ffe64p-3 x^(2) + 0x1.2859fce980332p-3 x^(3) + -0x1.a1b9db4dc05eep-4 x^(4)
      double coeffs[4] = {0x1.bcb7b14e835fp-2, -0x1.bcb795d0ffe64p-3, 0x1.2859fce980332p-3, -0x1.a1b9db4dc05eep-4}; 
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    } else {
      //0x1.2959203cae758p-8, 0x1.29ee62a46756dp-8, 0x1.2af84a062b2e3p-8, 0x1.2bec04fec04fep-8
      //y=0x1.bcb7b151388b5p-2 x^(1) + -0x1.bcb7a9e0d54f3p-3 x^(2) + 0x1.28723b156c4abp-3 x^(3) + -0x1.b4d9a3c59339p-4 x^(4) 
      double coeffs[4] = {0x1.bcb7b151388b5p-2, -0x1.bcb7a9e0d54f3p-3, 0x1.28723b156c4abp-3, -0x1.b4d9a3c59339p-4}; 
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    }
  }
  y += m*LOG102LOW;
  y += log10F[FIndex];
  y += m*LOG102HIGH;
  return y;
}
