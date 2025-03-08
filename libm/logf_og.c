#include "rlibm.h"

double rlibm_logf_og(float x) {

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

  double coeffs[6] = {
    0x1.000000000a8d2p+0,
    -0x1.00000096a7feap-1,
    0x1.55583de8775bep-2,
    -0x1.033dcd77e7462p-2,
    0x1.3aca6f043b6fcp-1,
    -0x1.4602e8829cb5fp+4
  };
  double y = exp * LN2 + lnF[FIndex];

  if(__builtin_expect(f == 0x1.7096969696969p-11, 0)) {
    return 0x1.707567c76c101p-11 + y;
  }

  if(__builtin_expect(f == 0x1.67f6db6db6db7p-10,  0)) {
    return 0x1.67b7a57462001p-10 + y;
  }
  
  if(__builtin_expect(f == 0x1.d6f7e432f7e44p-10, 0)) {
    return 0x1.d68bb6f7c2101p-10 +  y;
  }

  if(__builtin_expect(f == 0x1.23624dd2f1aap-9, 0)) {
    return 0x1.230f831236001p-9  + y;
  }

  if(__builtin_expect(f == 0x1.57497b425ed09p-9, 0)) {
    return 0x1.56d6991a2a001p-9 +  y;
  }
  
  if(__builtin_expect(f == 0x1.e8a1fd1b7af01p-9, 0)) {
    return 0x1.e7b9668c44001p-9 + y;
  }

  if(__builtin_expect(f == 0x1.3155555555555p-8, 0)) {
    return 0x1.309fcf6433001p-8 + y;
  }


  if(__builtin_expect(f == 0x1.9c0a2c145828bp-8, 0)) {
    return 0x1.9abff5d8ca001p-8 +  y;
  }

  if(__builtin_expect(f == 0x1.bab0df6b0df6bp-9, 0)){
    return 0x1.b9f1e20cc6801p-9 + y;
  }

  if(__builtin_expect(f == 0x1.fbd2361d2361ep-10, 0)) {
    return 0x1.fb54746534001p-10  +  y;
  }

  if(__builtin_expect(f == 0x1.f9fcp-8, 0)) {
    return 0x1.f80a850000001p-8 +  y;
  }



  double xsquare = f * f;
  double xcube = f * xsquare;
  double temp1 = fma(coeffs[1] ,f , coeffs[0]);
  double temp2 = fma(coeffs[2], xsquare, temp1);
  double temp3 = fma(coeffs[4], f , coeffs[3]);
  double temp4 = fma(coeffs[5], xsquare, temp3);
  double temp5 = fma(temp4, xcube ,  temp2);
  double temp6 =  f * temp5;
  return temp6 + y;  
}
