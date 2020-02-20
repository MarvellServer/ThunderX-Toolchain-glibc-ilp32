#include <math.h>
#include <arm_neon.h>
#include <stdint.h>
#include <stdio.h>
#include "libmvec_util.h"

/* Chebyshev constants for cos, range -PI/4 - PI/4.  */
static const double C0 = -0x1.ffffffffe98aep-2;
static const double C1 =  0x1.55555545c50c7p-5;
static const double C2 = -0x1.6c16b348b6874p-10;
static const double C3 =  0x1.a00eb9ac43ccp-16;
static const double C4 = -0x1.23c97dd8844d7p-22;

/* Chebyshev constants for sin, range -PI/4 - PI/4.  */
static const double S0 = -0x1.5555555551cd9p-3;
static const double S1 =  0x1.1111110c2688bp-7;
static const double S2 = -0x1.a019f8b4bd1f9p-13;
static const double S3 =  0x1.71d7264e6b5b4p-19;
static const double S4 = -0x1.a947e1674b58ap-26;

/* PI/2 with 98 bits of accuracy.  */
static const double PI_2_hi = 0x1.921fb544p+0;
static const double PI_2_lo = 0x1.0b4611a626332p-34;

static const double inv_PI_4 = 0x1.45f306dc9c883p+0; /* 4/PI.  */

static const double ones[] = { 1.0, -1.0 };

#define CUTOFF 1000.00

__attribute__((aarch64_vector_pcs, noinline)) static float32x4_t
__scalar_sinf (float32x4_t x)
{
  return (float32x4_t) { sinf(x[0]), sinf(x[1]), sinf(x[2]), sinf(x[3]) };
}

