#define _GNU_SOURCE
#pragma STDC FENV_ACCESS on
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "mpfr.h"

#include "libm.h"
#include "rounding.h"

#define MAX_STRIDE 19u

mpfr_t mval;
int new_emin, new_emax;

mpfr_rnd_t mpfr_rnd_modes[4] = {MPFR_RNDN, MPFR_RNDD, MPFR_RNDU, MPFR_RNDZ};
enum RoundMode my_rnd_modes[4] = {RNE, RNN, RNP, RNZ};
char* rnd_modes_string[4] = {"RNE", "RNN", "RNP", "RNZ"};

float MpfrResult(float x, int numExpBit, unsigned bitlen, mpfr_rnd_t rnd) { 
  mpfr_set_emin(new_emin);
  mpfr_set_emax(new_emax);
  int exact = mpfr_set_d(mval, x, MPFR_RNDZ);
  exact = mpfr_subnormalize(mval, exact, MPFR_RNDZ);
  exact = __MPFR_ELEM__(mval, mval, rnd);
  exact = mpfr_subnormalize(mval, exact, rnd);
  float result = mpfr_get_flt(mval, rnd);

  return result;
}

unsigned long RunTestForExponent(int numExpBit, FILE* f, char* FuncName) {
  unsigned long totalWrongResult = 0;
  unsigned bitlen = 32; 
  unsigned long wrongResult = 0;
  int bias = (1 << (numExpBit - 1)) - 1;
  int emax = (1 << numExpBit) - 1 - bias;
  
  new_emin = 1 - bias - ((int)bitlen - 1 - numExpBit) + 1;
  new_emax = emax;
  
  mpfr_init2(mval, bitlen - numExpBit);
 
  unsigned long upperlimit = 1lu << (unsigned long)bitlen;
  for (unsigned long count = 0x0; count < upperlimit; count++) {
    float x = ConvertBinToFP((unsigned)count, numExpBit, bitlen); 
    for (int rnd_index = 0; rnd_index < 4; rnd_index++) {
      float_x oracleResult = {.f = MpfrResult(x, numExpBit, bitlen, mpfr_rnd_modes[rnd_index])};
      double res = __ELEM__(x);
      float_x roundedResult = {.f = RoundDoubleToFEN(res, numExpBit, bitlen, my_rnd_modes[rnd_index], 0)};
      if (oracleResult.f != oracleResult.f && roundedResult.f != roundedResult.f) continue;
      if (oracleResult.x != roundedResult.x && wrongResult < 10) wrongResult++;
    }
  }
  
  if (wrongResult == 0) fprintf(f, "Binary32: check    \n");
  else fprintf(f, "Binary32: incorrect\n");
  fflush(f);
  totalWrongResult += wrongResult;
  
  mpfr_clear(mval);
  
  if (totalWrongResult == 0) {
    fprintf(f, "Binary32: check    \n");
  } else {
    fprintf(f, "Binary32: incorrect\n");
  }
  if (totalWrongResult == 0) {
    printf("Binary32: \033[0;32mcheck\033[0m    \n");
  } else {
    printf("Binary32: \033[0;31mincorrect\033[0m\n");
  }
  return totalWrongResult;
}

void RunTest(char* logFile, char* FuncName) {
  FILE* f = fopen(logFile, "w");
  fprintf(f, "Function: %s\n", FuncName);
  printf("Function: %s\n", FuncName);
  RunTestForExponent(8, f, FuncName);
  fclose(f);
}
