#pragma STDC FENV_ACCESS on
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <x86intrin.h>

#include "libm.h"

void RunTest(char* filename) {
  unsigned long long time_total = 0;
  unsigned long count = 0;
  unsigned long time_t1, time_t2;
  double res;
  double nan = 0.0;
  unsigned int dummy;

  double sum = 0.0;
  for (count = 0x0; count < 0x100000000; count++) {
    float_x x = {.x = count};
    do {
      time_t1 = __rdtscp(&dummy);
      int rnd = fegetround();
      fesetround(FE_TONEAREST);
      res = __ELEM__(x.f);
      fesetround(rnd);
      time_t2 = __rdtscp(&dummy);
    } while (time_t1 >= time_t2);

    if(res != res){
      nan = nan + 1.0;
    } else{
      float float_res = res;
      sum = sum +  float_res;
    }
    time_total += (time_t2 - time_t1);
  }
  FILE* f = fopen(filename, "a+");
  fprintf(f, "%llu\n", time_total);
  printf("total time = %llu\n", time_total);
  printf("final sum = %a\n", sum);
  fclose(f);
}
