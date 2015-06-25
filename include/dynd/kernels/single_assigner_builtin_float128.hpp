//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

// This file is an internal implementation detail of built-in value assignment
// for aligned values in native byte order.

#if !defined(DYND_HAS_FLOAT128)

// float128 -> boolean with no checking
template<>
struct single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_nocheck>
{
    DYND_CUDA_HOST_DEVICE inline static void assign(bool1 *dst,
                                                    const float128 *src)
    {
        DYND_TRACE_ASSIGNMENT((bool)(s != src_type(0)), bool1, s, src_type);

        *dst = ((src->m_lo != 0) || ((src->m_hi&0x7fffffffffffffffULL) != 0));
    }
};
template<>
struct single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_overflow>
{
    inline static void assign(bool1 *dst, const float128 *src)
    {
        // DYND_TRACE_ASSIGNMENT((bool)(s != src_type(0)), bool1, s, src_type);

        if ((src->m_hi&0x7fffffffffffffffULL) == 0 && src->m_lo == 0) {
            *dst = 0;
        } else if (src->m_hi == 0x3fff000000000000ULL && src->m_lo == 0) { // 1.0 in binary128
            *dst = 1;
        } else {
            std::stringstream ss;
            ss << "overflow while assigning " << ndt::make_type<float128>();
            // TODO: ss << " value " << s;
            ss << " to " << ndt::make_type<bool1>();
            throw std::runtime_error(ss.str());
        }
    }
};
template<>
struct single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_fractional>
    : public single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_overflow> {};
template<>
struct single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_inexact>
    : public single_assigner_builtin_base<bool1, float128, bool_kind, real_kind, assign_error_overflow> {};

// Bool -> float128
template<>
struct single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_nocheck>
{
    DYND_CUDA_HOST_DEVICE static void assign(float128 *dst, const bool1 *src) {
        DYND_TRACE_ASSIGNMENT((bool)(s != src_type(0)), bool1, s, src_type);

        if (*src) {
            *dst = float128(0x3fff000000000000ULL, 0ULL);
        } else {
            *dst = float128(0ULL, 0ULL);
        }
    }
};
template<>
struct single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_overflow>
    : public single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_nocheck> {};
template<>
struct single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_fractional>
    : public single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_nocheck> {};
template<>
struct single_assigner_builtin_base<float128, bool1, real_kind, bool_kind, assign_error_inexact>
    : public single_assigner_builtin_base<float128,bool1,  real_kind, bool_kind, assign_error_nocheck> {};

// Anything -> float128
#define DYND_MAKE_WITH_KIND(src_kind) \
template<class src_type> \
struct single_assigner_builtin_base<float128, src_type, real_kind, src_kind, assign_error_nocheck> \
    : public single_assigner_builtin_base_error<float128, src_type, assign_error_nocheck> {}; \
template<class src_type> \
struct single_assigner_builtin_base<float128, src_type, real_kind, src_kind, assign_error_overflow> \
    : public single_assigner_builtin_base_error<float128, src_type, assign_error_overflow> {}; \
template<class src_type> \
struct single_assigner_builtin_base<float128, src_type, real_kind, src_kind, assign_error_fractional> \
    : public single_assigner_builtin_base_error<float128, src_type, assign_error_fractional> {}; \
template<class src_type> \
struct single_assigner_builtin_base<float128, src_type, real_kind, src_kind, assign_error_inexact> \
    : public single_assigner_builtin_base_error<float128, src_type, assign_error_inexact> {};

DYND_MAKE_WITH_KIND(real_kind);
DYND_MAKE_WITH_KIND(complex_kind);

#undef DYND_MAKE_WITH_KIND

// Float128 -> anything
#define DYND_MAKE_WITH_KIND(dst_kind) \
template<class dst_type> \
struct single_assigner_builtin_base<dst_type, float128, dst_kind, real_kind, assign_error_nocheck> \
    : public single_assigner_builtin_base_error<dst_type, float128, assign_error_nocheck> {}; \
template<class dst_type> \
struct single_assigner_builtin_base<dst_type, float128, dst_kind, real_kind, assign_error_overflow> \
    : public single_assigner_builtin_base_error<dst_type, float128, assign_error_overflow> {}; \
template<class dst_type> \
struct single_assigner_builtin_base<dst_type, float128, dst_kind, real_kind, assign_error_fractional> \
    : public single_assigner_builtin_base_error<dst_type, float128, assign_error_fractional> {}; \
template<class dst_type> \
struct single_assigner_builtin_base<dst_type, float128, dst_kind, real_kind, assign_error_inexact> \
    : public single_assigner_builtin_base_error<dst_type, float128, assign_error_inexact> {};

DYND_MAKE_WITH_KIND(bool_kind);
DYND_MAKE_WITH_KIND(real_kind);
DYND_MAKE_WITH_KIND(complex_kind);

#undef DYND_MAKE_WITH_KIND

// float16 -> float128
template<>
struct single_assigner_builtin_base<float128, float16, real_kind, real_kind, assign_error_nocheck>
    : public single_assigner_builtin_base_error<float128, float16, assign_error_nocheck> {};
template<>
struct single_assigner_builtin_base<float128, float16, real_kind, real_kind, assign_error_overflow>
    : public single_assigner_builtin_base_error<float128, float16, assign_error_overflow> {};
template<>
struct single_assigner_builtin_base<float128, float16, real_kind, real_kind, assign_error_fractional>
    : public single_assigner_builtin_base_error<float128, float16, assign_error_fractional> {};
template<>
struct single_assigner_builtin_base<float128, float16, real_kind, real_kind, assign_error_inexact>
    : public single_assigner_builtin_base_error<float128, float16, assign_error_inexact> {};


// float128 -> float16
template<>
struct single_assigner_builtin_base<float16, float128, real_kind, real_kind, assign_error_nocheck>
    : public single_assigner_builtin_base_error<float16, float128, assign_error_nocheck> {};
template<>
struct single_assigner_builtin_base<float16, float128, real_kind, real_kind, assign_error_overflow>
    : public single_assigner_builtin_base_error<float16, float128, assign_error_overflow> {};
template<>
struct single_assigner_builtin_base<float16, float128, real_kind, real_kind, assign_error_fractional>
    : public single_assigner_builtin_base_error<float16, float128, assign_error_fractional> {};
template<>
struct single_assigner_builtin_base<float16, float128, real_kind, real_kind, assign_error_inexact>
    : public single_assigner_builtin_base_error<float16, float128, assign_error_inexact> {};

#endif // !defined(DYND_HAS_FLOAT128)
