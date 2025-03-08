#include "rlibm.h"

double rlibm_exp10f_fma(float x) {
  float_x fx = {.f=x};
  if((fx.x & 0x7FFFFFFF) == 0) return 1.0;
  if(fx.x <= 0x335e5bd7) {
    if(fx.x <= 0x32de5bd8) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  if(fx.x >= 0x421a209b && fx.x <= 0xb2de5bd9) {
    if(fx.x < 0x80000000) {
      if(fx.x < 0x7f800000) return 0x1.ffffff8p+127;
      if(fx.x == 0x7f800000) return 1.0/0.0;
      return 0.0/0.0;
    }
    if(fx.x <= 0xb25e5bd8) return 0x1.ffffff8p-1;
    return 0x1.fffffe8p-1;
  }
  if(fx.x >= 0xc2349e36) {
    if(fx.x == 0xff800000) return 0.0;
    if(fx.x < 0xff800000) return 0x1p-151;
    else return 0.0/0.0;
  }

  switch(fx.x) {
    case 0x00000000:
    case 0x80000000: return 1.0;
    case 0x3f800000: return 10.0;
    case 0x40000000: return 100.0;
    case 0x40400000: return 1000.0;
    case 0x40800000: return 10000.0;
    case 0x40a00000: return 100000.0;
    case 0x40c00000: return 1000000.0;
    case 0x40e00000: return 10000000.0;
    case 0x41000000: return 100000000.0;
    case 0x41100000: return 1000000000.0;
    case 0x41200000: return 10000000000.0;
  }
  double xp = x*LG10X64; 
  int N = (int)xp;
  int N2 = N % 64;
  if(N2<0) N2 += 64;
  int N1 = N-N2;
  int M = N1/64;
  int J = N2;
  double R = __builtin_fma(-N, ONEBY64LG10, x);
  double y = 0.0;
  if (__builtin_expect(R == -0x1.0c34ef4921aa8p-9, 0)) y = 0x1.fd97e302f1dfap-1;
  else if (__builtin_expect(R == -0x1.f0ed19f04c8c8p-10, 0)) y = 0x1.fdc52454c905cp-1;
  else if (__builtin_expect(R == -0x1.5894ap-10, 0)) y = 0x1.fe73e38p-1;
  else if (__builtin_expect(R == 0x1.e2c509064408p-12, 0)) y = 0x1.004582d8120f2p+0;
  else if (__builtin_expect(R == 0x1.fb29438864818p-10, 0)) y = 0x1.0124993c269dbp+0;
  else if (__builtin_expect(R == 0x1.4c203a2d1299p-9, 0)) y = 0x1.017f7d8b0151dp+0;
  else if (__builtin_expect(R == 0x1.7dd5a004eb084p-9, 0)) y = 0x1.01b9145a898cap+0;
  else if (__builtin_expect(R == 0x1.d924c938aa7bcp-9, 0)) y = 0x1.0222feead7746p+0;
  else if (__builtin_expect(R == 0x1.0e9a508751eb4p-8, 0)) y = 0x1.02720e4f294ccp+0;
  else if (__builtin_expect(R == 0x1.0ee0d38864818p-8, 0)) y = 0x1.0272b22894568p+0;
  else {
    //-0x1.0c34ef4921aa8p-9, -0x1.f0ed19f04c8c8p-10, -0x1.5894ap-10, 0x1.e2c509064408p-12, 0x1.fb29438864818p-10, 0x1.4c203a2d1299p-9, 0x1.7dd5a004eb084p-9, 0x1.d924c938aa7bcp-9, 0x1.0e9a508751eb4p-8, 0x1.0ee0d38864818p-8
    //y=0x1.ffffffffffffdp-1 x^(0) + 0x1.26bb1bbb55547p+1 x^(1) + 0x1.53524c7373b8dp+1 x^(2) + 0x1.0470587039be5p+1 x^(3) + 0x1.2bd8812fb3a7p+0 x^(4) + 0x1.17a3381366b94p-1 x^(5) 
    double coeffs[6] = {0x1.ffffffffffffdp-1, 0x1.26bb1bbb55547p+1, 0x1.53524c7373b8dp+1, 0x1.0470587039be5p+1, 0x1.2bd8812fb3a7p+0, 0x1.17a3381366b94p-1}; 
    double R2 = R*R;
    double tmp1 = __builtin_fma(R, coeffs[1], coeffs[0]);
    double tmp2 = __builtin_fma(R, coeffs[3], coeffs[2]);
    double tmp3 = __builtin_fma(R, coeffs[5], coeffs[4]);
    double tmp4 = __builtin_fma(R2, tmp3, tmp2);
    y = __builtin_fma(R2, tmp4, tmp1);
  }
  double_x ret = {.d=exp2JBy64[J]};
  ret.x += ((uint64_t)M << 52);
  y *= ret.d;
  return y;
}
