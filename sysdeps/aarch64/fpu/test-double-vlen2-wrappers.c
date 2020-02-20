/* Tests for aarch64 vector math routines.
   Copyright (C) 2014-2018 Free Software Foundation, Inc.
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

#include "test-double-vlen2.h"

#define VEC_TYPE __Float64x2_t

VECTOR_WRAPPER (WRAPPER_NAME (cos), _ZGVnN2v_cos)
VECTOR_WRAPPER (WRAPPER_NAME (exp), _ZGVnN2v_exp)
VECTOR_WRAPPER (WRAPPER_NAME (exp2), _ZGVnN2v_exp2)
VECTOR_WRAPPER (WRAPPER_NAME (exp10), _ZGVnN2v_exp10)
VECTOR_WRAPPER (WRAPPER_NAME (log), _ZGVnN2v_log)
VECTOR_WRAPPER (WRAPPER_NAME (log2), _ZGVnN2v_log2)
VECTOR_WRAPPER (WRAPPER_NAME (log10), _ZGVnN2v_log10)
VECTOR_WRAPPER (WRAPPER_NAME (sin), _ZGVnN2v_sin)
VECTOR_WRAPPER_ff (WRAPPER_NAME (pow), _ZGVnN2vv_pow)
