#include <math.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
#include <ieee754.h>
#include <math_private.h>

static const double log10_high = 0x2.4d7637p0;
static const double log10_low = 0x7.6aaa2b05ba95cp-28;

/* This version of exp10 is based on sysdeps/ieee754/dbl-64/e_exp2.c.  */

#define CUTOFF (double) 700.0

extern __Float64x2_t _ZGVnN2v_exp (__Float64x2_t);

__attribute__((aarch64_vector_pcs, noinline))
static __Float64x2_t
__scalar_exp10(__Float64x2_t x)
{
  return (__Float64x2_t) { exp10(x[0]), exp10(x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float64x2_t _ZGVnN2v_exp10(__Float64x2_t x)
{
  double c, d, h, arg_high_0, arg_high_1, arg_low_0, arg_low_1;
  double exp_high_0, exp_high_1, exp_low_0, exp_low_1;
  __Float64x2_t g, exp_high, exp_low; 
  int32_t lx_0, lx_1;

  c = x[0];
  d = x[1];
  if (__glibc_unlikely(!__builtin_isnormal (c) || !__builtin_isnormal (d)))
    return __scalar_exp10(x);
  g = __builtin_aarch64_absv2df (x);
  h = __builtin_aarch64_reduc_smax_scal_v2df (g);
  if (__glibc_unlikely(h > CUTOFF))
    return __scalar_exp10(x);

  GET_LOW_WORD (lx_0, c);
  GET_LOW_WORD (lx_1, d);
  lx_0 &= 0xf8000000;
  lx_1 &= 0xf8000000;
  arg_high_0 = c;
  arg_high_1 = d;
  SET_LOW_WORD (arg_high_0, lx_0);
  SET_LOW_WORD (arg_high_1, lx_1);
  arg_low_0 = c - arg_high_0;
  arg_low_1 = d - arg_high_1;
  exp_high_0 = arg_high_0 * log10_high;
  exp_high_1 = arg_high_1 * log10_high;
  exp_low_0 = arg_high_0 * log10_low + arg_low_0 * M_LN10;
  exp_low_1 = arg_high_1 * log10_low + arg_low_1 * M_LN10;
  exp_low = (__Float64x2_t) { exp_low_0, exp_low_1 };
  exp_high = (__Float64x2_t) { exp_high_0, exp_high_1 };
  return _ZGVnN2v_exp (exp_high) * _ZGVnN2v_exp (exp_low);
}
