#include "rlibm.h" 

double rlibm_expf_fma(float x) {
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
    else if (__builtin_expect(R == -0x1.e48ca8p-12, 0)) y = 0x1.ffc3718p-1;
    else if (__builtin_expect(R == -0x1.8bc31ep-12, 0)) y = 0x1.ffce898p-1;
    else {
      //-0x1.f925ff513d9ccp-9, -0x1.e08d3ep-9, -0x1.c57f87ab4d7f8p-9, -0x1.e48ca8p-12, -0x1.8bc31ep-12
      //y=0x1.0000000000007p+0 x^(0) + 0x1.fffffffffb6ddp-1 x^(1) + 0x1.ffffffaaa97a7p-2 x^(2) + 0x1.55546fb441066p-3 x^(3) + 0x1.53a2f24251869p-5 x^(4)
      double coeffs[5] = {0x1.0000000000007p+0, 0x1.fffffffffb6ddp-1, 0x1.ffffffaaa97a7p-2, 0x1.55546fb441066p-3, 0x1.53a2f24251869p-5};
      double R2 = R*R;
      double tmp1 = __builtin_fma(coeffs[1], R, coeffs[0]);
      double tmp2 = __builtin_fma(coeffs[3], R, coeffs[2]);
      double tmp3 = __builtin_fma(coeffs[4], R2, tmp2);
      y = __builtin_fma(tmp3, R2, tmp1);
    }
  } else {
    if (__builtin_expect(R == 0x1.fdff02p-17, 0)) y = 0x1.0000ff8p+0;
    else if (__builtin_expect(R == 0x1.e614fap-9, 0)) y = 0x1.00f37e8p+0;
    else if (__builtin_expect(R == 0x1.fb98e14737954p-9, 0)) y = 0x1.00fe4ae25ee7ep+0;
    else if (__builtin_expect(R == 0x1.8276f74aef674p-8, 0)) y = 0x1.01839ba05f765p+0;
    else if (__builtin_expect(R == 0x1.113e28d4656cdp-7, 0)) y = 0x1.0224c4fabbdeep+0;
    else if (__builtin_expect(R == 0x1.28e70f8380c3fp-7, 0)) y = 0x1.0254807630b8ep+0;
    else if (__builtin_expect(R == 0x1.322aa79dbc8eap-7, 0)) y = 0x1.02673379a0aedp+0;
    else if (__builtin_expect(R == 0x1.5d1488105c611p-7, 0)) y = 0x1.02bde4f477ae6p+0;
    else if (__builtin_expect(R == 0x1.5f25f7dc62a2bp-7, 0)) y = 0x1.02c212f8d4fc8p+0;
    else {
      //0x1.fdff02p-17, 0x1.e614fap-9, 0x1.fb98e14737954p-9, 0x1.8276f74aef674p-8, 0x1.113e28d4656cdp-7, 0x1.28e70f8380c3fp-7, 0x1.322aa79dbc8eap-7, 0x1.5d1488105c611p-7, 0x1.5f25f7dc62a2bp-7
      //y=0x1.ffffffffffffep-1 x^(0) + 0x1.fffffffffc99bp-1 x^(1) + 0x1.000000182ed63p-1 x^(2) + 0x1.5554afb58e096p-3 x^(3) + 0x1.56d03945e07ap-5 x^(4)      
      double coeffs[5] = {0x1.ffffffffffffep-1, 0x1.fffffffffc99bp-1, 0x1.000000182ed63p-1, 0x1.5554afb58e096p-3, 0x1.56d03945e07ap-5};
      double R2 = R*R;
      double tmp1 = __builtin_fma(coeffs[1], R, coeffs[0]);
      double tmp2 = __builtin_fma(coeffs[3], R, coeffs[2]);
      double tmp3 = __builtin_fma(coeffs[4], R2, tmp2);
      y = __builtin_fma(tmp3, R2, tmp1);
    }
  }
  double_x ret = {.d=exp2JBy64[J]};
  ret.x += ((uint64_t)M << 52);
  y *= ret.d;
  return y;
}
