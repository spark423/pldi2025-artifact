#include "libm.h"

double ourlibm_exp2f(float x) {
  float_x fx = {.f=x};
  if ((fx.x & 0x7FFFFFFF) == 0) return 1.0;
  if (fx.x <= 0x3438aa3a) {
    if(fx.x <= 0x33b8aa3a) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  if (fx.x >= 0x43000000 && fx.x <= 0xb3b8aa3b) {
    if (fx.x < 0x80000000) {
      if(fx.x < 0x7f800000) return 0x1.ffffff8p+127;
      if(fx.x == 0x7f800000) return 1.0/0.0;
      return 0.0/0.0;
    }
    if(fx.x <= 0xb338aa3b) return 0x1.ffffff8p-1;
    return 0x1.fffffe8p-1;
  }
  if(fx.x >= 0xc3160001) {
    if(fx.x == 0xff800000) return 0.0;
    if(fx.x < 0xff800000) return 0x1p-151;
    else return 0.0/0.0;
  }
  double_x ret;
  double xp = x * 64;
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = x-N*0x1p-6;
  if(R==0.0 && N2==0) {
    ret.d = 1.0;
    ret.x += ((uint64_t)M << 52);    
    return ret.d;
  }
  double y = 0.0;
  if (__builtin_expect(R == -0x1.a7a04cp-14, 0)) y = 0x1.fff6d28p-1;
  else if (__builtin_expect(R == -0x1.5a3f34p-21, 0)) y = 0x1.fffff08p-1;
  else if (__builtin_expect(R == 0x1.853a6ep-9, 0)) y = 0x1.0087098p+0;
  else {
    double coeffs[6] = {0x1p+0, 0x1.62e42fefa37eep-1, 0x1.ebfbdff825106p-3, 0x1.c6b08bf28a8bap-5, 0x1.3b2b523757898p-7, 0x1.61c93ca3f7bc8p-10};
    double R2 = R*R;
    double tmp1 = R*coeffs[1]+coeffs[0];
    double tmp2 = R*coeffs[3]+coeffs[2];
    double tmp3 = R*coeffs[5]+coeffs[4];
    double tmp4 = R2*tmp3+tmp2;
    y = R2*tmp4 + tmp1;
  }
  ret.d = exp2JBy64[J];
  ret.x += ((uint64_t)M << 52);
  y *= ret.d;
  return y;
}
