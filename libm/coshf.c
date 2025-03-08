#include "rlibm.h"

double rlibm_coshf(float x) {
  float_x fx;
  fx.f = x;
  fx.x &= 0x7fffffff;
  
  // Take care of special cases
  if (fx.x <= 0x39ffffff) {
    if (fx.x == 0) return 1.0;
    if (fx.x <= 0x39b504f3) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  
  if (fx.x >= 0x42b2d4fd) {
      if (fx.x > 0x7f800000) return 0.0/0.0;
      if (fx.x == 0x7f800000) return 1.0 / 0.0;
      return 0x1.ffffff8p+127;
  }
  double n_int = __builtin_trunc((double)fx.f * CONST64BYLN2);
  double_x NX = {.d = 0x1p52 + n_int};
  int N = (int)NX.x; 
  int N2 = N&0x3f;
  int N1 = N - N2;
  int I = N1 >> 6; 
  double sinhH = sinhKLn2[I];
  double coshH = coshKLn2[I];
  double sinhM = sinhKLn2By64[N2];
  double coshM = coshKLn2By64[N2];  
  double sinhHM = sinhH*coshM+coshH*sinhM;
  double coshHM = sinhH*sinhM+coshH*coshM;
  
  double R = __builtin_fma(-n_int, LN2BY64, fx.f);
  double R2 = R*R;

  //y=0x1.0000000000065p+0 x^(1) + 0x1.555555299a90fp-3 x^(3) + 0x1.116adea7782bep-7 x^(5)
  double sinhL = R2*0x1.116adea7782bep-7+0x1.555555299a90fp-3;
  sinhL = R*(sinhL*R2+0x1.0000000000065p+0);
  double coshL;
  if (__builtin_expect(R == 0x1.d2fd8bccca2c4p-9, 0)) coshL = 0x1.00006a22acbp+0;
  else {
    //0x1.d2fd8bccca2c4p-9
    //y=0x1.0000000000002p+0 x^(0) + 0x1.fffffffdbb4f2p-2 x^(2) + 0x1.555833375d5e2p-5 x^(4)
    coshL = R2*0x1.555833375d5e2p-5+0x1.fffffffdbb4f2p-2;
    coshL = coshL*R2+0x1.0000000000002p+0;
  }
  return sinhHM*sinhL+coshHM*coshL;
}
