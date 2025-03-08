#include "mathhelper.h"

double rlibm_log10f_fma(float x) {
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
  f = rz_multiply(f, oneByF[FIndex]);
  double f2 = f*f;
  double y = 0.0;
  if (f < 0x1.5ac30c30c30c2p-9) {
    if (__builtin_expect(f == 0x1.cd28ac42fd9b7p-12, 0)) y = 0x1.90785e9e9316p-13;
    else if (__builtin_expect(f == 0x1.a17982f305e6p-11, 0)) y = 0x1.6a784ede36ee9p-12;
    else if (__builtin_expect(f == 0x1.38a8a8a8a8a8ap-10, 0)) y = 0x1.0f6900a29225ep-11;
    else if (__builtin_expect(f == 0x1.8027f6027f602p-10, 0)) y = 0x1.4d6de75f69f55p-11;
    else if (__builtin_expect(f == 0x1.b2ce38e38e38dp-10, 0)) y = 0x1.795ac8e55db89p-11;
    else if (__builtin_expect(f == 0x1.14f05397829cbp-9, 0)) y = 0x1.e095991a1dc94p-11;
    else if (__builtin_expect(f == 0x1.1fddb0d3224f2p-9, 0)) y = 0x1.f386a17944062p-11;
    else if (__builtin_expect(f == 0x1.4a4ce6b41c54fp-9, 0)) y = 0x1.1e88cf682422cp-10;
    else if (f < 0x1.5abffffffffffp-10) {
      //0x1.cd28ac42fd9b7p-12, 0x1.a17982f305e6p-11, 0x1.38a8a8a8a8a8ap-10
      //y=0x1.bcb7b15255d06p-2 x^(1) + -0x1.bcb7ae397b902p-3 x^(2) + 0x1.286a6675c0b8dp-3 x^(3) + -0x1.88277ddec5e8dp-4 x^(4)
      double coeffs[4] = {0x1.bcb7b15255d06p-2, -0x1.bcb7ae397b902p-3, 0x1.286a6675c0b8dp-3, -0x1.88277ddec5e8dp-4};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      double tmp3 =__builtin_fma(tmp2, f2, tmp1);
      y = tmp3*f;
    } else {
      //0x1.8027f6027f602p-10, 0x1.b2ce38e38e38dp-10, 0x1.14f05397829cbp-9, 0x1.1fddb0d3224f2p-9, 0x1.4a4ce6b41c54fp-9
      //y=0x1.bcb7b1515cba5p-2 x^(1) + -0x1.bcb7a3d91d3b4p-3 x^(2) + 0x1.285ec70cfa14fp-3 x^(3) + -0x1.96e1458973cd2p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b1515cba5p-2, -0x1.bcb7a3d91d3b4p-3, 0x1.285ec70cfa14fp-3, -0x1.96e1458973cd2p-4};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      double tmp3 =__builtin_fma(tmp2, f2, tmp1);
      y = tmp3*f;
    }
  } else {
    if (__builtin_expect(f == 0x1.5befefefefefep-9, 0)) y = 0x1.2dd06517d9cf4p-10;
    else if (__builtin_expect(f == 0x1.6151515151514p-9, 0)) y = 0x1.32799497d9cf4p-10;
    else if (__builtin_expect(f == 0x1.7294949494949p-9, 0)) y = 0x1.416d8877d9cf4p-10;
    else if (__builtin_expect(f == 0x1.747c7c7c7c7c7p-9, 0)) y = 0x1.43141ff7d9cf4p-10;
    else if (__builtin_expect(f == 0x1.8ff099fc267fp-9, 0)) y = 0x1.5adab9d421c81p-10;
    else if (__builtin_expect(f == 0x1.bde34a2b10bf5p-9, 0)) y = 0x1.82a2d2e7ad681p-10;
    else if (__builtin_expect(f == 0x1.c36p-9, 0)) y = 0x1.8762c48p-10;
    else if (__builtin_expect(f == 0x1.e09ee58469ee5p-9, 0)) y = 0x1.a0b2c8b1d5db9p-10;
    else if (__builtin_expect(f == 0x1.e0b56ad5ab56ap-9, 0)) y = 0x1.a0c6415933e8p-10;
    else if (__builtin_expect(f == 0x1.f95306eb3e452p-9, 0)) y = 0x1.b6133cb3ccd2ap-10;
    else if (__builtin_expect(f == 0x1.f9a147ae147acp-9, 0)) y = 0x1.b656e25b8fee6p-10;
    else if (__builtin_expect(f == 0x1.2959203cae758p-8, 0)) y = 0x1.01b06af117e7ap-9;
    else if (__builtin_expect(f == 0x1.29ee62a46756dp-8, 0)) y = 0x1.0231755f6abc7p-9;
    else if (__builtin_expect(f == 0x1.2af84a062b2e3p-8, 0)) y = 0x1.031766776c50cp-9;
    else if (__builtin_expect(f == 0x1.2bec04fec04fep-8, 0)) y = 0x1.03ea19944c678p-9;
    else if (__builtin_expect(f == 0x1.95e4d9364d935p-8, 0)) y = 0x1.5f77b864726f6p-9;
    else if (f < 0x1.038e9aa180dbep-8) { 
      //0x1.5befefefefefep-9, 0x1.6151515151514p-9, 0x1.7294949494949p-9, 0x1.747c7c7c7c7c7p-9, 0x1.8ff099fc267fp-9, 0x1.bde34a2b10bf5p-9, 0x1.c36p-9, 0x1.e09ee58469ee5p-9, 0x1.e0b56ad5ab56ap-9, 0x1.f95306eb3e452p-9, 0x1.f9a147ae147acp-9
      //y=0x1.bcb7b1516e142p-2 x^(1) + -0x1.bcb7a93f2bed2p-3 x^(2) + 0x1.286f865694206p-3 x^(3) + -0x1.b19a958781102p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b1516e142p-2, -0x1.bcb7a93f2bed2p-3, 0x1.286f865694206p-3, -0x1.b19a958781102p-4};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      double tmp3 =__builtin_fma(tmp2, f2, tmp1);
      y = tmp3*f;
    } else {
      //0x1.2959203cae758p-8, 0x1.29ee62a46756dp-8, 0x1.2af84a062b2e3p-8, 0x1.2bec04fec04fep-8, 0x1.95e4d9364d935p-8
      //y=0x1.bcb7b1510be89p-2 x^(1) + -0x1.bcb7a93b9e55fp-3 x^(2) + 0x1.2871d754230c9p-3 x^(3) + -0x1.b4b22f9e9d9dbp-4 x^(4) 
      double coeffs[4] = {0x1.bcb7b1510be89p-2, -0x1.bcb7a93b9e55fp-3, 0x1.2871d754230c9p-3, -0x1.b4b22f9e9d9dbp-4};
      double tmp1 = __builtin_fma(f, coeffs[1], coeffs[0]);
      double tmp2 = __builtin_fma(f, coeffs[3], coeffs[2]);
      double tmp3 =__builtin_fma(tmp2, f2, tmp1);
      y = tmp3*f;
    }
  }
  y = __builtin_fma(m, LOG102LOW, y);
  double extra = __builtin_fma(m, LOG102HIGH, log10F[FIndex]);
  return y+extra;
}
