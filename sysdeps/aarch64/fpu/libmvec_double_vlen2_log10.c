#include <math.h>
#include <math_private.h>
#include <stdint.h>
#include <libc-symbols.h>

extern __Float64x2_t _ZGVnN2v_log(__Float64x2_t);

static const double ivln10 = 4.34294481903251816668e-01;        /* 0x3FDBCB7B, 0x1526E50E */
static const double log10_2hi = 3.01029995663611771306e-01;     /* 0x3FD34413, 0x509F6000 */
static const double log10_2lo = 3.69423907715893078616e-13;     /* 0x3D59FEF3, 0x11F12B36 */

__attribute__((aarch64_vector_pcs, noinline))
static __Float64x2_t
__scalar_log10(__Float64x2_t x)
{
  return (__Float64x2_t) { log10 (x[0]), log10 (x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float64x2_t _ZGVnN2v_log10(__Float64x2_t x)
{
  double c, d, y_0, y_1;
  int32_t i_0, i_1, k_0, k_1, hx_0, hx_1;
  __Float64x2_t y, vlog10_2hi, vlog10_2lo, vivln10, z;

  /* The algorithm used here is not accurate enough for
     numbers that are less than 1.32.  This test also catches zero
     and negative numbers which need special handling not in
     _ZGVnN2v_log10.  */
  c = x[0];
  d = x[1];
  if (c <= 1.32 || d <= 1.32)
    return __scalar_log10(x);

  /* Check for Inf/Nan which are not handled either  */
  if (!__builtin_isnormal (c) || !__builtin_isnormal (d))
    return __scalar_log10(x);

  GET_HIGH_WORD (hx_0, c);
  GET_HIGH_WORD (hx_1, d);
  k_0 = (hx_0 >> 20) - 1023;
  k_1 = (hx_1 >> 20) - 1023;
  i_0 = ((uint32_t) k_0 & 0x80000000) >> 31;
  i_1 = ((uint32_t) k_1 & 0x80000000) >> 31;
  hx_0 = (hx_0 & 0x000fffff) | ((0x3ff - i_0) << 20);
  hx_1 = (hx_1 & 0x000fffff) | ((0x3ff - i_1) << 20);
  y_0 = (double) (k_0 + i_0);
  y_1 = (double) (k_1 + i_1);
  y = (__Float64x2_t) { y_0, y_1 };
  SET_HIGH_WORD (c, hx_0);
  SET_HIGH_WORD (d, hx_1);
  x = (__Float64x2_t) { c, d };
  vlog10_2hi = (__Float64x2_t) { log10_2hi, log10_2hi };
  vlog10_2lo = (__Float64x2_t) { log10_2lo, log10_2lo };
  vivln10 = (__Float64x2_t) { ivln10, ivln10 };
  z = y * vlog10_2lo + vivln10 * _ZGVnN2v_log (x);
  return z + y * vlog10_2hi;
}
