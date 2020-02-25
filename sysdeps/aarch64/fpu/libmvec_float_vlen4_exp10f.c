#include <math.h>
#include <arm_neon.h>
#include <stdint.h>
#include <libc-symbols.h>
#include "libmvec_util.h"

extern __Float64x2_t _ZGVnN2v_exp(__Float64x2_t);

__attribute__((aarch64_vector_pcs))
__Float32x4_t _ZGVnN4v_exp10f(__Float32x4_t x)
{
  __Float64x2_t result_0, result_1;
  __Float64x2_t ln10 = (__Float64x2_t) { M_LN10,  M_LN10 };
  __Float64x2_t x_0 = get_lo_and_extend (x);
  __Float64x2_t x_1 = get_hi_and_extend (x);
  
  result_0 = _ZGVnN2v_exp (x_0 * ln10);
  result_1 = _ZGVnN2v_exp (x_1 * ln10);
  return pack_and_trunc (result_0, result_1);
}
