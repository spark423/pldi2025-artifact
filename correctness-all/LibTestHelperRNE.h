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
#include "rounding.h"
#include "RoundToOdd.h"

mpfr_t mval;
int fenv_rnd_modes[4] = {FE_TOWARDZERO, FE_TONEAREST, FE_UPWARD, FE_DOWNWARD};
enum RoundMode my_rnd_modes[4] = {RNZ, RNE, RNP, RNN};

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

void RunTestOracle(FILE *f) {
  for (unsigned bitlen = 10; bitlen <= 32; bitlen++) {
    unsigned long wrongResults = 0;
    unsigned long upperlimit = 1lu << (unsigned long)bitlen;
    for (unsigned long count = 0x0; count < upperlimit; count += 1) {
      int all_correct = 1;
      float_x x = {.f=ConvertBinToFP((unsigned)count, 8, bitlen)};
      double oracle_res = ComputeOracleResult(x.f, mval);
      double res = __ELEM__(x.f);
      for (int rnd_index = 0; rnd_index < 4; rnd_index++) {
        float_x oracleResult = {.f=RoundDoubleToF8N(oracle_res, bitlen, my_rnd_modes[rnd_index])};
        float_x roundedResult = {.f=RoundDoubleToF8N(res, bitlen, my_rnd_modes[rnd_index])};
        if (oracleResult.x != oracleResult.x && roundedResult.x != roundedResult.x) continue;
        if (oracleResult.x != roundedResult.x) all_correct = 0;
      }
      if (!all_correct) wrongResults++;
      if (count%0x100000 == 0) {
	fprintf(f, "Testing FP%u(8 exp bits): count = 0x%lx, wrong results = %ld\r", bitlen, count, wrongResults);
	fflush(f);
      }
    }
    if (wrongResults == 0) {
      printf("FP%u(8 exp bits) -> \033[0;32mcheck\033[0m    \n", bitlen);
      fprintf(f, "FP%u(8 exp bits) -> check    \n", bitlen);
    } else {
      printf("FP%u(8 exp bits) -> \033[0;31mincorrect\033[0m\n", bitlen);
      fprintf(f, "FP%u(8 exp bits) -> incorrect\n", bitlen);
    }
  }
}

void RunTest(char* logFile, char* FuncName) {
  mpfr_init2(mval, 25);
  mpfr_set_emin(-150);
  mpfr_set_emax(128);
  FILE* f = fopen(logFile, "w");
  fprintf(f, "Function: %s\n", FuncName);
  printf("Function: %s\n", FuncName);
  RunTestOracle(f);
  fclose(f);
}
