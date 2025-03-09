#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "libm.h"

uint64_t GetPredecessor(double_x y) {
  if (y.d == 0) {
    return 0x8000000000000001;
  } else if (y.d < 0) {
    return y.x + 1;
  } else {
    return y.x - 1;
  } 
}

uint64_t GetSuccessor(double_x y) {
  if (y.d == 0) {
    return 0x0000000000000001;
  } else if (y.d < 0) {
    return y.x - 1;
  } else {
    return y.x + 1;
  } 
}

int Calc34RNOInterval(double y, double& lb, double& ub) {
  double_x dY = {.d=y};
  int s = (dY.d < 0) ? -1 : 1;
  dY.x &= 0x7FFFFFFFFFFFFFFF;
  double_x lbx, ubx;
  if (dY.d == ldexp(1.0, -151)) {
    lbx.d = 0.0;
    ubx.d = ldexp(1.0, -150);
  } else {
    int shift = 27;
    if (dY.d < ldexp(1.0, -126)) {
      int e = dY.x >> 52L;
      e -= 1023;
      shift = -e - 99;
    }
    lbx.x = (dY.x - (1LL << shift));
    ubx.x = (dY.x + (1LL << shift));
  }
  if (s == -1) {
    double temp = ubx.d;
    ubx.d = -lbx.d;
    lbx.d = -temp;
  }
  lbx.x = GetSuccessor(lbx);
  ubx.x = GetPredecessor(ubx);
  lb = lbx.d;
  ub = ubx.d;
  return 0;
}  

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: %s <Name of the Sin Interval File 1> <Name of the Sin Interval File 2> <Oracle File>\n", argv[0]);
    exit(0);
  }
  FILE* fp_int1 = fopen(argv[1], "w");
  FILE* fp_int2 = fopen(argv[2], "w");
  FILE* fp_oracle = fopen(argv[3], "r");
  float_x x;
  double y;
  unsigned long count;
  for (count=0; count<0x39E89769; ++count) {
    size_t size = fread(&y, sizeof(double), 1, fp_oracle); 
    if (y == 0.0 || y == 1.0 || y == -1.0) {
      continue;
    }
    x.x = count;  
    double roundLB, roundUB;
    Calc34RNOInterval(y, roundLB, roundUB);
    double data_entry[3];
    data_entry[0] = (double)x.f;
    data_entry[1] = roundLB;
    data_entry[2] = roundUB;
    fwrite(&data_entry, sizeof(double), 3, fp_int1);
  }
  for (count=0x39E89769; count<0x3CC90FDB; ++count) {
    size_t size = fread(&y, sizeof(double), 1, fp_oracle);
    if (y == 0.0 || y == 1.0 || y == -1.0) {
      continue;
    }
    x.x = count; 
    double roundLB, roundUB;
    Calc34RNOInterval(y, roundLB, roundUB);
    double data_entry[3];
    data_entry[0] = (double)x.f;
    data_entry[1] = roundLB;
    data_entry[2] = roundUB;
    fwrite(&data_entry, sizeof(double), 3, fp_int2);
  }
  fclose(fp_int1);
  fclose(fp_int2);
  fclose(fp_oracle);
  return 0;
}

