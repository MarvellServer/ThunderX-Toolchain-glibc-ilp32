#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
#include <ieee754.h>
#include <math-narrow-eval.h>
#include "math_config.h"

#define N (1 << EXP_TABLE_BITS)
#define Shift __exp_data.exp2_shift
#define T __exp_data.tab
#define C1 __exp_data.exp2_poly[0]
#define C2 __exp_data.exp2_poly[1]
#define C3 __exp_data.exp2_poly[2]
#define C4 __exp_data.exp2_poly[3]
#define C5 __exp_data.exp2_poly[4]

/* This version of exp2 is based on sysdeps/ieee754/dbl-64/e_exp2.c.  */

#define CUTOFF (double) 700.0

__attribute__((aarch64_vector_pcs, noinline))
static __Float64x2_t
__scalar_exp2(__Float64x2_t x)
{
  return (__Float64x2_t) { exp2(x[0]), exp2(x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float64x2_t _ZGVnN2v_exp2(__Float64x2_t x)
{
  __Float64x2_t g, kd_v, r_v, r2_v, tail_v, scale_v, tmp_v;
  __Float64x2_t C1_v, C2_v, C3_v, C4_v, C5_v;
  double c, d, h, kd_0, kd_1;
  uint64_t ki_0, ki_1, idx_0, idx_1, top_0, top_1, sbits_0, sbits_1;

  c = x[0];
  d = x[1];
  if (__glibc_unlikely(!__builtin_isnormal (c) || !__builtin_isnormal (d)))
    return __scalar_exp2 (x);
  g = __builtin_aarch64_absv2df (x);
  h = __builtin_aarch64_reduc_smax_scal_v2df (g);
  if (__glibc_unlikely(h > CUTOFF))
    return __scalar_exp2 (x);

  kd_0 = math_narrow_eval (x[0] + Shift);
  kd_1 = math_narrow_eval (x[1] + Shift);
  ki_0 = asuint64 (kd_0);
  ki_1 = asuint64 (kd_1);
  kd_0 -= Shift;
  kd_1 -= Shift;
  idx_0 = 2 * (ki_0 % N);
  idx_1 = 2 * (ki_1 % N);
  top_0 = ki_0 << (52 - EXP_TABLE_BITS);
  top_1 = ki_1 << (52 - EXP_TABLE_BITS);
  sbits_0 = T[idx_0 + 1] + top_0;
  sbits_1 = T[idx_1 + 1] + top_1;
  C1_v = (__Float64x2_t) { C1, C1 };
  C2_v = (__Float64x2_t) { C2, C2 };
  C3_v = (__Float64x2_t) { C3, C3 };
  C4_v = (__Float64x2_t) { C4, C4 };
  C5_v = (__Float64x2_t) { C5, C5 };

  kd_v = (__Float64x2_t) { kd_0, kd_1 };

  r_v = x - kd_v;
  r2_v = r_v * r_v;
  tail_v = (__Float64x2_t) { asdouble (T[idx_0]), asdouble (T[idx_1]) };
  scale_v = (__Float64x2_t) { asdouble (sbits_0), asdouble (sbits_1) };
  tmp_v = tail_v + r_v * C1_v + r2_v * (C2_v + r_v * C3_v) + r2_v * r2_v * (C4_v + r_v * C5_v);
  return scale_v + scale_v * tmp_v;
}
