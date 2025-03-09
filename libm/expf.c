#include "libm.h" 

double ourlibm_expf(float x) {
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
  if (R < -0x1.9e76cap-24) {
    if (__builtin_expect(R == -0x1.f925ff513d9ccp-9, 0)) y = 0x1.fe07db242d393p-1;
    else if (__builtin_expect(R == -0x1.e08d3ep-9, 0)) y = 0x1.fe20548p-1;
    else if (__builtin_expect(R == -0x1.c57f87ab4d7f8p-9, 0)) y = 0x1.fe3b49c55f111p-1;
    else {
      //-0x1.f925ff513d9ccp-9, -0x1.e08d3ep-9, -0x1.c57f87ab4d7f8p-9
      //y=0x1.0000000000002p+0 x^(0) + 0x1.fffffffff8b01p-1 x^(1) + 0x1.ffffffa49bdf1p-2 x^(2) + 0x1.55546aade8b29p-3 x^(3) + 0x1.53a01be61af96p-5 x^(4) 
      double coeffs[5] = {0x1.0000000000002p+0, 0x1.fffffffff8b01p-1, 0x1.ffffffa49bdf1p-2, 0x1.55546aade8b29p-3, 0x1.53a01be61af96p-5};
      double R2 = R*R;
      double tmp1 = coeffs[1]*R+coeffs[0];
      double tmp2 = coeffs[3]*R+coeffs[2];
      double tmp3 = coeffs[4]*R2+tmp2;
      y = tmp3*R2+tmp1;
    }
  } else {
    if (__builtin_expect(R == 0x1.fdff02p-17, 0)) y = 0x1.0000ff8p+0;
    else if (__builtin_expect(R == 0x1.8d7cb6p-12, 0)) y = 0x1.0018d98p+0;
    else if (__builtin_expect(R == 0x1.4687aa6f9bc18p-9, 0)) y = 0x1.00a3779b33e9p+0;
    else if (__builtin_expect(R == 0x1.473eeec82589cp-9, 0)) y = 0x1.00a3d386370cep+0;
    else if (__builtin_expect(R == 0x1.d2fd8bccca2c4p-9, 0)) y = 0x1.00e9e908c645ep+0;
    else if (__builtin_expect(R == 0x1.8276f74aef674p-8, 0)) y = 0x1.01839ba05f765p+0;
    else if (__builtin_expect(R == 0x1.a142e08c76f12p-8, 0)) y = 0x1.01a297ec1baf8p+0;
    else if (__builtin_expect(R == 0x1.28e70f8380c3fp-7, 0)) y = 0x1.0254807630b8ep+0;
    else {
      //0x1.fdff02p-17, 0x1.8d7cb6p-12, 0x1.4687aa6f9bc18p-9, 0x1.473eeec82589cp-9, 0x1.d2fd8bccca2c4p-9, 0x1.8276f74aef674p-8, 0x1.a142e08c76f12p-8, 0x1.28e70f8380c3fp-7
      //y=0x1.ffffffffffffep-1 x^(0) + 0x1.fffffffff6c27p-1 x^(1) + 0x1.0000002e9c5d4p-1 x^(2) + 0x1.555465534ee63p-3 x^(3) + 0x1.5712c517ad9b7p-5 x^(4)
      double coeffs[5] = {0x1.ffffffffffffep-1, 0x1.fffffffff6c27p-1, 0x1.0000002e9c5d4p-1, 0x1.555465534ee63p-3, 0x1.5712c517ad9b7p-5};
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
