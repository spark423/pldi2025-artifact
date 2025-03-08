#include "rlibm.h"

double rlibm_cospif_fma(float x) {
  float_x fX;
  fX.f = x;
  fX.x &= 0x7FFFFFFF;
  
  if (fX.x <= 0x38A2F983) {
    if (fX.x == 0) return 1.0;
    return 0x1.ffffff8p-1;
  }
  if (fX.x >= 0x4b000000) {
    if (fX.x >= 0x7f800000) {
        return 0.0/0.0;
    }
    if (fX.x >= 0x4b800000) return 1.0;
    if ((fX.x & 0x1) == 0) return 1.0;
    return -1.0;
  } 
  double n_int = __builtin_roundeven(x * 256.0); 
  double z = -n_int*0.00390625+x;
  double_x NX = {.d = 0x1.8p52 + n_int};
  int N = NX.x;
  unsigned N2 = (N&0x7f);
  if (z == 0.0 && N2 == 0) {
    unsigned mask = N>>31;
    unsigned I = (((N^mask)-mask)>>7) + 1;
    if (I&0x1) {
      int s = ((I&0x2)>>1);
      double sgns[2] = {1.0, -1.0};
      return 1.0*sgns[s];
    } else {
      return 0.0;
    }
  }
  double sinpiK = sinpiMBy256TwoPi[N&511];
  double cospiK = sinpiMBy256TwoPi[(N+128)&511]; 
  double z2 = z*z;
  //y=0x1.000000000000dp+0 x^(0) + -0x1.3bd3cca15859ep+2 x^(2) + 0x1.03dc724f908f9p+2 x^(4)
  double cospiZ = __builtin_fma(z2, 0x1.03dc724f908f9p+2, -0x1.3bd3cca15859ep+2);
  cospiZ = __builtin_fma(cospiZ, z2, 0x1.000000000000dp+0);
  //y=0x1.921fb54442e42p+1 x^(1) + -0x1.4abbcf1abbae6p+2 x^(3) + 0x1.4d4e5d12b06b7p+1 x^(5)
  double sinpiZ = __builtin_fma(z2, 0x1.4d4e5d12b06b7p+1, -0x1.4abbcf1abbae6p+2);
  sinpiZ = z*__builtin_fma(sinpiZ,z2,0x1.921fb54442e42p+1);
  return __builtin_fma(cospiK, cospiZ, -sinpiK*sinpiZ);
}
