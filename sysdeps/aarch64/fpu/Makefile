ifeq ($(subdir),math)
CFLAGS-e_sqrtf.c += -fno-math-errno
CFLAGS-e_sqrt.c += -fno-math-errno
CFLAGS-s_lroundf.c += -fno-math-errno
CFLAGS-s_lround.c += -fno-math-errno
CFLAGS-s_llroundf.c += -fno-math-errno
CFLAGS-s_llround.c += -fno-math-errno
# GCC 4.9 and 5 requires the flag to correct emits a f{max,min}nm
# for a __builtin_{fmax,fmin}{f}.
CFLAGS-s_fmax.c += -ffinite-math-only
CFLAGS-s_fmaxf.c += -ffinite-math-only
CFLAGS-s_fmin.c += -ffinite-math-only
CFLAGS-s_fminf.c += -ffinite-math-only
endif

ifeq ($(subdir),mathvec)
CFLAGS-libmvec_double_vlen2_exp.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_exp2.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_exp10.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_log.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_log2.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_log10.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_pow.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_double_vlen2_sincos.c += -march=armv8-a+simd -fno-math-errno

CFLAGS-libmvec_float_vlen4_cosf.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_expf.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_exp2f.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_exp10f.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_logf.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_log2f.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_log10f.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_powf.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_float_vlen4_sinf.c += -march=armv8-a+simd -fno-math-errno

CFLAGS-libmvec_exp_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_log_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_log2_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_pow_log_data.c += -march=armv8-a+simd -fno-math-errno

CFLAGS-libmvec_exp2f_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_logf_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_log2f_data.c += -march=armv8-a+simd -fno-math-errno
CFLAGS-libmvec_aliases.c += -march=armv8-a+simd -fno-math-errno

libmvec-support += libmvec_double_vlen2_exp
libmvec-support += libmvec_double_vlen2_exp2
libmvec-support += libmvec_double_vlen2_exp10
libmvec-support += libmvec_double_vlen2_log
libmvec-support += libmvec_double_vlen2_log2
libmvec-support += libmvec_double_vlen2_log10
libmvec-support += libmvec_double_vlen2_pow
libmvec-support += libmvec_double_vlen2_sincos

libmvec-support += libmvec_float_vlen4_cosf
libmvec-support += libmvec_float_vlen4_expf
libmvec-support += libmvec_float_vlen4_exp2f
libmvec-support += libmvec_float_vlen4_exp10f
libmvec-support += libmvec_float_vlen4_logf
libmvec-support += libmvec_float_vlen4_log2f
libmvec-support += libmvec_float_vlen4_log10f
libmvec-support += libmvec_float_vlen4_powf
libmvec-support += libmvec_float_vlen4_sinf

libmvec-support += libmvec_exp_data
libmvec-support += libmvec_log_data
libmvec-support += libmvec_log2_data
libmvec-support += libmvec_pow_log_data

libmvec-support += libmvec_exp2f_data
libmvec-support += libmvec_logf_data
libmvec-support += libmvec_log2f_data

libmvec-support += libmvec_aliases

# If I do not add a static routine I do not get libmvec_nonshared.a
# installed and GCC links fail when they cannot find it.  Put the
# *_finite aliases here instead of in the shared library so they
# are not part of the library ABI.
libmvec-static-only-routines += libmvec_aliases
endif

ifeq ($(subdir),math)
ifeq ($(build-mathvec),yes)

libmvec-tests += double-vlen2 float-vlen4

double-vlen2-funcs = cos exp exp2 exp10 log log2 log10 pow sin
float-vlen4-funcs = cos exp exp2 exp10 log log2 log10 pow sin

endif
endif
