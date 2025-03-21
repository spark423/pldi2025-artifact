#include "mathhelper.h"

double ourlibm_sinpif_rz(float x) {
  float_x fX;
  fX.f = x;
  int s = fX.x>>31;
  double sgns[2] = {1.0, -1.0};
  fX.x &= 0x7FFFFFFF;
  
  if (fX.x <= 0x33fc1537) {
    if (__builtin_expect(fX.x == 0x33cd01d7, 0)) return 0x1.4206478p-22*sgns[s];
    return rz_multiply(x, 0x1.921fb54442d48p+1);
  }
  if (fX.x >= 0x4b000000) {
    if (fX.x >= 0x7f800000) {
        return 0.0/0.0;
    }
    return __builtin_copysign(0.0, x);
  }  
  double n_int = __builtin_roundeven(x * 256.0); 
  double z = fma(-n_int, 0.00390625, x);
  double_x NX = {.d = 0x1.8p52 + n_int};
  int N = NX.x;
  unsigned N2 = (N&0x7f);
  if (z == 0.0 && N2 == 0) {
    unsigned mask = N>>31;
    unsigned I = ((N^mask)-mask)>>7;
    if (I&0x1) {
      s ^= ((I&0x2)>>1);
      return 1.0*sgns[s];
    } else {
      return __builtin_copysign(0.0, x);
    }
  }
  double sinpiK = sinpiMBy256TwoPi[N&511];
  double cospiK = sinpiMBy256TwoPi[(N+128)&511]; 
  double z2 = rz_multiply(z, z); 
  //y=0x1.0000000000005p+0 x^(0) + -0x1.3bd3cc9f88f41p+2 x^(2) + 0x1.03d1058565a7p+2 x^(4)
  double cospiZ = rz_add(rz_multiply(z2, 0x1.03d1058565a7p+2), -0x1.3bd3cc9f88f41p+2);
  cospiZ = rz_add(rz_multiply(cospiZ, z2), 0x1.0000000000005p+0);
  //y=0x1.921fb54442d18p+1 x^(1) + -0x1.4abbce758b54ap+2 x^(3) + 0x1.4743b9e6ee6ccp+1 x^(5)
  double sinpiZ = rz_add(rz_multiply(z2, 0x1.4743b9e6ee6ccp+1), -0x1.4abbce758b54ap+2);
  sinpiZ = rz_multiply(z, rz_add(rz_multiply(sinpiZ, z2), 0x1.921fb54442d18p+1));
  return rz_add(rz_multiply(cospiK, sinpiZ), rz_multiply(sinpiK, cospiZ));
}
