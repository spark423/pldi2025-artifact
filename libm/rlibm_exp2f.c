#include "libm.h"

double rlibm_exp2f(float x) { 
  double_x dY;
  float_x fx;
  fx.f = x;
  
  // Take care of special cases
  if ((fx.x & 0x7FFFFFFF) == 0) return 1.0;
  
  if (fx.x <= 0x3438aa3a) {
    if (fx.x <= 0x33b8aa3a) return 0x1.0000008p+0;
    return 0x1.0000018p+0;
  }
  
  if (0x43000000 <= fx.x && fx.x <= 0xb3b8aa3b) {
    if (fx.x < 0x80000000) {
      if (fx.x < 0x7F800000) return 0x1.ffffff8p+127; 
      if (fx.x == 0x7F800000) return 1.0 / 0.0;
      return 0.0/0.0;
    }
    
    // negative counterpart
    if (fx.x <= 0xb338aa3b) return 0x1.ffffff8p-1;
    
    return 0x1.fffffe8p-1;
  }
  
  if (fx.x >= 0xc3160001) {
    if (fx.x == 0xFF800000) return 0.0; 
    if (fx.x < 0xFF800000) {
      dY.x = 0x3680000000000000;
      return dY.d;
    }
    return 0.0/0.0;
  }
  
  // Perform range reduction
  double xp = x * 64;
  int N = (int)xp;
  int N2 = N % 64;
  if (N2 < 0) N2 += 64;
  int N1 = N - N2;
  
  int M = N1 / 64;
  int J = N2;
  double R = x - N * 0x1p-6;
  
  if (R == 0.0 && N2 == 0) {

    dY.d = 1.0;
    dY.x += ((uint64_t) M << 52);    
    return dY.d;
  }

  double y = 0.0;

  if(R == 0x1.853a6ep-9){
    y = 0x1.0087090000001p+0 ;
  }
  else{
    double coeffs[] = {
		       0x1.fffffffffffffp-1,
		       0x1.62e42fefa3806p-1,
		       0x1.ebfbdff81263ap-3,
		       0x1.c6b08b875921bp-5,
		       0x1.3b2b5ff31806dp-7,
		       0x1.62bcac112f1e1p-10,
    };

    double xsquare = R * R;
    double temp1 = fma(R, coeffs[1], coeffs[0]);
    double temp2 = fma(R, coeffs[5], coeffs[4]);
    double temp3 = fma(R, coeffs[3], coeffs[2]);

    double temp4 = fma(xsquare, temp2, temp3);
    y = fma(xsquare, temp4, temp1);
  }
  
  // Perform output compensation
  
  dY.d = exp2JBy64[J];
  dY.x += ((uint64_t)M << 52);
  y *= dY.d;
  return y;
}
