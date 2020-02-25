#include <math.h>
#include <arm_neon.h>
#include <stdint.h>
#include <math_private.h>
#include <sysdeps/ieee754/flt-32/math_config.h>
#include "libmvec_util.h"

extern __Float32x4_t _ZGVnN4v_logf (__Float32x4_t);

static const float
ivln10     =  4.3429449201e-01, /* 0x3ede5bd9 */
log10_2hi  =  3.0102920532e-01, /* 0x3e9a2080 */
log10_2lo  =  7.9034151668e-07; /* 0x355427db */

#define CALC_Z(__n) \
	k_##__n = (hx_##__n >> 23) - 127; \
	i_##__n  = ((uint32_t) k_##__n & 0x80000000) >> 31; \
	hx_##__n = (hx_##__n & 0x007fffff) | ((0x7f - i_##__n) << 23); \
	y_##__n  = (float) (k_##__n + i_##__n);

__attribute__((aarch64_vector_pcs, noinline)) static float32x4_t
__scalar_log10f (float32x4_t x)
{
  return (float32x4_t) { log10f(x[0]), log10f(x[1]),
			 log10f(x[2]), log10f(x[3]) };
}

__attribute__((aarch64_vector_pcs))
__Float32x4_t _ZGVnN4v_log10f(__Float32x4_t x)
{
  float f, x_0, x_1, x_2, x_3, y_0, y_1, y_2, y_3;
  int32_t i_0, i_1, i_2, i_3, k_0, k_1, k_2, k_3, hx_0, hx_1, hx_2, hx_3;
  __Float32x4_t y, z, vlog10_2lo, vlog10_2hi, vivln10;


  x_0 = x[0];
  x_1 = x[1];
  x_2 = x[2];
  x_3 = x[3];

  f = __builtin_aarch64_reduc_smin_scal_v4sf (x);
  if (f < 1.3)
    return __scalar_log10f (x);

  if (!isnormal (x_0) || !isnormal (x_1) || !isnormal (x_2) || !isnormal (x_3))
    return __scalar_log10f (x);

  GET_FLOAT_WORD(hx_0,x_0);
  GET_FLOAT_WORD(hx_1,x_1);
  GET_FLOAT_WORD(hx_2,x_2);
  GET_FLOAT_WORD(hx_3,x_3);

  CALC_Z(0);
  CALC_Z(1);
  CALC_Z(2);
  CALC_Z(3);

  SET_FLOAT_WORD(x_0, hx_0);
  SET_FLOAT_WORD(x_1, hx_1);
  SET_FLOAT_WORD(x_2, hx_2);
  SET_FLOAT_WORD(x_3, hx_3);

  vlog10_2lo = (__Float32x4_t) { log10_2lo, log10_2lo, log10_2lo, log10_2lo };
  vlog10_2hi = (__Float32x4_t) { log10_2hi, log10_2hi, log10_2hi, log10_2hi };
  vivln10 = (__Float32x4_t) { ivln10, ivln10, ivln10, ivln10 };

  x = (__Float32x4_t) {x_0, x_1, x_2, x_3};
  y = (__Float32x4_t) {y_0, y_1, y_2, y_3};
  z  = y * vlog10_2lo + vivln10 * _ZGVnN4v_logf (x);
  return z + y * vlog10_2hi;
}
