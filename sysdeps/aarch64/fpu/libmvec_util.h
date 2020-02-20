
static __always_inline
__Float64x2_t get_lo_and_extend (__Float32x4_t x)
{
	__Uint64x2_t  tmp1 = (__Uint64x2_t) x;
#ifdef BIG_ENDI
	uint64_t      tmp2 = (uint64_t) tmp1[1];
#else
	uint64_t      tmp2 = (uint64_t) tmp1[0];
#endif
	return __builtin_aarch64_float_extend_lo_v2df ((__Float32x2_t) tmp2);
}

static __always_inline
__Float64x2_t get_hi_and_extend (__Float32x4_t x)
{
	return __builtin_aarch64_vec_unpacks_hi_v4sf (x);
}

static __always_inline
__Float32x4_t pack_and_trunc (__Float64x2_t x, __Float64x2_t y)
{
        __Float32x2_t xx = __builtin_aarch64_float_truncate_lo_v2sf (x);
        __Float32x2_t yy = __builtin_aarch64_float_truncate_lo_v2sf (y);
        return (__builtin_aarch64_combinev2sf (xx, yy));
}
