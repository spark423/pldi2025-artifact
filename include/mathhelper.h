#ifndef MATHHELPER_H
#define MATHHELPER_H

#include "rlibm.h"

static inline double rz_add(double a, double b) {
  double_x ba = {.d=a};
  double_x bb = {.d=b};
  double_x retval = {.d=a+b};
  int alb = ((ba.x & 0x7FFFFFFFFFFFFFFF) < (bb.x & 0x7FFFFFFFFFFFFFFF));
  unsigned long long mask = ba.x ^ bb.x;
  ba.x = ba.x ^ (mask * alb);
  bb.x = bb.x ^ (mask * alb);
  //At this point, |ba.d|>=|bb.d|
  ba.d = retval.d - ba.d;
  bb.d -= ba.d;
  //At this point, bb.d = a+b - rnd(a+b).
  //Given the properties of FP addition, there will be no underflow on the error term.
  //In the case that rounding had occurred, bb.d will have a non-zero value.
  //In the case that RNDA had occurred in the computation of a+b, |a+b| < |rnd(a+b)| and thus bb.d = a+b-rnd(a+b) will have a different sign from rnd(a+b).
  retval.x -= ((bb.x<<1)!=0x0)&&((bb.x^retval.x)>=0x8000000000000000);
  return retval.d;
}

static inline double rz_multiply(double a, double b) {
  //The objective of this function is to find the error term if a*b is inexact and to subtract from the ULP if and only if the error is an RNDA error.
  double_x retval = {.d=a*b};
  double_x compare1 = {.d=__builtin_fma(a, b, -retval.d)};
  double_x compare2 = {.d=__builtin_fma(-a, b, retval.d)};
  //At this point, compare1.d = a*b - rnd(a*b) and compare2.d = -a*b + rnd(a*b).
  //In the case where the operation is exact, compare1.x == compare2.x.
  //When the operation is inexact, compare1.x != compare2.x even when there is underflow since they would have different signs and underflow will preserve the signs.
  //Hence, compare1.x == compare2.x if and only if the original operation was exact.
  //In the case that RNDA had occurred in the computation of rnd(a*b) and induced an error, |rnd(a*b)|>|a*b| and compare1.d = a*b - rnd(a*b) will have a sign that is the opposite of rnd(a*b). 
  //(compare1.x^retval.x)>0x8000000000000000 will be true if such is the case.
  //Even when there is underflow on compare1.d, (compare1.x^retval.x)>0x8000000000000000) will hold since underflow still preserves the sign.
  //In summary, (compare1.x != compare2.x) checks if error exists. ((compare1.x^retval.x)>0x8000000000000000) checks if the error was caused by RNDA.
  retval.x -= (compare1.x!=compare2.x)&&((compare1.x^retval.x)>=0x8000000000000000);
  return retval.d;
}

#endif
