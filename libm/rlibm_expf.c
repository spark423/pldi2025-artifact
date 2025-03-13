#include "libm.h"

double rlibm_expf(float x) {
  float_x fx = {.f=x};
  if((fx.x & 0x7FFFFFFF) == 0) return 1.0;
  if(fx.x <= 0x33ffffff) {
    if(fx.x <= 0x337fffff) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  if(fx.x >= 0x42b17218 && fx.x <= 0xb3800000) {
    if(fx.x < 0x80000000) {
      if(fx.x < 0x7f800000) return 0x1.ffffff8p+127;
      if(fx.x == 0x7f800000) return 1.0/0.0;
      return 0.0/0.0;
    }
    if(fx.x <= 0xb3000000) return 0x1.ffffff8p-1;
    return 0x1.fffffe8p-1;
  }
  if(fx.x >= 0xc2cff1b5) {
    if(fx.x == 0xff800000) return 0.0;
    if(fx.x < 0xff800000) return 0x1p-151;
    else return 0.0/0.0;
  }
  double xp = x*LGEX64; 
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = __builtin_fma(-N, ONEBY64LGE, x);
  double y = 0.0;
  if (R < -0x1.9e76dcp-24) {
    if (__builtin_expect(R == -0x1.f925ff513d9ccp-9, 0)) y = 0x1.fe07db242d392p-1;
    else if (__builtin_expect(R == -0x1.c57f87ab4d7f8p-9, 0)) y = 0x1.fe3b49c55f111p-1;
    else if (__builtin_expect(R == -0x1.e48ca8p-12, 0)) y = 0x1.ffc3718p-1;
    else if (__builtin_expect(R == -0x1.8bc31ep-12, 0)) y = 0x1.ffce898p-1;
    else {
      //-0x1.f925ff513d9ccp-9, -0x1.c57f87ab4d7f8p-9, -0x1.e48ca8p-12, -0x1.8bc31ep-12
      //y=0x1.0000000000007p+0 x^(0) + 0x1.fffffffff7ec1p-1 x^(1) + 0x1.ffffffa17fe05p-2 x^(2) + 0x1.55546831af0b8p-3 x^(3) + 0x1.539f0766b7222p-5 x^(4)
      double coeffs[5] = {0x1.0000000000007p+0, 0x1.fffffffff7ec1p-1, 0x1.ffffffa17fe05p-2, 0x1.55546831af0b8p-3, 0x1.539f0766b7222p-5};
      double R2 = R*R;
      double tmp1 = coeffs[1]*R+coeffs[0];
      double tmp2 = coeffs[3]*R+coeffs[2];
      double tmp3 = coeffs[4]*R2+tmp2;
      y = tmp3*R2+tmp1;
    }
  } else {
    if (__builtin_expect(R == 0x1.627a9ep-10, 0)) y = 0x1.0058ae8p+0;
    else if (__builtin_expect(R == 0x1.e614fap-9, 0)) y = 0x1.00f37e8p+0;
    else if (__builtin_expect(R == 0x1.28e70f8380c3fp-7, 0)) y = 0x1.0254807630b8ep+0;
    else if (__builtin_expect(R == 0x1.5c77fap-7, 0)) y = 0x1.02bca88p+0;
    else if (__builtin_expect(R == 0x1.5d1488105c611p-7, 0)) y = 0x1.02bde4f477ae6p+0;
    else if (__builtin_expect(R == 0x1.5f25f7dc62a2bp-7, 0)) y = 0x1.02c212f8d4fc7p+0;
    else {
      //0x1.627a9ep-10, 0x1.e614fap-9, 0x1.28e70f8380c3fp-7, 0x1.5c77fap-7, 0x1.5d1488105c611p-7, 0x1.5f25f7dc62a2bp-7
      //y=0x1.ffffffffffffep-1 x^(0) + 0x1.fffffffffb1d4p-1 x^(1) + 0x1.0000001a3525fp-1 x^(2) + 0x1.5554b125654acp-3 x^(3) + 0x1.56c81a1f7d0c3p-5 x^(4) 
      double coeffs[5] = {0x1.ffffffffffffep-1, 0x1.fffffffffb1d4p-1, 0x1.0000001a3525fp-1, 0x1.5554b125654acp-3, 0x1.56c81a1f7d0c3p-5};
      double R2 = R*R;
      double tmp1 = coeffs[1]*R+coeffs[0];
      double tmp2 = coeffs[3]*R+coeffs[2];
      double tmp3 = coeffs[4]*R2+tmp2;
      y = tmp3*R2+tmp1;
    }
  }
  double_x ret = {.d=exp2JBy64[J]};
  ret.x += ((uint64_t)M << 52);
  y *= ret.d;
  return y;
}
