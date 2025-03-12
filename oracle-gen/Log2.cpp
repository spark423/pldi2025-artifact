#define __MPFR_ELEM__ mpfr_log2
#include "OracleGenerate.h"

mpfr_t mval;

int main(int argc, char** argv) {
  mpfr_init2(mval, 25);
  mpfr_set_emin(-150);
  mpfr_set_emax(128);
  if (argc != 2) {
      printf("UsageL %s <output file>\n", argv[0]);
      exit(0);
  }
  
  RunTestHelper(argv[1], mval, 0x0, 0x100000000);
  mpfr_clear(mval);
  return 0;
} 
