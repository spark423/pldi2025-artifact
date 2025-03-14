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

mpfr_t mval;
int new_emin, new_emax;

mpfr_rnd_t mpfr_rnd_modes[4] = {MPFR_RNDN, MPFR_RNDD, MPFR_RNDU, MPFR_RNDZ};
enum RoundMode my_rnd_modes[4] = {RNE, RNN, RNP, RNZ};
char* rnd_modes_string[4] = {"RNE", "RNN", "RNP", "RNZ"};

float MpfrResult(float x, int numExpBit, unsigned bitlen, mpfr_rnd_t rnd) { 
  int exact = mpfr_set_d(mval, x, MPFR_RNDZ);
  exact = mpfr_subnormalize(mval, exact, MPFR_RNDZ);
  exact = __MPFR_ELEM__(mval, mval, rnd);
  exact = mpfr_subnormalize(mval, exact, rnd);
  float result = mpfr_get_flt(mval, rnd);
  return result;
}

unsigned long RunTestForExponent(int numExpBit, FILE* f, char* FuncName) {
  unsigned long wrongResult = 0;
  float_x x;
  for (unsigned long count = 0x0; count < 0x100000000; count++) {
    x.x = count;
    for (int rnd_index = 0; rnd_index < 4; rnd_index++) {
      float_x oracleResult = {.f = MpfrResult(x.f, numExpBit, 32, mpfr_rnd_modes[rnd_index])};
      double res = __ELEM__(x.f);
      float_x roundedResult = {.f = (float)res};
      if (oracleResult.f != oracleResult.f && roundedResult.f != roundedResult.f) continue;
      if (oracleResult.x != roundedResult.x) wrongResult++;
    }
    if (count % 0x100000 == 0) {    
      if (wrongResult == 0) fprintf(f, "Binary32: check     (count = %lx)\n", count);
      else fprintf(f, "Binary32: incorrect (count = %lx)\n", count);
      fflush(f);
    }
  }  
  if (wrongResult == 0) {
    printf("Binary32: \033[0;32mcheck\033[0m    \n");
  } else {
    printf("Binary32: \033[0;31mincorrect\033[0m\n");
  }
  return wrongResult;
}

void RunTest(char* logFile, char* FuncName) {
  FILE* f = fopen(logFile, "w");
  fprintf(f, "Function: %s\n", FuncName);
  printf("Function: %s\n", FuncName);
  mpfr_set_emin(-148);
  mpfr_set_emax(128);
  mpfr_init2(mval, 24);
  RunTestForExponent(8, f, FuncName);
  mpfr_clear(mval);
  fclose(f);
}
