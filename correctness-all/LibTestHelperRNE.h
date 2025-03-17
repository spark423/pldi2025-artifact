#define _GNU_SOURCE
#pragma STDC FENV_ACCESS on
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "libm.h"
#include "RoundToOdd.h"

// MAXVAL = 0111 1111 0111 1111 1111 1111 1111 1111 11
#define MAXVAL 3.40282361850336062550457001444955389952e+38
// MAXm1VAL = 0111 1111 0111 1111 1111 1111 1111 1111 10
#define MAXm1VAL 3.40282356779733661637539395458142568448e+38

mpfr_t mval;
int fenv_rnd_modes[4] = {FE_TONEAREST, FE_DOWNWARD, FE_UPWARD, FE_TOWARDZERO};

double ComputeOracleResult(float x, mpfr_t mval) {
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

double RoundToFloat34RNO(double val) {
  // Take care of special cases
  if (val == 0.0) return val;
  if (val == 1.0 / 0.0) return val;
  if (val == -1.0 / 0.0) return val;
  if (val > 0) {
    if (val < ldexp(1.0, -150)) return ldexp(1.0, -151);
    if (val > MAXm1VAL) return MAXVAL;
    
  } else {
    if (val > ldexp(-1.0, -150)) return ldexp(-1.0, -151);
    if (val < -MAXm1VAL) return -MAXVAL;
  }
  
  // At this point we have AT LEAST 2 precision bits. Guaranteed 1+ mantissa bit.
  double_x dx;
  dx.d = val;
  
  // Get exp value of val
  int exp;
  double frac = frexp(val, &exp);
  exp--;
  
  // with exp value, figure out how many precision/mantissa bits i get to have
  // # precision = min(26, max(2, 152 + exp))
  // # mantissa  = min(25, max(1, 151 + exp))
  long numMantissa = 151L + exp;
  if (numMantissa < 1) numMantissa = 1;
  if (numMantissa > 25) numMantissa = 25;
  
  unsigned long sticky = dx.x & ((1LU << (52LU - (unsigned long)numMantissa)) - 1LU);
  dx.x -= sticky;
  if (sticky != 0LU) dx.x |= 1LU << (52LU - (unsigned long)numMantissa);
  
  return dx.d;
}

unsigned long RunTestOracle(FILE* f, char* FuncName) {
  float_x x;
  unsigned long wrongResult = 0; 
  unsigned long upperlimit = 1lu << (unsigned long)32;
  for (unsigned long count = 0x0; count < upperlimit; count += 1) {
    x.x = count;
    double_x oracleResult = {.d = ComputeOracleResult(x.f, mval)};
    int all_correct = 1;
    double res = __ELEM__(x.f);
    double_x roundedResult = {.d = RoundToFloat34RNO(res)};
    if (oracleResult.d != oracleResult.d && roundedResult.d != roundedResult.d) continue;
    if (oracleResult.x != roundedResult.x) wrongResult++;
    if (count%0x100000 == 0) { 
      fprintf(f, "No. of inputs tested = 0x%lx; No. of wrong results = %ld\n", count, wrongResult);
    }
  }
  if (wrongResult == 0) {
    printf("All inputs produce the 34RNO oracle result -> \033[0;32mcheck\033[0m    \n");
  } else {
    printf("All inputs produce the 34RNO oracle result -> \033[0;31mincorrect\033[0m\n");
  }
  return wrongResult;
}

void RunTest(char* logFile, char* FuncName) {
  mpfr_init2(mval, 25);
  mpfr_set_emin(-150);
  mpfr_set_emax(128);
  FILE* f = fopen(logFile, "w");
  fprintf(f, "Function: %s\n", FuncName);
  printf("Function: %s\n", FuncName);
  RunTestOracle(f, FuncName);
  fclose(f);
}
