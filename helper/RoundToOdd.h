#pragma once
#include "mpfr.h"
#include "math.h"

#include "../include/libm.h"

double FromMPFRToFloat34Ro(mpfr_t mval, int sticky) {
  double_x y;
  double max_val = 0x1.ffffff8p+127;
  double sub_max_val = 0x1.ffffffp+127;
  /* Handle case where result is nan */
  if (mpfr_nan_p(mval) != 0) return 0.0/0.0;
  /* Handle cases where the approximation result is zero. If sticky bit is set, return the smallest 34-bit FP number according to the sign bit. Else, return +/-0 according to the sign bit. */
  if (mpfr_cmp_d(mval, 0.0) == 0) {
    if (sticky == 0) {
      if (mpfr_signbit(mval)) return -0.0;
      else return 0.0;
    } else {
      if (mpfr_signbit(mval)) return -0x1p-151;
      else return 0x1p-151;
    }
  }
  /* Handle cases where the result is infinite */
  if (mpfr_inf_p(mval) && (mpfr_sgn(mval) > 0)) return INFINITY; 
  if (mpfr_inf_p(mval) && (mpfr_sgn(mval) < 0)) return -INFINITY; 
  /* Handle cases where mval's absolute value is the second largest number in the 34-bit representation (which would be the largest number in mval's representation since it only has 25 bits of precision) and the sticky bit is set. */ 
  if ((mpfr_cmp_d(mval, sub_max_val) == 0) && (sticky != 0)) return max_val;
  if ((mpfr_cmp_d(mval, -sub_max_val) == 0) && (sticky != 0)) return -max_val;
  /* Compare mval against the two normal numbers with the smallest absolute values to determine if it is subnormal. */
  bool pos_subnormal = (mpfr_sgn(mval) > 0) && (mpfr_cmp_d(mval, 0x1p-126) < 0);
  bool neg_subnormal = (mpfr_sgn(mval) < 0) && (mpfr_cmp_d(mval, -0x1p-126) > 0);
  if (pos_subnormal || neg_subnormal) {
    /* mval is in the subnormal range. Note that at this point 0x1p-150 <= |mval| <= 0x1.fffffep-127. */
    y.d = mpfr_get_d(mval, MPFR_RNDZ);
    unsigned long exp = y.x >> 52;
    exp &= 0x7ff;
    exp -= 1023;
    unsigned long shift = -exp - 99;
    if (sticky != 0) y.x |= (1ull << shift);
    return y.d;
  }
  /* This is the case reached when mval is in the normal range, meaning it has 25 bits of precision. */
  /* Once mval is casted to a double, there will be 24 bits after the binary point. */
  y.d = mpfr_get_d(mval, MPFR_RNDZ);
  /* Should the sticky bit be non-zero, a bit needs to be appended to the 25th bit after the binary point, which would be the 26th bit for the final number. */
  if (sticky != 0) y.x |= (1ull << 27);
  return y.d;
}
