#include <math.h>
#include <arm_neon.h>
#include <stdint.h>
#include <sysdeps/ieee754/flt-32/math_config.h>
#include "libmvec_util.h"

#define N (1 << EXP2F_TABLE_BITS)
#define LIMIT 128.0

#define T __exp2f_data.tab
#define C __exp2f_data.poly
#define SHIFT __exp2f_data.shift_scaled

__attribute__((aarch64_vector_pcs, noinline)) static float32x4_t
__scalar_exp2fx4 (float32x4_t x)
{
  return (float32x4_t) { exp2f(x[0]), exp2f(x[1]), exp2f(x[2]), exp2f(x[3]) };
}

__attribute__((aarch64_vector_pcs, noinline)) static float32x2_t
__scalar_exp2fx2 (float32x2_t x)
{
  return (float32x2_t) { exp2f(x[0]), exp2f(x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float32x4_t _ZGVnN4v_exp2f(__Float32x4_t x)
{
  __Float32x4_t g, result;
  __Float64x2_t z_0, z_1, r_0, r_1;
  __Float64x2_t vs_0, vs_1, c0, c1, c2, y_0, y_1, r2_0, r2_1, one;
  uint64_t ki_0, ki_1, ki_2, ki_3, t_0, t_1, t_2, t_3;
  double s_0, s_1, s_2, s_3, kd_0, kd_1, kd_2, kd_3, rr_0, rr_1, rr_2, rr_3;
  double xd_0, xd_1, xd_2, xd_3;
  float f, x_0, x_1, x_2, x_3;

  x_0 = x[0];
  x_1 = x[1];
  x_2 = x[2];
  x_3 = x[3];
  g = __builtin_aarch64_absv4sf (x);
  f = __builtin_aarch64_reduc_smax_scal_v4sf (g);
  if (f >= LIMIT)
    return __scalar_exp2fx4 (x);
  if (!isnormal (x_0) || !isnormal (x_1) || !isnormal (x_2) || !isnormal (x_3))
    return __scalar_exp2fx4 (x);

  xd_0 = x_0; 
  xd_1 = x_1;
  xd_2 = x_2; 
  xd_3 = x_3;

  kd_0 = (double) (xd_0 + SHIFT);
  kd_1 = (double) (xd_1 + SHIFT);
  kd_2 = (double) (xd_2 + SHIFT);
  kd_3 = (double) (xd_3 + SHIFT);

  /* x = k/N + r with r in [-1/(2N), 1/(2N)] and int k.  */

  ki_0 = asuint64 (kd_0);
  ki_1 = asuint64 (kd_1);
  ki_2 = asuint64 (kd_2);
  ki_3 = asuint64 (kd_3);

  kd_0 -= SHIFT;
  kd_1 -= SHIFT;
  kd_2 -= SHIFT;
  kd_3 -= SHIFT;

  rr_0 = xd_0 - kd_0;
  rr_1 = xd_1 - kd_1;
  rr_2 = xd_2 - kd_2;
  rr_3 = xd_3 - kd_3;

  r_0 = (__Float64x2_t) { rr_0, rr_1 };
  r_1 = (__Float64x2_t) { rr_2, rr_3 };

  t_0 = T[ki_0 % N]; 
  t_1 = T[ki_1 % N]; 
  t_2 = T[ki_2 % N]; 
  t_3 = T[ki_3 % N]; 

  t_0 += ki_0 << (52 - EXP2F_TABLE_BITS);
  t_1 += ki_1 << (52 - EXP2F_TABLE_BITS);
  t_2 += ki_2 << (52 - EXP2F_TABLE_BITS);
  t_3 += ki_3 << (52 - EXP2F_TABLE_BITS);

  s_0 = asdouble (t_0);
  s_1 = asdouble (t_1);
  s_2 = asdouble (t_2);
  s_3 = asdouble (t_3);

  vs_0 = (__Float64x2_t) { s_0, s_1 };
  vs_1 = (__Float64x2_t) { s_2, s_3 };
  c0 = (__Float64x2_t) { C[0], C[0] };
  c1 = (__Float64x2_t) { C[1], C[1] };
  c2 = (__Float64x2_t) { C[2], C[2] };
  one = (__Float64x2_t) { 1.0, 1.0 };

  z_0 = c0 * r_0 + c1;
  z_1 = c0 * r_1 + c1;
  r2_0 = r_0 * r_0;
  r2_1 = r_1 * r_1;
  y_0 = c2 * r_0 + one;
  y_1 = c2 * r_1 + one;
  y_0 = z_0 * r2_0 + y_0;
  y_1 = z_1 * r2_1 + y_1;
  y_0 = y_0 * vs_0;
  y_1 = y_1 * vs_1;
  result = pack_and_trunc (y_0, y_1);
  return result;
}

__attribute__((aarch64_vector_pcs))
__Float32x2_t _ZGVnN2v_exp2f(__Float32x2_t x)
{
  __Float32x2_t g, result;
  __Float64x2_t z, r;
  __Float64x2_t vs, c0, c1, c2, y, r2, one;
  uint64_t ki_0, ki_1, t_0, t_1;
  double s_0, s_1, kd_0, kd_1, rr_0, rr_1;
  double xd_0, xd_1;
  float f, x_0, x_1;

  x_0 = x[0];
  x_1 = x[1];
  g = __builtin_aarch64_absv2sf (x);
  f = __builtin_aarch64_reduc_smax_scal_v2sf (g);
  if (f >= LIMIT)
    return __scalar_exp2fx2 (x);
  if (!isnormal (x_0) || !isnormal (x_1))
    return __scalar_exp2fx2 (x);

  xd_0 = x_0; 
  xd_1 = x_1;

  kd_0 = (double) (xd_0 + SHIFT);
  kd_1 = (double) (xd_1 + SHIFT);

  /* x = k/N + r with r in [-1/(2N), 1/(2N)] and int k.  */

  ki_0 = asuint64 (kd_0);
  ki_1 = asuint64 (kd_1);

  kd_0 -= SHIFT;
  kd_1 -= SHIFT;

  rr_0 = xd_0 - kd_0;
  rr_1 = xd_1 - kd_1;

  r = (__Float64x2_t) { rr_0, rr_1 };

  t_0 = T[ki_0 % N]; 
  t_1 = T[ki_1 % N]; 

  t_0 += ki_0 << (52 - EXP2F_TABLE_BITS);
  t_1 += ki_1 << (52 - EXP2F_TABLE_BITS);

  s_0 = asdouble (t_0);
  s_1 = asdouble (t_1);

  vs = (__Float64x2_t) { s_0, s_1 };
  c0 = (__Float64x2_t) { C[0], C[0] };
  c1 = (__Float64x2_t) { C[1], C[1] };
  c2 = (__Float64x2_t) { C[2], C[2] };
  one = (__Float64x2_t) { 1.0, 1.0 };

  z = c0 * r + c1;
  r2 = r * r;
  y = c2 * r + one;
  y = z * r2 + y;
  y = y * vs;
  result = (float32x2_t) { y[0], y[1] };
  return result;
}
