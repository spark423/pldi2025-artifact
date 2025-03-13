#include "libm.h"

double rlibm_sinf(float x) {
  float_x fX = {.f=x};
  uint32_t b = fX.x<<1;
  if (b < 0xff000000) {
    int k;
    long long a;
    int s = ((fX.x>>23)&0xff) - 150;
    uint64_t m = (fX.x&0x7FFFFF)|1<<23;
    double z, z2;
    if (b < 0x9d000000) {
      if (b < 0x79921fb6) { 
	if (b < 0x73d12ed2) return x*0x1.ffffffffffffep-1;
	//y=0x1.000000000001p+0 x^(1) + -0x1.55555558a12d3p-3 x^(3) + 0x1.1112f60e1bacep-7 x^(5)
	z = x;
	z2 = z*z;
	double temp = z2*0x1.1112f60e1bacep-7-0x1.55555558a12d3p-3;
	return z*(z2*temp+0x1.000000000001p+0);
      }
      uint64_t p0 = m*0x441529fc27;
      uint64_t p1 = m*0xa2f9836e4e; p1+=(p0>>40);
      k = (p1>>(33-s));
      a = p1<<(31+s);
      if (b > 0x8b400000) a |= ((p0<<24)>>(33-s));
      long sm = a>>63;
      k -= sm;
      k += (fX.x>>31)<<8;
      z = ((a>>10)<<10)*0x1p-64;
      z2 = z*z;
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      //y=0x1.ffffffffffffdp-1 x^(0) + -0x1.3bd3cc9b3b045p-14 x^(2) + 0x1.03be21c9cfcd4p-30 x^(4)
      double cospiZ = z2*0x1.03be21c9cfcd4p-30-0x1.3bd3cc9b3b045p-14;
      cospiZ = cospiZ*z2+0x1.ffffffffffffdp-1;
      double sinpiZ;
      if (__builtin_expect(z == 0x1.ef72d3a60f64p-8, 0)) sinpiZ = 0x1.851fd78p-14;
      else {
	//0x1.ef72d3a60f64p-8
	//y=0x1.921fb54442d3dp-7 x^(1) + -0x1.4abbce7fc8f5cp-22 x^(3) + 0x1.477019b799b7ep-39 x^(5)
	sinpiZ  = z2*0x1.477019b799b7ep-39-0x1.4abbce7fc8f5cp-22;
	sinpiZ = z*(sinpiZ*z2+0x1.921fb54442d3dp-7);
      }
      return sinpiK*cospiZ+cospiK*sinpiZ;
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
      k += (fX.x>>31)<<8;
      z = ((a>>10)<<10)*0x1p-64;
      z2 = z*z;
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      double cospiZ;
      if (__builtin_expect(z == -0x1.fa7ff5e745c55p-2, 0)) cospiZ = 0x1.fffd9675792fcp-1;
      else if (__builtin_expect(z == -0x1.b4f365d6c2c58p-4, 0)) cospiZ = 0x1.ffffe3bff623cp-1;
      else if (__builtin_expect(z == 0x1.73b15119dad6fp-2, 0)) cospiZ = 0x1.fffeb23f12e5bp-1; 
      else {
	//-0x1.fa7ff5e745c55p-2, -0x1.b4f365d6c2c58p-4, 0x1.73b15119dad6fp-2
	//y=0x1.fffffffffffffp-1 x^(0) + -0x1.3bd3cc9b4c3bp-14 x^(2) + 0x1.03bf30b5e92eep-30 x^(4)
	cospiZ = z2*0x1.03bf30b5e92eep-30-0x1.3bd3cc9b4c3bp-14;
	cospiZ = cospiZ*z2+0x1.fffffffffffffp-1;
      }
      //y=0x1.921fb54442d3dp-7 x^(1) + -0x1.4abbce838bdbcp-22 x^(3) + 0x1.478184d87873p-39 x^(5)
      double sinpiZ = z2*0x1.478184d87873p-39-0x1.4abbce838bdbcp-22;
      sinpiZ = z*(sinpiZ*z2+0x1.921fb54442d3dp-7);
      return sinpiK*cospiZ+cospiK*sinpiZ;
    }
  } else { 
    return 0.0f/0.0f;
  }
}
