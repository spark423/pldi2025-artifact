#include "libm.h"

double rlibm_cosf(float x) {
  float_x fX = {.f=x};
  uint32_t b = fX.x<<1;
  if (b < 0xff000000) {
    int k;
    long long a;
    int s = ((fX.x>>23)&0xff) - 150;
    uint64_t m = (fX.x&0x7FFFFF)|1<<23;
    double z, z2;
    if (b < 0x9d000000) {
      if (b < 0x78921fb6) {
	if (__builtin_expect(b == 0, 0)) return 1.0;
	if (b < 0x73000002) return 0x1.ffffff8p-1;
	//y=0x1.0000000000002p+0 x^(0) + -0x1.00000000752fdp-1 x^(2) + 0x1.5557b658a7321p-5 x^(4)
	z = x;
	z2 = z*z;
	double temp = z2*0x1.5557b658a7321p-5-0x1.00000000752fdp-1;
	return z2*temp+0x1.0000000000002p+0;
      }
      uint64_t p0 = m*0x441529fc27;
      uint64_t p1 = m*0xa2f9836e4e; p1+=(p0>>40);
      k = (p1>>(33-s));
      a = p1<<(31+s);
      if (b > 0x8b400000) a |= ((p0<<24)>>(33-s));
      long sm = a>>63;
      k -= sm;
      z = ((a>>10)<<10)*0x1p-64;
      z2 = z*z;
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      double cospiZ;
      if (__builtin_expect(z == -0x1.6ad140905564p-6, 0)) cospiZ = 0x1.fffffe2611ef2p-1;
      else if (__builtin_expect(z == 0x1.6e3bed4p-21, 0)) cospiZ = 0x1.ffffff8p-1;
      else {
	//-0x1.6ad140905564p-6, 0x1.6e3bed4p-21
	//y=0x1p+0 x^(0) + -0x1.3bd3cc9c520aep-14 x^(2) + 0x1.03c3e80e4a7p-30 x^(4)
	cospiZ = z2*0x1.03c3e80e4a7p-30-0x1.3bd3cc9c520aep-14;
	cospiZ = cospiZ*z2+0x1p+0;
      }
      double sinpiZ;
      if (__builtin_expect(z == 0x1.f50866898p-20, 0)) sinpiZ = 0x1.8982a08p-26;
      else {
	//0x1.f50866898p-20
	//y=0x1.921fb54442d1p-7 x^(1) + -0x1.4abbce643d53bp-22 x^(3) + 0x1.46a3d63aebfafp-39 x^(5)
	sinpiZ = z2*0x1.46a3d63aebfafp-39-0x1.4abbce643d53bp-22;
	sinpiZ = z*(sinpiZ*z2+0x1.921fb54442d1p-7);
      }
      return cospiK*cospiZ-sinpiK*sinpiZ;
    } else {
      static const uint64_t ipi[] = {0xdb6295993c439041, 0xfc2757d1f534ddc0, 0xa2f9836e4e441529};
      uint128_t p1 = (uint128_t)m*ipi[0];
      uint128_t p2 = (uint128_t)m*ipi[1]; p2 += p1>>64;
      uint128_t p3 = (uint128_t)m*ipi[2]; p3 += p2>>64;
      uint64_t p3h = p3>>64, p3l = p3, p2l = p2, p1l = p1;
      if (s < 57) {
	k = (p3h<<(7+s))|(p3l>>(57-s));
	a = (p3l<<(7+s))|(p2l>>(57-s));
      } else if (s == 57) {
	k = p3l;
	a = p2l;
      } else {
	k = (p3l<<(s-57))|(p2l>>(121-s));
	a = (p2l<<(s-57))|(p1l>>(121-s));
      }
      long sm = a>>63;
      k -= sm;
      z = ((a>>10)<<10)*0x1p-64;
      z2 = z*z;
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      double cospiZ;
      if (__builtin_expect(z == -0x1.4b9e317ebb175p-2, 0)) cospiZ = 0x1.fffef7887a448p-1;
      else if (__builtin_expect(z == -0x1.3d5cf3c8209fp-6, 0)) cospiZ = 0x1.ffffffa2ed8e4p-1;
      else if (__builtin_expect(z == 0x1.8af3288215126p-2, 0)) cospiZ = 0x1.fffe88a4a30e5p-1;
      else {
	//-0x1.4b9e317ebb175p-2, -0x1.3d5cf3c8209fp-6, 0x1.8af3288215126p-2
	//y=0x1.fffffffffffffp-1 x^(0) + -0x1.3bd3cc9c0718ep-14 x^(2) + 0x1.03c2d39a40a99p-30 x^(4)
	cospiZ = z2*0x1.03c2d39a40a99p-30-0x1.3bd3cc9c0718ep-14;
	cospiZ = cospiZ*z2+0x1.fffffffffffffp-1;
      }
      //y=0x1.921fb54442d3dp-7 x^(1) + -0x1.4abbce838bdbcp-22 x^(3) + 0x1.478184d87873p-39 x^(5)
      double sinpiZ = z2*0x1.478184d87873p-39-0x1.4abbce838bdbcp-22;
      sinpiZ = z*(sinpiZ*z2+0x1.921fb54442d3dp-7);
      return cospiK*cospiZ-sinpiK*sinpiZ;
    }
  } else { 
    return 0.0f/0.0f;
  }
}
