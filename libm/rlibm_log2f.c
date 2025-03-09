#include "libm.h"

double rlibm_log2f(float x) {

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

  /* power of 2 */
  if(__builtin_expect(!m, 0)) return exp;
  
  double_x  xd = {.x = m | 0x3FF0000000000000ULL};
  uint64_t FIndex = m>> 45;
  uint64_t fm = (FIndex) << 45;
  double_x  xf = {.x = fm |0x3FF0000000000000ULL};
  double f = xd.d - xf.d;  
  
  f *= oneByF[FIndex];

  double coeffs[] = {
    0x1.71547652bcde3p+0,
    -0x1.7154769679dd8p-1,
    0x1.ec7198ec61291p-2,
    -0x1.72033bee9c2d6p-2,
    0x1.4f082e01903edp-2
  };
  
  double xsquare = f*f;

  double temp1 = coeffs[3] + f * coeffs[4];
  double temp2 = coeffs[1] + f * coeffs[2];
  double temp3 = temp2 + xsquare * temp1;
  double temp4 = xsquare * temp3;
  double temp5 = logBase2[FIndex] + exp;
  double y = temp4 + f * coeffs[0] + temp5;
  return y;
}
