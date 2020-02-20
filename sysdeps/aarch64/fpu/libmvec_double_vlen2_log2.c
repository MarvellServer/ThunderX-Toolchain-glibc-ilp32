#include <math.h>
#include <math_private.h>
#include <stdint.h>
#include <libc-symbols.h>

static const double ln2 = 0.69314718055994530942;
static const double Lg1 = 6.666666666666735130e-01;     /* 3FE55555 55555593 */
static const double Lg2 = 3.999999999940941908e-01;     /* 3FD99999 9997FA04 */
static const double Lg3 = 2.857142874366239149e-01;     /* 3FD24924 94229359 */
static const double Lg4 = 2.222219843214978396e-01;     /* 3FCC71C5 1D8E78AF */
static const double Lg5 = 1.818357216161805012e-01;     /* 3FC74664 96CB03DE */
static const double Lg6 = 1.531383769920937332e-01;     /* 3FC39A09 D078C69F */
static const double Lg7 = 1.479819860511658591e-01;     /* 3FC2F112 DF3E5244 */

__attribute__((aarch64_vector_pcs, noinline))
static __Float64x2_t
__scalar_log2(__Float64x2_t x)
{
  return (__Float64x2_t) { log2 (x[0]), log2 (x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float64x2_t _ZGVnN2v_log2(__Float64x2_t x)
{
  __Float64x2_t vln2, dk, f, s, z, w, t1, t2, R, rr, result;
  double hfsq, c, d;
  int32_t k_0, k_1, hx_0, hx_1, i_0, i_1, j_0, j_1;

  /* The algorithm used here is not accurate enough for
     numbers that are less than 1.32.  This test also catches zero
     and negative numbers which need special handling not in
     _ZGVnN2v_log2.  */
  c = x[0];
  d = x[1];
  if (c <= 1.32 || d <= 1.32)
    return __scalar_log2 (x);

  /* Check for Inf/Nan which are not handled either  */
  if (!__builtin_isnormal (c) || !__builtin_isnormal (d))
    return __scalar_log2 (x);

  GET_HIGH_WORD (hx_0, x[0]);
  GET_HIGH_WORD (hx_1, x[1]);
  k_0 = (hx_0 >> 20) - 1023;
  k_1 = (hx_1 >> 20) - 1023;
  hx_0 &= 0x000fffff;
  hx_1 &= 0x000fffff;
  i_0 = (hx_0 + 0x95f64) & 0x100000;
  i_1 = (hx_1 + 0x95f64) & 0x100000;
  SET_HIGH_WORD (x[0], hx_0 | (i_0 ^ 0x3ff00000));     /* normalize x or x/2 */
  SET_HIGH_WORD (x[1], hx_1 | (i_1 ^ 0x3ff00000));     /* normalize x or x/2 */
  k_0 += (i_0 >> 20);
  k_1 += (i_1 >> 20);
  dk = (__Float64x2_t) { (double) k_0, (double) k_1 };
  f = x - 1.0;
  s = f / (2.0 + f);
  z = s * s;
  i_0 = hx_0 - 0x6147a;
  i_1 = hx_1 - 0x6147a;
  w = z * z;
  j_0 = 0x6b851 - hx_0;
  j_1 = 0x6b851 - hx_1;
  t1 = w * (Lg2 + w * (Lg4 + w * Lg6));
  t2 = z * (Lg1 + w * (Lg3 + w * (Lg5 + w * Lg7)));
  i_0 |= j_0;
  i_1 |= j_1;
  R = t2 + t1;
  if (i_0 > 0)
    {
      hfsq = 0.5 * f[0] * f[0];
      rr[0] = (hfsq - (s[0] * (hfsq + R[0])));
    }
  else
    {
      rr[0] = s[0] * (f[0] - R[0]);
    }
  if (i_1 > 0)
    {
      hfsq = 0.5 * f[1] * f[1];
      rr[1] = hfsq - (s[1] * (hfsq + R[1]));
    }
  else
    {
      rr[1] = s[1] * (f[1] - R[1]);
    }
  vln2 = (__Float64x2_t) { ln2, ln2 };
  result = dk - ((rr - f) / vln2);
  return result;
}