__attribute__((aarch64_vector_pcs))
__Float32x4_t _ZGVnN4v_sinf(__Float32x4_t x)
{
  __Float32x4_t c;
  __Float64x2_t theta2_a, theta2_b;
  __Float64x2_t cs0_a, cs0_b, cs1_a, cs1_b, cs2_a, cs2_b, cs3_a, cs3_b;
  __Float64x2_t cs4_a, cs4_b, ta_a, ta_b, tm_a, tm_b, sx_a, sx_b;
  __Float64x2_t sign_a, sign_b, result_a, result_b;
  double theta_0, theta_1, theta_2, theta_3;
  double theta2_0, theta2_1, theta2_2, theta2_3;
  double abstheta_0, abstheta_1, abstheta_2, abstheta_3;
  double cs0_0, cs0_1, cs0_2, cs0_3, cs1_0, cs1_1, cs1_2, cs1_3;
  double cs2_0, cs2_1, cs2_2, cs2_3, cs3_0, cs3_1, cs3_2, cs3_3;
  double cs4_0, cs4_1, cs4_2, cs4_3;
  double ta_0, ta_1, ta_2, ta_3, tm_0, tm_1, tm_2, tm_3;
  float d, x_0, x_1, x_2, x_3, sign_0, sign_1, sign_2, sign_3;
  unsigned int signbit_0, signbit_1, signbit_2, signbit_3, n_0, n_1, n_2, n_3;

  x_0 = x[0];
  x_1 = x[1];
  x_2 = x[2];
  x_3 = x[3];

  c = __builtin_aarch64_absv4sf (x);
  d = __builtin_aarch64_reduc_smax_scal_v4sf (c);
  /* This algorithm is inexact for large numbers.  */
  if (d > CUTOFF)
    return __scalar_sinf (x);

  /* We need to make sure we return the correct sign for neg zero input.  */
  d = __builtin_aarch64_reduc_smin_scal_v4sf (c);
  if (d == 0.0)
    return __scalar_sinf (x);

  theta_0 = x_0;
  theta_1 = x_1;
  theta_2 = x_2;
  theta_3 = x_3;
  abstheta_0 = fabs (theta_0);
  abstheta_1 = fabs (theta_1);
  abstheta_2 = fabs (theta_2);
  abstheta_3 = fabs (theta_3);
  signbit_0 = isless (x_0, 0);
  signbit_1 = isless (x_1, 0);
  signbit_2 = isless (x_2, 0);
  signbit_3 = isless (x_3, 0);
  n_0 = ((unsigned int) (abstheta_0 * inv_PI_4)) + 1;
  n_1 = ((unsigned int) (abstheta_1 * inv_PI_4)) + 1;
  n_2 = ((unsigned int) (abstheta_2 * inv_PI_4)) + 1;
  n_3 = ((unsigned int) (abstheta_3 * inv_PI_4)) + 1;
  x_0 = n_0 / 2;
  x_1 = n_1 / 2;
  x_2 = n_2 / 2;
  x_3 = n_3 / 2;
  theta_0 = (abstheta_0 - x_0 * PI_2_hi) - x_0 * PI_2_lo;
  theta_1 = (abstheta_1 - x_1 * PI_2_hi) - x_1 * PI_2_lo;
  theta_2 = (abstheta_2 - x_0 * PI_2_hi) - x_2 * PI_2_lo;
  theta_3 = (abstheta_3 - x_1 * PI_2_hi) - x_3 * PI_2_lo;

  /* Call reduced_sin (theta, n, signbit); */

  theta2_0 = theta_0 * theta_0;
  theta2_1 = theta_1 * theta_1;
  theta2_2 = theta_2 * theta_2;
  theta2_3 = theta_3 * theta_3;
  sign_0 = ones[((n_0 >> 2) & 1) ^ signbit_0];
  sign_1 = ones[((n_1 >> 2) & 1) ^ signbit_1];
  sign_2 = ones[((n_2 >> 2) & 1) ^ signbit_2];
  sign_3 = ones[((n_3 >> 2) & 1) ^ signbit_3];

#define CALC(__n) \
	if ((n_##__n & 2) == 0) { \
		cs0_##__n = S0; cs1_##__n = S1; cs2_##__n = S2; cs3_##__n = S3; cs4_##__n = S4; \
		tm_##__n = theta_##__n * theta2_##__n; \
		ta_##__n = theta_##__n; } \
	else { \
		cs0_##__n = C0; cs1_##__n = C1; cs2_##__n = C2; cs3_##__n = C3; cs4_##__n = C4; \
		tm_##__n = theta2_##__n; \
		ta_##__n = 1.0; }


  CALC(0);
  CALC(1);
  CALC(2);
  CALC(3);

  cs0_a = (__Float64x2_t) { cs0_0, cs0_1 };
  cs0_b = (__Float64x2_t) { cs0_2, cs0_3 };
  cs1_a = (__Float64x2_t) { cs1_0, cs1_1 };
  cs1_b = (__Float64x2_t) { cs1_2, cs1_3 };
  cs2_a = (__Float64x2_t) { cs2_0, cs2_1 };
  cs2_b = (__Float64x2_t) { cs2_2, cs2_3 };
  cs3_a = (__Float64x2_t) { cs3_0, cs3_1 };
  cs3_b = (__Float64x2_t) { cs3_2, cs3_3 };
  cs4_a = (__Float64x2_t) { cs4_0, cs4_1 };
  cs4_b = (__Float64x2_t) { cs4_2, cs4_3 };
  theta2_a = (__Float64x2_t) { theta2_0, theta2_1 };
  theta2_b = (__Float64x2_t) { theta2_2, theta2_3 };
  ta_a = (__Float64x2_t) { ta_0, ta_1 };
  ta_b = (__Float64x2_t) { ta_2, ta_3 };
  tm_a = (__Float64x2_t) { tm_0, tm_1 };
  tm_b = (__Float64x2_t) { tm_2, tm_3 };
  sign_a = (__Float64x2_t) { sign_0, sign_1 };
  sign_b = (__Float64x2_t) { sign_2, sign_3 };

  sx_a = cs3_a + theta2_a * cs4_a;
  sx_b = cs3_b + theta2_b * cs4_b;
  sx_a = cs2_a + theta2_a * sx_a;
  sx_b = cs2_b + theta2_b * sx_b;
  sx_a = cs1_a + theta2_a * sx_a;
  sx_b = cs1_b + theta2_b * sx_b;
  sx_a = cs0_a + theta2_a * sx_a;
  sx_b = cs0_b + theta2_b * sx_b;
  sx_a = ta_a + tm_a * sx_a;
  sx_b = ta_b + tm_b * sx_b;
  result_a = sx_a * sign_a;
  result_b = sx_b * sign_b;
  return pack_and_trunc (result_a, result_b);
}
