#include <stdint.h>
#include <math.h>
#include <libc-symbols.h>
#include "dla.h"
#include "endian.h"
#include "mpa.h"
#include "math_config.h"

#define T __log_data.tab
#define T2 __log_data.tab2
#define B __log_data.poly1
#define A __log_data.poly
#define Ln2hi __log_data.ln2hi
#define Ln2lo __log_data.ln2lo
#define N (1 << LOG_TABLE_BITS)
#define OFF 0x3fe6000000000000

__attribute__((aarch64_vector_pcs, noinline))
static __Float64x2_t
__scalar_log(__Float64x2_t x)
{
  return (__Float64x2_t) { log (x[0]), log (x[1]) };
}

__attribute__((aarch64_vector_pcs))
__Float64x2_t _ZGVnN2v_log(__Float64x2_t x)
{
  double_t z_0, z_1;
  double_t invc_0, invc_1, logc_0, logc_1;
  double_t x_0, x_1;
  __Float64x2_t r_v, r2_v, y_v, z_v, kd_v, w_v;
  __Float64x2_t hi_v, lo_v, invc_v, logc_v;
  __Float64x2_t negone_v, Ln2hi_v, Ln2lo_v;
  __Float64x2_t A0_v, A1_v, A2_v, A3_v, A4_v;
  uint64_t ix_0, ix_1, iz_0, iz_1, tmp_0, tmp_1;
  int i_0, i_1, k_0, k_1;

  x_0 = x[0];
  x_1 = x[1];

  /* The algorithm used here is not accurate enough for
     numbers that are less than 1.3.  This test also catches zero
     and negative numbers which need special handling not in
     this code. */
  if (x_0 <= 1.3 || x_1 <= 1.3)
    return __scalar_log (x);

  /* Check for Inf/Nan which are not handled either  */
  if (!__builtin_isnormal (x_0) || !__builtin_isnormal (x_1))
    return __scalar_log (x);

  ix_0 = asuint64 (x[0]);
  ix_1 = asuint64 (x[1]);
  tmp_0 = ix_0 - OFF;
  tmp_1 = ix_1 - OFF;
  i_0 = (tmp_0 >> (52 - LOG_TABLE_BITS)) % N;
  i_1 = (tmp_1 >> (52 - LOG_TABLE_BITS)) % N;
  k_0 = (int64_t) tmp_0 >> 52; /* arithmetic shift */
  k_1 = (int64_t) tmp_1 >> 52; /* arithmetic shift */
  iz_0 = ix_0 - (tmp_0 & 0xfffULL << 52);
  iz_1 = ix_1 - (tmp_1 & 0xfffULL << 52);
  invc_0 = T[i_0].invc;
  invc_1 = T[i_1].invc;
  logc_0 = T[i_0].logc;
  logc_1 = T[i_1].logc;
  z_0 = asdouble (iz_0);
  z_1 = asdouble (iz_1);

  invc_v = (__Float64x2_t) { invc_0, invc_1 };
  logc_v = (__Float64x2_t) { logc_0, logc_1 };
  z_v = (__Float64x2_t) { z_0, z_1 };
  negone_v = (__Float64x2_t) { -1.0, -1.0 };
  Ln2hi_v = (__Float64x2_t) { Ln2hi, Ln2hi };
  Ln2lo_v = (__Float64x2_t) { Ln2lo, Ln2lo };

  A0_v = (__Float64x2_t) { A[0], A[0] };
  A1_v = (__Float64x2_t) { A[1], A[1] };
  A2_v = (__Float64x2_t) { A[2], A[2] };
  A3_v = (__Float64x2_t) { A[3], A[3] };
  A4_v = (__Float64x2_t) { A[4], A[4] };

  r_v = __builtin_aarch64_fmav2df (z_v, invc_v, negone_v);
  kd_v = (__Float64x2_t) { (double) k_0, (double) k_1 };
  w_v = kd_v * Ln2hi_v + logc_v;
  hi_v = w_v + r_v;
  lo_v = w_v - hi_v + r_v + kd_v * Ln2lo_v;
  r2_v = r_v * r_v;
  y_v = lo_v + r2_v * A0_v + r_v * r2_v * (A1_v + r_v * A2_v + r2_v * (A3_v + r_v * A4_v)) + hi_v;
  return y_v;
}
