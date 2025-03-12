#ifndef OURLIBM_H
#define OURLIBM_H

#include <errno.h>
#include <fenv.h>
#include <stdint.h>
#include "math.h"

#include "constants.h"

typedef union {
  double d;
  uint64_t x;
} double_x;

typedef union  {
  float f;
  uint32_t x;
} float_x;

struct IntData {
  double lb;
  double ub;
};

typedef unsigned __int128 uint128_t;

//OURLIBM functions
double ourlibm_cosf(float);
double ourlibm_coshf(float);
double ourlibm_cospif(float);
double ourlibm_expf(float);
double ourlibm_exp2f(float);
double ourlibm_exp10f(float);
double ourlibm_logf(float);
double ourlibm_log2f(float);
double ourlibm_log10f(float);
double ourlibm_sinf(float);
double ourlibm_sinhf(float);
double ourlibm_sinpif(float);
double ourlibm_cosf_rz(float);
double ourlibm_coshf_rz(float);
double ourlibm_cospif_rz(float);
double ourlibm_expf_rz(float);
double ourlibm_exp2f_rz(float);
double ourlibm_exp10f_rz(float);
double ourlibm_logf_rz(float);
double ourlibm_log2f_rz(float);
double ourlibm_log10f_rz(float);
double ourlibm_sinf_rz(float);
double ourlibm_sinhf_rz(float);
double ourlibm_sinpif_rz(float);

//RLIBM functions
double rlibm_cosf(float);
double rlibm_coshf(float);
double rlibm_cospif(float);
double rlibm_expf(float);
double rlibm_exp2f(float);
double rlibm_exp10f(float);
double rlibm_logf(float);
double rlibm_log2f(float);
double rlibm_log10f(float);
double rlibm_sinf(float);
double rlibm_sinhf(float);
double rlibm_sinpif(float);

//CORE-MATH functions
float cr_cosf(float);
float cr_coshf(float);
float cr_cospif(float);
float cr_expf(float);
float cr_exp2f(float);
float cr_exp10f(float);
float cr_logf(float);
float cr_log2f(float);
float cr_log10f(float);
float cr_sinf(float);
float cr_sinhf(float);
float cr_sinpif(float);

#endif
