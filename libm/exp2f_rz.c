#include "mathhelper.h"

double ourlibm_exp2f_rz(float x) {
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
  if (__builtin_expect(R == 0x1.853a6ep-9, 0)) y = 0x1.0087098p+0;
  else {
    //0x1.853a6ep-9
    //y=0x1p+0 x^(0) + 0x1.62e42fefa37f8p-1 x^(1) + 0x1.ebfbdff82a128p-3 x^(2) + 0x1.c6b08be2f0fcbp-5 x^(3) + 0x1.3b2b4de5d8155p-7 x^(4) + 0x1.61f78463e59f5p-10 x^(5) 
    double coeffs[6] = {0x1p+0, 0x1.62e42fefa37f8p-1, 0x1.ebfbdff82a128p-3, 0x1.c6b08be2f0fcbp-5, 0x1.3b2b4de5d8155p-7, 0x1.61f78463e59f5p-10};
    double R2 = rz_multiply(R, R);
    double tmp1 = rz_multiply(R, coeffs[1]);
    double tmp2 = rz_multiply(R, coeffs[3]);
    double tmp3 = rz_multiply(R, coeffs[5]);
    tmp1 = rz_add(tmp1, coeffs[0]);
    tmp2 = rz_add(tmp2, coeffs[2]);
    tmp3 = rz_add(tmp3, coeffs[4]);
    double tmp4 = rz_multiply(R2, tmp3);
    tmp4 = rz_add(tmp4, tmp2);
    double tmp5 = rz_multiply(R2, tmp4);
    y = rz_add(tmp5, tmp1);
  }
  ret.d = exp2JBy64[J];
  ret.x += ((uint64_t)M << 52);
  y = rz_multiply(y, ret.d);
  return y;
}
