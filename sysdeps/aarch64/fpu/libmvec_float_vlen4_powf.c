#include <math.h>
#include <arm_neon.h>

extern float32x4_t _ZGVnN4v_exp2f(float32x4_t);
extern float32x2_t _ZGVnN2v_exp2f(float32x2_t);
extern float32x4_t _ZGVnN4v_log2f(float32x4_t);
extern float32x2_t _ZGVnN2v_log2f(float32x2_t);

#define CUTOFF 80.0

__attribute__((aarch64_vector_pcs, noinline)) static float32x4_t
__scalar_powfx4 (float32x4_t x, float32x4_t y)
{
  return (float32x4_t) { powf(x[0], y[0]), powf(x[1], y[1]),
			 powf(x[2], y[2]), powf(x[3], y[3]) };
}

__attribute__((aarch64_vector_pcs, noinline)) static float32x2_t
__scalar_powfx2 (float32x2_t x, float32x2_t y)
{
  return (float32x2_t) { powf(x[0], y[0]), powf(x[1], y[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float32x4_t _ZGVnN4vv_powf(__Float32x4_t x, __Float32x4_t y)
{
#if 1
  float x_0, x_1, x_2, x_3, y_0, y_1, y_2, y_3;
  float f, g;

  x_0 = x[0];
  x_1 = x[1];
  x_2 = x[2];
  x_3 = x[3];
  y_0 = y[0];
  y_1 = y[1];
  y_2 = y[2];
  y_3 = y[3];

  if (__glibc_unlikely(!__builtin_isnormal (x_0) || !__builtin_isnormal (x_1)
		    || !__builtin_isnormal (x_2) || !__builtin_isnormal (x_3)))
    return __scalar_powfx4 (x, y);

  if (__glibc_unlikely(!__builtin_isnormal (y_0) || !__builtin_isnormal (y_1)
		    || !__builtin_isnormal (y_2) || !__builtin_isnormal (y_3)))
    return __scalar_powfx4 (x, y);

  f = __builtin_aarch64_reduc_smin_scal_v4sf (x);
  g = __builtin_aarch64_reduc_smin_scal_v4sf (y);

  if (f < 0.0 || g < 0.0)
    return __scalar_powfx4 (x, y);

  f = __builtin_aarch64_reduc_smax_scal_v4sf (x);
  g = __builtin_aarch64_reduc_smax_scal_v4sf (y);

  if (f > CUTOFF || g > CUTOFF)
    return __scalar_powfx4 (x, y);

  return (_ZGVnN4v_exp2f (y * _ZGVnN4v_log2f (x)));
#else
  return __scalar_powfx4 (x, y);
#endif
}


__attribute__((aarch64_vector_pcs))
__Float32x2_t _ZGVnN2vv_powf(__Float32x2_t x, __Float32x2_t y)
{
#if 1
  float x_0, x_1, y_0, y_1;
  float f, g;

  x_0 = x[0];
  x_1 = x[1];
  y_0 = y[0];
  y_1 = y[1];

  if (__glibc_unlikely(!__builtin_isnormal (x_0) || !__builtin_isnormal (x_1)))
    return __scalar_powfx2 (x, y);

  if (__glibc_unlikely(!__builtin_isnormal (y_0) || !__builtin_isnormal (y_1)))
    return __scalar_powfx2 (x, y);

  f = __builtin_aarch64_reduc_smin_scal_v2sf (x);
  g = __builtin_aarch64_reduc_smin_scal_v2sf (y);

  if (f < 0.0 || g < 0.0)
    return __scalar_powfx2 (x, y);

  f = __builtin_aarch64_reduc_smax_scal_v2sf (x);
  g = __builtin_aarch64_reduc_smax_scal_v2sf (y);

  if (f > CUTOFF || g > CUTOFF)
    return __scalar_powfx2 (x, y);

  return (_ZGVnN2v_exp2f (y * _ZGVnN2v_log2f (x)));
#else
  return __scalar_powfx2 (x, y);
#endif
}
