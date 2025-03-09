#include "mathhelper.h"

double ourlibm_expf_rz(float x) {
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
    if (__builtin_expect(R == -0x1.f925ff513d9ccp-9, 0)) y = 0x1.fe07db242d394p-1;
    else if (__builtin_expect(R == -0x1.e08d3ep-9, 0)) y = 0x1.fe20548p-1;
    else if (__builtin_expect(R == -0x1.c57f87ab4d7f8p-9, 0)) y = 0x1.fe3b49c55f112p-1;
    else { 
      //-0x1.f925ff513d9ccp-9, -0x1.e08d3ep-9, -0x1.c57f87ab4d7f8p-9
      //y=0x1.0000000000003p+0 x^(0) + 0x1.fffffffff96cdp-1 x^(1) + 0x1.ffffffa71f92bp-2 x^(2) + 0x1.55546da07a83dp-3 x^(3) + 0x1.53a24ef8f1327p-5 x^(4) 
      double coeffs[5] = {0x1.0000000000003p+0, 0x1.fffffffff96cdp-1, 0x1.ffffffa71f92bp-2, 0x1.55546da07a83dp-3, 0x1.53a24ef8f1327p-5};
      double R2 = rz_multiply(R, R);
      double tmp1 = rz_add(rz_multiply(R, coeffs[1]), coeffs[0]);
      double tmp2 = rz_add(rz_multiply(R, coeffs[3]), coeffs[2]);
      double tmp3 = rz_add(rz_multiply(R2, coeffs[4]), tmp2);
      double tmp4 = rz_multiply(R2, tmp3);
      y = rz_add(tmp4, tmp1);
    }
  } else {
    if (__builtin_expect(R == 0x1.fdff02p-17, 0)) y = 0x1.0000ff8p+0;
    else if (__builtin_expect(R == 0x1.e614fap-9, 0)) y = 0x1.00f37e8p+0;
    else if (__builtin_expect(R == 0x1.8276f74aef674p-8, 0)) y = 0x1.01839ba05f766p+0;
    else if (__builtin_expect(R == 0x1.113e28d4656cdp-7, 0)) y = 0x1.0224c4fabbdeep+0;
    else if (__builtin_expect(R == 0x1.28e70f8380c3fp-7, 0)) y = 0x1.0254807630b8ep+0;
    else if (__builtin_expect(R == 0x1.322aa79dbc8eap-7, 0)) y = 0x1.02673379a0aeep+0;
    else if (__builtin_expect(R == 0x1.5d1488105c611p-7, 0)) y = 0x1.02bde4f477ae6p+0;
    else {
      //0x1.fdff02p-17, 0x1.e614fap-9, 0x1.8276f74aef674p-8, 0x1.113e28d4656cdp-7, 0x1.28e70f8380c3fp-7, 0x1.322aa79dbc8eap-7, 0x1.5d1488105c611p-7
      //y=0x1.ffffffffffffep-1 x^(0) + 0x1.fffffffffdb5ep-1 x^(1) + 0x1.00000017a215ep-1 x^(2) + 0x1.5554aeb3df86dp-3 x^(3) + 0x1.56d222a7657a4p-5 x^(4) 
      double coeffs[5] = {0x1.ffffffffffffep-1, 0x1.fffffffffdb5ep-1, 0x1.00000017a215ep-1, 0x1.5554aeb3df86dp-3, 0x1.56d222a7657a4p-5};
      double R2 = rz_multiply(R, R);
      double tmp1 = rz_add(rz_multiply(R, coeffs[1]), coeffs[0]);
      double tmp2 = rz_add(rz_multiply(R, coeffs[3]), coeffs[2]);
      double tmp3 = rz_add(rz_multiply(R2, coeffs[4]), tmp2);
      double tmp4 = rz_multiply(R2, tmp3);
      y = rz_add(tmp4, tmp1);
    }
  }
  double_x ret = {.d=exp2JBy64[J]};
  ret.x += ((uint64_t)M << 52);
  y = rz_multiply(y, ret.d);
  return y;
}
