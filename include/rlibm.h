#ifndef RLIBM_H
#define RLIBM_H

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
double rlibm_cosf_fma(float);
double rlibm_coshf_fma(float);
double rlibm_cospif_fma(float);
double rlibm_expf_fma(float);
double rlibm_expf_fma(float);
double rlibm_exp2f_fma(float);
double rlibm_exp10f_fma(float);
double rlibm_logf_fma(float);
double rlibm_log2f_fma(float);
double rlibm_log10f_fma(float);
double rlibm_sinf_fma(float);
double rlibm_sinhf_fma(float);
double rlibm_sinpif_fma(float);
double rlibm_cosf_rz(float);
double rlibm_coshf_rz(float);
double rlibm_cospif_rz(float);
double rlibm_expf_rz(float);
double rlibm_exp2f_rz(float);
double rlibm_exp10f_rz(float);
double rlibm_logf_rz(float);
double rlibm_log2f_rz(float);
double rlibm_log10f_rz(float);
double rlibm_sinf_rz(float);
double rlibm_sinhf_rz(float);
double rlibm_sinpif_rz(float);
double rlibm_cosf_og(float);
double rlibm_coshf_og(float);
double rlibm_cospif_og(float);
double rlibm_expf_og(float);
double rlibm_exp2f_og(float);
double rlibm_exp10f_og(float);
double rlibm_logf_og(float);
double rlibm_log2f_og(float);
double rlibm_log10f_og(float);
double rlibm_sinf_og(float);
double rlibm_sinhf_og(float);
double rlibm_sinpif_og(float);

//Core-Math functions
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
