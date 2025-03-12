#include "OracleGenerate.h"

mpfr_t mval;
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
  
  // Call MPFR's log function.
  int sticky = mpfr_log(mval, mval, MPFR_RNDZ);
  sticky = mpfr_subnormalize(mval, sticky, MPFR_RNDZ);

  // FromMPFRToFloat34RO accepts a MPFR value and turns it into a 34-bit FP
  // value with the ro mode. Also accepts sticky bit.
  return FromMPFRToFloat34Ro(mval, sticky);
}

int main(int argc, char** argv) {
  mpfr_init2(mval, 25);
  mpfr_set_emin(-150);
  mpfr_set_emax(128);
  if (argc != 2) {
      printf("UsageL %s <output file>\n", argv[0]);
      exit(0);
  }
  
  // TODO : Set the range of inputs to generate oracle for. This example
  RunTestHelper(argv[1], mval, 0x0, 0x80000000);
  mpfr_clear(mval);
  return 0;
} 
