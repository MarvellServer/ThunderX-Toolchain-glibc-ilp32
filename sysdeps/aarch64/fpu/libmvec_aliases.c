/* These aliases added as workaround to exclude unnecessary symbol
   aliases in libmvec.so while compiler creates the vector names
   based on scalar asm name.  Corresponding discussion is at
   <https://gcc.gnu.org/ml/gcc/2015-06/msg00173.html>.
   Copyright (C) 2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <arm_neon.h>

#define FINITE_ALIAS(FFUNC,RFUNC,TYPE) \
  extern __attribute__((aarch64_vector_pcs)) TYPE RFUNC (TYPE x); \
  __attribute__((aarch64_vector_pcs)) TYPE \
  FFUNC (TYPE x) { return RFUNC (x); }

#define FINITE_ALIAS2(FFUNC,RFUNC,TYPE) \
  extern __attribute__((aarch64_vector_pcs)) TYPE RFUNC (TYPE x, TYPE y); \
  __attribute__((aarch64_vector_pcs)) TYPE \
  FFUNC (TYPE x, TYPE y) { return RFUNC (x,y); }

FINITE_ALIAS(_ZGVnN2v___cos_finite,_ZGVnN2v_cos,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___exp_finite,_ZGVnN2v_exp,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___exp2_finite,_ZGVnN2v_exp2,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___exp10_finite,_ZGVnN2v_exp10,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___log_finite,_ZGVnN2v_log,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___log2_finite,_ZGVnN2v_log2,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___log10_finite,_ZGVnN2v_log10,float64x2_t)
FINITE_ALIAS(_ZGVnN2v___sin_finite,_ZGVnN2v_sin,float64x2_t)
FINITE_ALIAS2(_ZGVnN2vv___pow_finite,_ZGVnN2vv_pow,float64x2_t)

FINITE_ALIAS(_ZGVnN4v___cosf_finite,_ZGVnN4v_cosf,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___expf_finite,_ZGVnN4v_expf,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___exp2f_finite,_ZGVnN4v_exp2f,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___exp10f_finite,_ZGVnN4v_exp10f,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___logf_finite,_ZGVnN4v_logf,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___log10f_finite,_ZGVnN4v_log10f,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___log2f_finite,_ZGVnN4v_log2f,float32x4_t)
FINITE_ALIAS(_ZGVnN4v___sinf_finite,_ZGVnN4v_sinf,float32x4_t)
FINITE_ALIAS2(_ZGVnN4vv___powf_finite,_ZGVnN4vv_powf,float32x4_t)
FINITE_ALIAS2(_ZGVnN2vv___powf_finite,_ZGVnN2vv_powf,float32x2_t)

#undef FINITE_ALIAS
#undef FINITE_ALIAS2
