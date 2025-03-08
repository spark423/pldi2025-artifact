#include "rlibm.h"

double rlibm_log10f_og(float x) {

  //  double old_rr = old_range_reduction(x);
  float_x inp = {.f = x};
  uint32_t ux = inp.x;
  uint64_t m = ux & 0x7FFFFF;
  m = m << 29;
  int exp = (ux >> 23) - 127;
  
  if(__builtin_expect(ux < 0x800000 || ux >= 0x7F800000, 0)){

    /* This code for handling subnormals and special cases is from the
       CORE-MATH project:
       https://gitlab.inria.fr/core-math/core-math/-/blob/master/src/binary32/log2/log2f.c
    */    
    if (ux==0||ux==(1u<<31))
      return -__builtin_inff(); // +0.0 || -0.0

    uint32_t inf_or_nan = ((ux>>23)&0xff) == 0xff, nan = inf_or_nan && (ux<<9);

    if (ux>>31 && !nan) return __builtin_nanf("-");

    if (inf_or_nan) return x;

    // subnormal
    int nz = __builtin_clzll(m);
    m <<= nz-11;
    m &= ~0ul>>12;
    exp = exp - (nz - 12);
  }

  double_x  xd = {.x = m | 0x3FF0000000000000ULL};
  uint64_t FIndex = m>> 45;
  uint64_t fm = (FIndex) << 45;
  double_x  xf = {.x = fm |0x3FF0000000000000ULL};
  double f = xd.d - xf.d;  

  f *= oneByF[FIndex];

  double coeffs[6] =
    {
      0x1.bcb7b1526eba1p-2,
      -0x1.bcb7b152ff289p-3,
      0x1.287a6320ef253p-3,
      -0x1.bc614c3bdbca8p-4,
      0x1.23bf152c3f48ap-4,
      0x1.cb2f0b48e857fp-1,
    };
  double y = exp * LOG102LOW + log10F[FIndex] + exp * LOG102HIGH;

  if(__builtin_expect(f == 0x1.bde34a2b10bf6p-9,  0)) {
    return 0x1.82a2d0cd6ee1p-10  + y;
  }
  
  if(__builtin_expect(f == 0x1.8ff099fc267fp-9,  0)) {
    return  0x1.5adab7bb93889p-10 + y;
  }


  if(__builtin_expect(f ==0x1.8abe0f83e0f84p-9,  0)) {
    return 0x1.565a88a764385p-10  + y;
  }

  if(__builtin_expect(f == 0x1.8533a8c0dc69ap-10 ,  0)) {
    return 0x1.51ce40d6f4f67p-11  + y;
  }

  if(__builtin_expect(f == 0x1.2bec04fec04ffp-8,  0)) {
    return  0x1.03ea0f7b7496dp-9  + exp * LOG102LOW + log10F[FIndex] + exp * LOG102HIGH;
  }
  
  if(__builtin_expect(f == 0x1.2af84a062b2e5p-8,  0)) {
    return 0x1.03176656347c4p-9 + exp * LOG102LOW + log10F[FIndex] + exp * LOG102HIGH;
  }


  if(__builtin_expect(f == 0x1.e0b56ad5ab56bp-9,  0)) {
    return 0x1.a0c640ef6a074p-10 + y;
  }

  if(__builtin_expect(f == 0x1.1fddb0d3224f3p-9,  0)) {
    return 0x1.f386956531508p-11 + exp * LOG102LOW + log10F[FIndex] + exp * LOG102HIGH;
  }

  double xsquare = f * f;
  double xcube = f * xsquare;
  double temp1 = fma(coeffs[1] ,f , coeffs[0]);
  double temp2 = fma(coeffs[2], xsquare, temp1);
  double temp3 = fma(coeffs[4], f , coeffs[3]);
  double temp4 = fma(coeffs[5], xsquare, temp3);
  double temp5 = fma(temp4, xcube ,  temp2);
  double temp6 =  f * temp5;
  return temp6 + exp * LOG102LOW + log10F[FIndex] + exp * LOG102HIGH;  
}
