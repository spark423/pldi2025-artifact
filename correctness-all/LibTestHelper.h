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
int fenv_rnd_modes[4] = {FE_TONEAREST, FE_DOWNWARD, FE_UPWARD, FE_TOWARDZERO};
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

  for (unsigned bitlen = numExpBit + 2; bitlen <= numExpBit + 24; bitlen++) {
    unsigned long wrongResult = 0;
    int bias = (1 << (numExpBit - 1)) - 1;
    int emax = (1 << numExpBit) - 1 - bias;
    
    new_emin = 1 - bias - ((int)bitlen - 1 - numExpBit) + 1;
    new_emax = emax;
    
    mpfr_init2(mval, bitlen - numExpBit);
    
    unsigned long upperlimit = 1lu << (unsigned long)bitlen;
    for (unsigned long count = 0; count < upperlimit; count += 1) {
      float x = ConvertBinToFP((unsigned)count, numExpBit, bitlen); 
      for (int rnd_index = 0; rnd_index < 4; rnd_index++) {
        float_x oracleResult = {.f = MpfrResult(x, numExpBit, bitlen, mpfr_rnd_modes[rnd_index])};
	fesetround(fenv_rnd_modes[rnd_index]);
	double res = __ELEM__(x);
        float_x roundedResult = {.f = RoundDoubleToFEN(res, numExpBit, bitlen, my_rnd_modes[rnd_index], 0)};
        if (oracleResult.f != oracleResult.f && roundedResult.f != roundedResult.f) continue;
        if (oracleResult.x != roundedResult.x && wrongResult < 10) wrongResult++;
      }
    }
    
    if (wrongResult == 0) {
      if (bitlen == numExpBit+24) {
	fprintf(f, "Testing FP%u(%d exp bit): check    \n", bitlen, numExpBit);
      } else { 
	fprintf(f, "Testing FP%u(%d exp bit): check    \t", bitlen, numExpBit);
      }
    } else {
      if (bitlen == numExpBit+24) {
	fprintf(f, "Testing FP%u(%d exp bit): incorrect\t", bitlen, numExpBit);
      } else {
	fprintf(f, "Testing FP%u(%d exp bit): incorrect\t", bitlen, numExpBit);
      }
    }
    fflush(f);
    totalWrongResult += wrongResult;
    
    mpfr_clear(mval);
  }
  
  if (totalWrongResult == 0) {
    fprintf(f, "FP reps with %d exp bits: check    \n", numExpBit);
  } else {
    fprintf(f, "FP reps with %d exp bits: incorrect\n", numExpBit);
  }
  if (totalWrongResult == 0) {
    printf("FP reps with %d exp bits: \033[0;32mcheck\033[0m    \n", numExpBit);
  } else {
    printf("FP reps with %d exp bits: \033[0;31mincorrect\033[0m\n", numExpBit);
  }
  return totalWrongResult;
}

void RunTest(char* logFile, char* FuncName) {
  FILE* f = fopen(logFile, "w");
  fprintf(f, "Function: %s\n", FuncName);
  printf("Function: %s\n", FuncName);
  for (int i = 3; i <= 8; i++) {
    RunTestForExponent(i, f, FuncName);
  }
  fclose(f);
}
