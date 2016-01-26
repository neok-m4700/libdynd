//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#pragma once

#include <dynd/kernels/comparison_kernels.hpp>
#include <dynd/string_encodings.hpp>

namespace dynd {

/**
 * Makes a kernel which compares fixed_strings.
 *
 * \param string_size  The number of characters (1, 2, or 4-bytes each) in the string.
 * \param encoding  The encoding of the string.
 */
DYND_API void make_fixed_string_comparison_kernel(nd::kernel_builder *ckb, size_t string_size,
                                                  string_encoding_t encoding, comparison_type_t comptype,
                                                  const eval::eval_context *ectx);

/**
 * Makes a kernel which compares blockref strings.
 *
 * \param encoding  The encoding of the string.
 */
DYND_API void make_string_comparison_kernel(nd::kernel_builder *ckb, string_encoding_t encoding,
                                            comparison_type_t comptype, const eval::eval_context *ectx);

/**
 * Makes a kernel which compares two strings of any type.
 *
 */
DYND_API void make_general_string_comparison_kernel(nd::kernel_builder *ckb, const ndt::type &src0_dt,
                                                    const char *src0_arrmeta, const ndt::type &src1_dt,
                                                    const char *src1_arrmeta, comparison_type_t comptype,
                                                    const eval::eval_context *ectx);

} // namespace dynd
