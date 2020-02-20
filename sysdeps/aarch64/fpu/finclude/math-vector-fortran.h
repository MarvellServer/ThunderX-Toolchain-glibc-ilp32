! Platform-specific declarations of SIMD math functions for Fortran. -*- f90 -*-
!   Copyright (C) 2019 Free Software Foundation, Inc.
!   This file is part of the GNU C Library.
!
!   The GNU C Library is free software; you can redistribute it and/or
!   modify it under the terms of the GNU Lesser General Public
!   License as published by the Free Software Foundation; either
!   version 2.1 of the License, or (at your option) any later version.
!
!   The GNU C Library is distributed in the hope that it will be useful,
!   but WITHOUT ANY WARRANTY; without even the implied warranty of
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
!   Lesser General Public License for more details.
!
!   You should have received a copy of the GNU Lesser General Public
!   License along with the GNU C Library; if not, see
!   <http://www.gnu.org/licenses/>.

!GCC$ builtin (cos) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (cosf) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (exp) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (expf) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (exp2) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (exp2f) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (exp10) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (exp10f) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (log) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (logf) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (log2) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (log2f) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (log10) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (log10f) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (pow) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (powf) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (sin) attributes simd (notinbranch) if('aarch64')
!GCC$ builtin (sinf) attributes simd (notinbranch) if('aarch64')
