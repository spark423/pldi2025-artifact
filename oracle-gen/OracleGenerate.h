#include "stdio.h"
#include "stdlib.h"
#include "RoundToOdd.h"

// ComputeOracleResult:
// Given a float input, compute the correctly rouned round-to-odd (ro) result
// in 34-bit floating point representation.
// The oracle must account for every special cases.
double ComputeOracleResult(float x, mpfr_t mval) {
  // TODO : Implement ComputeOracleResult
  if (x == 1.0 / 0.0) return 1.0 / 0.0;
  if (x == 0) return -1.0 / 0.0;
    
  // Set float value to mpfr. This should be exact
  int status = mpfr_set_d(mval, (double)x, MPFR_RNDN);
  if (status != 0) {
      printf("Something went wrong when setting float to mpfr\n");
      exit(0);
  }
  
  // Call appropriate function from MPFR.
  int sticky = __MPFR_ELEM__(mval, mval, MPFR_RNDZ);
  sticky = mpfr_subnormalize(mval, sticky, MPFR_RNDZ);

  // FromMPFRToFloat34RO accepts a MPFR value and turns it into a 34-bit FP
  // value with the ro mode. Also accepts sticky bit.
  return FromMPFRToFloat34Ro(mval, sticky);
}

void RunTestHelper(char* FileName, mpfr_t m, unsigned long start, unsigned long end) {
  unsigned long count = 0;
  
  float x;
  float_x xbase;
  
  FILE* f = fopen(FileName, "w");
  
  for (count = start; count < end; count++) {
    if (count%0x100000 == 0) {
      printf("count = %lx\r", count);
      fflush(stdout);
    }
    xbase.x = count;
    x = xbase.f;
    
    double res = ComputeOracleResult(x, m);
    
    fwrite(&res, sizeof(double), 1, f);
  }
  
  fclose(f);

}
