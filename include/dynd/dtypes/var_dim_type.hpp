//
// Copyright (C) 2011-13 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__VAR_DIM_TYPE_HPP_
#define _DYND__VAR_DIM_TYPE_HPP_

#include <dynd/type.hpp>
#include <dynd/dtypes/base_uniform_dim_type.hpp>
#include <dynd/dtype_assign.hpp>
#include <dynd/dtypes/view_dtype.hpp>
#include <dynd/string_encodings.hpp>

namespace dynd {

struct var_dim_type_metadata {
    /**
     * A reference to the memory block which contains the array's data.
     */
    memory_block_data *blockref;
    intptr_t stride;
    /* Each pointed-to destination is offset by this amount */
    intptr_t offset;
};

struct var_dim_type_data {
    char *begin;
    size_t size;
};

class var_dim_type : public base_uniform_dim_type {
    std::vector<std::pair<std::string, gfunc::callable> > m_array_properties, m_array_functions;
public:
    var_dim_type(const ndt::type& element_dtype);

    virtual ~var_dim_type();

    size_t get_default_data_size(size_t DYND_UNUSED(ndim), const intptr_t *DYND_UNUSED(shape)) const {
        return sizeof(var_dim_type_data);
    }


    /** Alignment of the data being pointed to. */
    size_t get_target_alignment() const {
        return m_element_dtype.get_data_alignment();
    }

    void print_data(std::ostream& o, const char *metadata, const char *data) const;

    void print_dtype(std::ostream& o) const;

    bool is_expression() const;
    bool is_unique_data_owner(const char *metadata) const;
    void transform_child_types(type_transform_fn_t transform_fn, void *extra,
                    ndt::type& out_transformed_dtype, bool& out_was_transformed) const;
    ndt::type get_canonical_type() const;
    bool is_strided() const;
    void process_strided(const char *metadata, const char *data,
                    ndt::type& out_dt, const char *&out_origin,
                    intptr_t& out_stride, intptr_t& out_dim_size) const;

    ndt::type apply_linear_index(size_t nindices, const irange *indices,
                size_t current_i, const ndt::type& root_dt, bool leading_dimension) const;
    intptr_t apply_linear_index(size_t nindices, const irange *indices, const char *metadata,
                    const ndt::type& result_dtype, char *out_metadata,
                    memory_block_data *embedded_reference,
                    size_t current_i, const ndt::type& root_dt,
                    bool leading_dimension, char **inout_data,
                    memory_block_data **inout_dataref) const;
    ndt::type at_single(intptr_t i0, const char **inout_metadata, const char **inout_data) const;

    ndt::type get_type_at_dimension(char **inout_metadata, size_t i, size_t total_ndim = 0) const;

    intptr_t get_dim_size(const char *metadata, const char *data) const;
    void get_shape(size_t ndim, size_t i, intptr_t *out_shape, const char *metadata) const;
    void get_strides(size_t i, intptr_t *out_strides, const char *metadata) const;

    axis_order_classification_t classify_axis_order(const char *metadata) const;

    bool is_lossless_assignment(const ndt::type& dst_dt, const ndt::type& src_dt) const;

    bool operator==(const base_type& rhs) const;

    void metadata_default_construct(char *metadata, size_t ndim, const intptr_t* shape) const;
    void metadata_copy_construct(char *dst_metadata, const char *src_metadata, memory_block_data *embedded_reference) const;
    void metadata_reset_buffers(char *metadata) const;
    void metadata_finalize_buffers(char *metadata) const;
    void metadata_destruct(char *metadata) const;
    void metadata_debug_print(const char *metadata, std::ostream& o, const std::string& indent) const;
    size_t metadata_copy_construct_onedim(char *dst_metadata, const char *src_metadata,
                    memory_block_data *embedded_reference) const;

    size_t get_iterdata_size(size_t ndim) const;
    size_t iterdata_construct(iterdata_common *iterdata, const char **inout_metadata, size_t ndim, const intptr_t* shape, ndt::type& out_uniform_dtype) const;
    size_t iterdata_destruct(iterdata_common *iterdata, size_t ndim) const;

    size_t make_assignment_kernel(
                    hierarchical_kernel *out, size_t offset_out,
                    const ndt::type& dst_dt, const char *dst_metadata,
                    const ndt::type& src_dt, const char *src_metadata,
                    kernel_request_t kernreq, assign_error_mode errmode,
                    const eval::eval_context *ectx) const;

    void foreach_leading(char *data, const char *metadata, foreach_fn_t callback, void *callback_data) const;
    
    void get_dynamic_dtype_properties(
                    const std::pair<std::string, gfunc::callable> **out_properties,
                    size_t *out_count) const;
    void get_dynamic_array_properties(
                    const std::pair<std::string, gfunc::callable> **out_properties,
                    size_t *out_count) const;
    void get_dynamic_array_functions(
                    const std::pair<std::string, gfunc::callable> **out_functions,
                    size_t *out_count) const;
};

inline ndt::type make_var_dim_type(const ndt::type& element_dtype) {
    return ndt::type(new var_dim_type(element_dtype), false);
}

} // namespace dynd

#endif // _DYND__VAR_DIM_TYPE_HPP_