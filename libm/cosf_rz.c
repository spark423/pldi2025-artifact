#include "mathhelper.h"

double rlibm_cosf_rz(float x) {
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
	z = x;
	z2 = rz_multiply(z, z);
	//y=0x1.0000000000002p+0 x^(0) + -0x1.00000000752fdp-1 x^(2) + 0x1.5557b658a7321p-5 x^(4)
	double temp = rz_add(rz_multiply(z2, 0x1.5557b658a7321p-5), -0x1.00000000752fdp-1);
	return rz_add(rz_multiply(temp, z2), 0x1.0000000000002p+0);
      }
      uint64_t p0 = m*0x441529fc27;
      uint64_t p1 = m*0xa2f9836e4e; p1+=(p0>>40);
      k = (p1>>(33-s));
      a = p1<<(31+s);
      if (b > 0x8b400000) a |= ((p0<<24)>>(33-s));
      long sm = a>>63;
      k -= sm;
      z = ((a>>10)<<10)*0x1p-64;
      z2 = rz_multiply(z, z);
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      double cospiZ;
      if (__builtin_expect(z == -0x1.edab45ad2523p-2, 0)) cospiZ = 0x1.fffdb43b9fd5p-1;
      else if (__builtin_expect(z == -0x1.6ad140905564p-6, 0)) cospiZ = 0x1.fffffe2611ef3p-1;
      else {
	//-0x1.edab45ad2523p-2, -0x1.6ad140905564p-6
	//y=0x1p+0 x^(0) + -0x1.3bd3cc9c7498ep-14 x^(2) + 0x1.03c63bd9ad8b2p-30 x^(4) 
	cospiZ = rz_add(rz_multiply(z2, 0x1.03c63bd9ad8b2p-30), -0x1.3bd3cc9c7498ep-14);
	cospiZ = rz_add(rz_multiply(cospiZ, z2), 0x1p+0);
      }
      double sinpiZ;
      if (__builtin_expect(z == 0x1.f50866898p-20, 0)) sinpiZ = 0x1.8982a08p-26;
      else {
	//0x1.f50866898p-20
	//y=0x1.921fb54442cfbp-7 x^(1) + -0x1.4abbce5acf646p-22 x^(3) + 0x1.4664e926983a1p-39 x^(5) 
	sinpiZ = rz_add(rz_multiply(z2, 0x1.4664e926983a1p-39), -0x1.4abbce5acf646p-22);
	sinpiZ = rz_multiply(z, rz_add(rz_multiply(sinpiZ, z2), 0x1.921fb54442cfbp-7));
      }
      return rz_add(rz_multiply(cospiK, cospiZ), rz_multiply(-sinpiK, sinpiZ));
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
      z2 = rz_multiply(z, z);
      double sinpiK = sinpiMBy256TwoPi[k&511];
      double cospiK = sinpiMBy256TwoPi[(k+128)&511];
      double cospiZ;
      if (__builtin_expect(z == -0x1.bb0c2d47cfd2cp-2, 0)) cospiZ = 0x1.fffe266eed5ecp-1;
      else if (__builtin_expect(z == -0x1.5d823ac42b395p-2, 0)) cospiZ = 0x1.fffed9124fb55p-1;
      else if (__builtin_expect(z == -0x1.0788e4762434p-2, 0)) cospiZ = 0x1.ffff57fef757p-1;
      else if (__builtin_expect(z == -0x1.aafc551c92bf8p-4, 0)) cospiZ = 0x1.ffffe579a26f1p-1;
      else if (__builtin_expect(z == -0x1.3d5cf3c8209fp-6, 0)) cospiZ = 0x1.ffffffa2ed8e5p-1;
      else if (__builtin_expect(z == 0x1.58f335ff0f9d9p-2, 0)) cospiZ = 0x1.fffee0c5cde98p-1;
      else {
	//-0x1.bb0c2d47cfd2cp-2, -0x1.5d823ac42b395p-2, -0x1.0788e4762434p-2, -0x1.aafc551c92bf8p-4, -0x1.3d5cf3c8209fp-6, 0x1.58f335ff0f9d9p-2
	//y=0x1p+0 x^(0) + -0x1.3bd3cc9bb8911p-14 x^(2) + 0x1.03c26191a092ep-30 x^(4)
	cospiZ = rz_add(rz_multiply(z2, 0x1.03c26191a092ep-30), -0x1.3bd3cc9bb8911p-14);
	cospiZ = rz_add(rz_multiply(cospiZ, z2), 0x1p+0);
      }
      //y=0x1.921fb54442d2ep-7 x^(1) + -0x1.4abbce7468105p-22 x^(3) + 0x1.471cf9d459e7cp-39 x^(5)
      double sinpiZ = rz_add(rz_multiply(z2, 0x1.471cf9d459e7cp-39), -0x1.4abbce7468105p-22);
      sinpiZ = rz_multiply(z, rz_add(rz_multiply(sinpiZ, z2), 0x1.921fb54442d2ep-7));
      return rz_add(rz_multiply(cospiK, cospiZ), rz_multiply(-sinpiK, sinpiZ));
    }
  } else { 
    return 0.0f/0.0f;
  }
}
