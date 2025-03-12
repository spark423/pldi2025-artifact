#include "stdio.h"
#include "stdlib.h"
#include "RoundToOdd.h"

double ComputeOracleResult(float x, mpfr_t m);

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
