#include "mathhelper.h"

double ourlibm_log10f(float x) {
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
    else if (__builtin_expect(f == 0x1.4868686868686p-12, 0)) y = 0x1.1d34f2bece798p-13;
    else if (__builtin_expect(f == 0x1.cd28ac42fd9b7p-12, 0)) y = 0x1.90785e9e8095fp-13;
    else if (__builtin_expect(f == 0x1.a17982f305e6p-11, 0)) y = 0x1.6a784ede374e9p-12;
    else if (__builtin_expect(f == 0x1.38a8a8a8a8a8ap-10, 0)) y = 0x1.0f6900a29215dp-11;
    else if (__builtin_expect(f == 0x1.8027f6027f602p-10, 0)) y = 0x1.4d6de75f6cd55p-11;
    else if (__builtin_expect(f == 0x1.b2ce38e38e38dp-10, 0)) y = 0x1.795ac8e55e109p-11;
    else if (__builtin_expect(f == 0x1.14f05397829cbp-9, 0)) y = 0x1.e095991a1dc84p-11;
    else if (__builtin_expect(f == 0x1.1fddb0d3224f2p-9, 0)) y = 0x1.f386a17940062p-11;
    else if (__builtin_expect(f == 0x1.4a4ce6b41c54fp-9, 0)) y = 0x1.1e88cf68242aep-10;
    else if (f < 0x1.5abffffffffffp-10) {
      //y=0x1.bcb7b15254969p-2 x^(1) + -0x1.bcb7ae357da5ep-3 x^(2) + 0x1.286aab8d33048p-3 x^(3) + -0x1.899bb5e03a67cp-4 x^(4)
      double coeffs[4] = {0x1.bcb7b15254969p-2, -0x1.bcb7ae357da5ep-3, 0x1.286aab8d33048p-3, -0x1.899bb5e03a67cp-4};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    } else {
      //y=0x1.bcb7b151652bep-2 x^(1) + -0x1.bcb7a44c30e46p-3 x^(2) + 0x1.285fba8584b17p-3 x^(3) + -0x1.98277e0310802p-4 x^(4) 
      double coeffs[4] = {0x1.bcb7b151652bep-2, -0x1.bcb7a44c30e46p-3, 0x1.285fba8584b17p-3, -0x1.98277e0310802p-4};
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    }
  } else {
    if (__builtin_expect(f == 0x1.63875b37e875bp-9, 0)) y = 0x1.3463f286e5e07p-10;                                                     else if (__builtin_expect(f == 0x1.7f15789157891p-9, 0)) y = 0x1.4c41e5f756217p-10; 
    else if (__builtin_expect(f == 0x1.8ff099fc267fp-9, 0)) y = 0x1.5adab9d4238b9p-10;
    else if (__builtin_expect(f == 0x1.bde34a2b10bf5p-9, 0)) y = 0x1.82a2d2e7aa3a1p-10;
    else if (__builtin_expect(f == 0x1.c12cp-9, 0)) y = 0x1.857a8f8p-10;
    else if (__builtin_expect(f == 0x1.c36p-9, 0)) y = 0x1.8762c48p-10;
    else if (__builtin_expect(f == 0x1.c3e7e7e7e7e7ep-9, 0)) y = 0x1.87d86907d9cf3p-10;
    else if (__builtin_expect(f == 0x1.d337373737373p-9, 0)) y = 0x1.9518c907d9cf3p-10;
    else if (__builtin_expect(f == 0x1.e09ee58469ee5p-9, 0)) y = 0x1.a0b2c8b1d87f9p-10;
    else if (__builtin_expect(f == 0x1.e0b56ad5ab56ap-9, 0)) y = 0x1.a0c6415932f8p-10;
    else if (__builtin_expect(f == 0x1.f95306eb3e452p-9, 0)) y = 0x1.b6133cb3cca4ap-10;
    else if (__builtin_expect(f == 0x1.f9a147ae147acp-9, 0)) y = 0x1.b656e25b8fc66p-10;
    else if (__builtin_expect(f == 0x1.fdf239662b9f8p-9, 0)) y = 0x1.ba12f06b7a773p-10; 
    else if (__builtin_expect(f == 0x1.32fffffffffffp-8, 0)) y = 0x1.0a08c06518725p-9;
    else if (__builtin_expect(f == 0x1.397caf168c99dp-8, 0)) y = 0x1.0fa46b95ae248p-9;
    else if (__builtin_expect(f == 0x1.4212f684bda12p-8, 0)) y = 0x1.1710983746603p-9;
    else if (__builtin_expect(f == 0x1.48e7791a0f544p-8, 0)) y = 0x1.1cf7d4373cd23p-9;
    else if (__builtin_expect(f == 0x1.4dc498c05a84ep-8, 0)) y = 0x1.212be44fb2275p-9;
    else if (__builtin_expect(f == 0x1.572cb2cb2cb2cp-8, 0)) y = 0x1.294ccbb7cc9d6p-9;
    else if (__builtin_expect(f == 0x1.600c71c71c71cp-8, 0)) y = 0x1.30f798a6c78d8p-9;
    else if (__builtin_expect(f == 0x1.95e4d9364d935p-8, 0)) y = 0x1.5f77b864725d6p-9;
    else if (__builtin_expect(f == 0x1.d8098d5f85bb3p-8, 0)) y = 0x1.9889718daa069p-9;
    else if (__builtin_expect(f == 0x1.eafep-8, 0)) y = 0x1.a8e17b8218083p-9;
    else if (f < 0x1.038e9aa180dbep-8) {
      //y=0x1.bcb7b14fc8c53p-2 x^(1) + -0x1.bcb79f2d9c851p-3 x^(2) + 0x1.286558230e07dp-3 x^(3) + -0x1.aacc26c85724cp-4 x^(4)
      double coeffs[4] = {0x1.bcb7b14fc8c53p-2, -0x1.bcb79f2d9c851p-3, 0x1.286558230e07dp-3, -0x1.aacc26c85724cp-4}; 
      double tmp1 = f*coeffs[1]+coeffs[0];
      double tmp2 = f*coeffs[3]+coeffs[2];
      double tmp3 = tmp2*f2+tmp1;
      y = tmp3*f;
    } else {
      //y=0x1.bcb7b154fca63p-2 x^(1) + -0x1.bcb7ba4283d67p-3 x^(2) + 0x1.287dd26be6789p-3 x^(3) + -0x1.ba344c43b9a77p-4 x^(4)
      double coeffs[4] = {0x1.bcb7b154fca63p-2, -0x1.bcb7ba4283d67p-3, 0x1.287dd26be6789p-3, -0x1.ba344c43b9a77p-4}; 
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
