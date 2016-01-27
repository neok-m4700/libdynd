//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <dynd/func/assignment.hpp>
#include <dynd/functional.hpp>
#include <dynd/kernels/assignment_kernels.hpp>
#include <dynd/types/any_kind_type.hpp>

using namespace std;
using namespace dynd;

DYND_API nd::callable nd::assign::make()
{
  typedef type_id_sequence<bool_id, int8_id, int16_id, int32_id, int64_id, int128_id,
                           uint8_id, uint16_id, uint32_id, uint64_id, uint128_id,
                           float32_id, float64_id, complex_float32_id,
                           complex_float64_id> numeric_ids;

  ndt::type self_tp = ndt::callable_type::make(ndt::any_kind_type::make(), {ndt::any_kind_type::make()}, {"error_mode"},
                                               {ndt::make_type<ndt::option_type>(ndt::make_type<assign_error_mode>())});

  map<std::array<type_id_t, 2>, callable> children =
      callable::make_all<_bind<assign_error_mode, assignment_kernel>::type, numeric_ids, numeric_ids>();
  children[{{date_id, date_id}}] = callable::make<assignment_kernel<date_id, date_id>>();
  children[{{date_id, string_id}}] = callable::make<assignment_kernel<date_id, string_id>>();
  children[{{date_id, fixed_string_id}}] = callable::make<assignment_kernel<date_id, string_id>>();
  children[{{string_id, date_id}}] = callable::make<assignment_kernel<string_id, date_id>>();
  children[{{string_id, string_id}}] = callable::make<assignment_kernel<string_id, string_id>>();
  children[{{bytes_id, bytes_id}}] = callable::make<assignment_kernel<bytes_id, bytes_id>>();
  children[{{fixed_bytes_id, fixed_bytes_id}}] =
      callable::make<assignment_kernel<fixed_bytes_id, fixed_bytes_id>>();
  children[{{char_id, char_id}}] = callable::make<assignment_kernel<char_id, char_id>>();
  children[{{char_id, fixed_string_id}}] =
      callable::make<assignment_kernel<char_id, fixed_string_id>>();
  children[{{char_id, string_id}}] = callable::make<assignment_kernel<char_id, string_id>>();
  children[{{fixed_string_id, char_id}}] =
      callable::make<assignment_kernel<fixed_string_id, char_id>>();
  children[{{string_id, char_id}}] = callable::make<assignment_kernel<string_id, char_id>>();
  children[{{type_id, type_id}}] = callable::make<assignment_kernel<type_id, type_id>>();
  children[{{time_id, string_id}}] = callable::make<assignment_kernel<time_id, string_id>>();
  children[{{string_id, time_id}}] = callable::make<assignment_kernel<string_id, time_id>>();
  children[{{string_id, int32_id}}] = callable::make<assignment_kernel<string_id, int32_id>>();
  children[{{datetime_id, string_id}}] =
      callable::make<assignment_kernel<datetime_id, string_id>>();
  children[{{string_id, datetime_id}}] =
      callable::make<assignment_kernel<string_id, datetime_id>>();
  children[{{datetime_id, datetime_id}}] =
      callable::make<assignment_kernel<datetime_id, datetime_id>>();
  children[{{fixed_string_id, fixed_string_id}}] =
      callable::make<assignment_kernel<fixed_string_id, fixed_string_id>>();
  children[{{fixed_string_id, string_id}}] =
      callable::make<assignment_kernel<fixed_string_id, string_id>>();
  children[{{fixed_string_id, uint8_id}}] =
      callable::make<assignment_kernel<fixed_string_id, uint8_id>>();
  children[{{fixed_string_id, uint16_id}}] =
      callable::make<assignment_kernel<fixed_string_id, uint16_id>>();
  children[{{fixed_string_id, uint32_id}}] =
      callable::make<assignment_kernel<fixed_string_id, uint32_id>>();
  children[{{fixed_string_id, uint64_id}}] =
      callable::make<assignment_kernel<fixed_string_id, uint64_id>>();
  children[{{fixed_string_id, uint128_id}}] =
      callable::make<assignment_kernel<fixed_string_id, uint128_id>>();
  children[{{int32_id, fixed_string_id}}] =
      callable::make<assignment_kernel<int32_id, fixed_string_id>>();
  children[{{string_id, string_id}}] = callable::make<assignment_kernel<string_id, string_id>>();
  children[{{string_id, fixed_string_id}}] =
      callable::make<assignment_kernel<string_id, fixed_string_id>>();
  children[{{bool_id, string_id}}] = callable::make<assignment_kernel<bool_id, string_id>>();
  children[{{option_id, option_id}}] =
      callable::make<detail::assignment_option_kernel>(ndt::type("(?Any) -> ?Any"));
  for (type_id_t tp_id : {int32_id, string_id, float64_id, bool_id, int8_id, uint32_id}) {
    children[{{tp_id, option_id}}] = callable::make<detail::assignment_option_kernel>(ndt::type("(?Any) -> ?Any"));
    children[{{option_id, tp_id}}] = callable::make<detail::assignment_option_kernel>(ndt::type("(?Any) -> ?Any"));
  }
  children[{{string_id, type_id}}] = callable::make<assignment_kernel<string_id, type_id>>();
  children[{{type_id, string_id}}] = callable::make<assignment_kernel<type_id, string_id>>();
  children[{{pointer_id, pointer_id}}] =
      callable::make<assignment_kernel<pointer_id, pointer_id>>();
  children[{{int8_id, string_id}}] = callable::make<assignment_kernel<int8_id, string_id>>();
  children[{{int16_id, string_id}}] = callable::make<assignment_kernel<int16_id, string_id>>();
  children[{{int32_id, string_id}}] = callable::make<assignment_kernel<int32_id, string_id>>();
  children[{{int64_id, string_id}}] = callable::make<assignment_kernel<int64_id, string_id>>();
  children[{{uint8_id, string_id}}] = callable::make<assignment_kernel<uint8_id, string_id>>();
  children[{{uint16_id, string_id}}] = callable::make<assignment_kernel<uint16_id, string_id>>();
  children[{{uint32_id, string_id}}] = callable::make<assignment_kernel<uint32_id, string_id>>();
  children[{{uint64_id, string_id}}] = callable::make<assignment_kernel<uint64_id, string_id>>();
  children[{{float32_id, string_id}}] = callable::make<assignment_kernel<float32_id, string_id>>();
  children[{{float64_id, string_id}}] = callable::make<assignment_kernel<float64_id, string_id>>();
  children[{{tuple_id, tuple_id}}] = callable::make<assignment_kernel<tuple_id, tuple_id>>();
  children[{{struct_id, int32_id}}] = callable::make<assignment_kernel<struct_id, struct_id>>();
  children[{{struct_id, struct_id}}] = callable::make<assignment_kernel<struct_id, struct_id>>();
  for (type_id_t tp_id : {bool_id, int8_id, int16_id, int32_id, int64_id, int128_id,
                          uint8_id, uint16_id, uint32_id, uint64_id, uint128_id,
                          float32_id, float64_id, fixed_dim_id, type_id}) {
    children[{{tp_id, var_dim_id}}] =
        nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));
    children[{{var_dim_id, tp_id}}] =
        nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));
  }
  children[{{var_dim_id, var_dim_id}}] =
      nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));
  for (type_id_t tp_id : {bool_id, int8_id, int16_id, int32_id, int64_id, int128_id,
                          uint8_id, uint16_id, uint32_id, uint64_id, uint128_id,
                          float32_id, float64_id, type_id}) {
    children[{{tp_id, fixed_dim_id}}] =
        nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));
    children[{{fixed_dim_id, tp_id}}] =
        nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));
  }
  children[{{fixed_dim_id, fixed_dim_id}}] =
      nd::functional::elwise(nd::functional::call<assign>(ndt::type("(Any) -> Any")));

  children[{{adapt_id, int16_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, int32_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, int64_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, float32_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, float64_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, complex_float32_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, complex_float64_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));
  children[{{adapt_id, date_id}}] =
      nd::callable::make<detail::adapt_assign_to_kernel>(ndt::type("(Any) -> Any"));

  children[{{int32_id, adapt_id}}] =
      nd::callable::make<detail::adapt_assign_from_kernel>(ndt::type("(Any) -> Any"));
  children[{{struct_id, adapt_id}}] =
      nd::callable::make<detail::adapt_assign_from_kernel>(ndt::type("(Any) -> Any"));

  children[{{fixed_bytes_id, view_id}}] =
      callable::make<assignment_kernel<fixed_bytes_id, view_id>>();
  children[{{date_id, expr_id}}] = callable::make<assignment_kernel<date_id, expr_id>>();
  children[{{option_id, convert_id}}] = callable::make<assignment_kernel<option_id, convert_id>>();
  children[{{string_id, convert_id}}] = callable::make<assignment_kernel<string_id, convert_id>>();
  children[{{string_id, expr_id}}] = callable::make<assignment_kernel<string_id, expr_id>>();
  children[{{datetime_id, convert_id}}] =
      callable::make<assignment_kernel<datetime_id, convert_id>>();
  children[{{fixed_string_id, convert_id}}] =
      callable::make<assignment_kernel<fixed_string_id, convert_id>>();
  children[{{convert_id, convert_id}}] =
      callable::make<assignment_kernel<convert_id, convert_id>>();
  children[{{int16_id, view_id}}] = callable::make<assignment_kernel<int16_id, view_id>>();
  children[{{int32_id, view_id}}] = callable::make<assignment_kernel<int32_id, view_id>>();
  children[{{int64_id, view_id}}] = callable::make<assignment_kernel<int64_id, view_id>>();
  children[{{categorical_id, convert_id}}] =
      callable::make<assignment_kernel<categorical_id, convert_id>>();
  children[{{string_id, convert_id}}] = callable::make<assignment_kernel<string_id, convert_id>>();
  children[{{bool_id, convert_id}}] = callable::make<assignment_kernel<bool_id, convert_id>>();
  children[{{type_id, convert_id}}] = callable::make<assignment_kernel<type_id, convert_id>>();
  children[{{convert_id, convert_id}}] =
      callable::make<assignment_kernel<convert_id, convert_id>>();
  children[{{float64_id, convert_id}}] =
      callable::make<assignment_kernel<float64_id, convert_id>>();
  children[{{int32_id, convert_id}}] = callable::make<assignment_kernel<int32_id, convert_id>>();
  children[{{int8_id, convert_id}}] = callable::make<assignment_kernel<int8_id, convert_id>>();
  children[{{float32_id, convert_id}}] =
      callable::make<assignment_kernel<float32_id, convert_id>>();
  children[{{int64_id, convert_id}}] = callable::make<assignment_kernel<int64_id, convert_id>>();
  children[{{int16_id, convert_id}}] = callable::make<assignment_kernel<int16_id, convert_id>>();
  children[{{convert_id, float64_id}}] =
      callable::make<assignment_kernel<convert_id, float64_id>>();
  children[{{convert_id, int8_id}}] = callable::make<assignment_kernel<convert_id, int8_id>>();
  children[{{convert_id, int16_id}}] = callable::make<assignment_kernel<convert_id, int16_id>>();
  children[{{convert_id, int32_id}}] = callable::make<assignment_kernel<convert_id, int32_id>>();
  children[{{convert_id, int64_id}}] = callable::make<assignment_kernel<convert_id, int64_id>>();
  children[{{convert_id, uint8_id}}] = callable::make<assignment_kernel<convert_id, uint8_id>>();
  children[{{convert_id, uint16_id}}] = callable::make<assignment_kernel<convert_id, uint16_id>>();
  children[{{convert_id, uint32_id}}] = callable::make<assignment_kernel<convert_id, uint32_id>>();
  children[{{convert_id, uint64_id}}] = callable::make<assignment_kernel<convert_id, uint64_id>>();
  children[{{view_id, int8_id}}] = callable::make<assignment_kernel<view_id, int8_id>>();
  children[{{view_id, int16_id}}] = callable::make<assignment_kernel<view_id, int16_id>>();
  children[{{view_id, int32_id}}] = callable::make<assignment_kernel<view_id, int32_id>>();
  children[{{view_id, int64_id}}] = callable::make<assignment_kernel<view_id, int64_id>>();
  children[{{view_id, uint8_id}}] = callable::make<assignment_kernel<view_id, uint8_id>>();
  children[{{view_id, uint16_id}}] = callable::make<assignment_kernel<view_id, uint16_id>>();
  children[{{view_id, uint32_id}}] = callable::make<assignment_kernel<view_id, uint32_id>>();
  children[{{view_id, uint64_id}}] = callable::make<assignment_kernel<view_id, uint64_id>>();
  children[{{uint8_id, view_id}}] = callable::make<assignment_kernel<uint8_id, view_id>>();
  children[{{uint16_id, view_id}}] = callable::make<assignment_kernel<uint16_id, view_id>>();
  children[{{uint32_id, view_id}}] = callable::make<assignment_kernel<uint32_id, view_id>>();
  children[{{uint64_id, view_id}}] = callable::make<assignment_kernel<uint64_id, view_id>>();
  children[{{uint8_id, convert_id}}] = callable::make<assignment_kernel<uint8_id, convert_id>>();
  children[{{uint16_id, convert_id}}] = callable::make<assignment_kernel<uint16_id, convert_id>>();
  children[{{uint32_id, convert_id}}] = callable::make<assignment_kernel<uint32_id, convert_id>>();
  children[{{uint64_id, convert_id}}] = callable::make<assignment_kernel<uint64_id, convert_id>>();
  children[{{fixed_dim_id, convert_id}}] =
      callable::make<assignment_kernel<fixed_dim_id, convert_id>>();
  children[{{struct_id, convert_id}}] = callable::make<assignment_kernel<struct_id, convert_id>>();
  children[{{view_id, int32_id}}] = callable::make<assignment_kernel<view_id, int32_id>>();
  children[{{view_id, int64_id}}] = callable::make<assignment_kernel<view_id, int64_id>>();
  children[{{view_id, view_id}}] = callable::make<assignment_kernel<view_id, view_id>>();
  children[{{complex_float32_id, convert_id}}] =
      callable::make<assignment_kernel<complex_float32_id, convert_id>>();
  children[{{complex_float64_id, convert_id}}] =
      callable::make<assignment_kernel<complex_float64_id, convert_id>>();
  children[{{time_id, convert_id}}] = callable::make<assignment_kernel<time_id, convert_id>>();
  children[{{date_id, convert_id}}] = callable::make<assignment_kernel<date_id, convert_id>>();

  return functional::dispatch(self_tp, [children](const ndt::type &dst_tp, intptr_t DYND_UNUSED(nsrc),
                                                  const ndt::type *src_tp) mutable -> callable & {
    callable &child = children[{{dst_tp.get_id(), src_tp[0].get_id()}}];
    if (child.is_null()) {
      //      throw std::runtime_error("assignment error");
    }
    return child;
  });
}

DYND_API struct nd::assign nd::assign;

void dynd::make_assignment_kernel(nd::kernel_builder *ckb, const ndt::type &dst_tp, const char *dst_arrmeta,
                                  const ndt::type &src_tp, const char *src_arrmeta, kernel_request_t kernreq,
                                  const eval::eval_context *ectx)
{
  nd::array error_mode = ectx->errmode;
  nd::assign::get()->instantiate(nd::assign::get()->static_data(), NULL, ckb, dst_tp, dst_arrmeta, 1, &src_tp,
                                 &src_arrmeta, kernreq, 1, &error_mode, std::map<std::string, ndt::type>());
}

void dynd::make_pod_typed_data_assignment_kernel(nd::kernel_builder *ckb, size_t data_size,
                                                 size_t DYND_UNUSED(data_alignment), kernel_request_t kernreq)
{
  // Aligned specialization tables
  switch (data_size) {
  case 1:
    ckb->emplace_back<nd::trivial_copy_kernel<1>>(kernreq);
    break;
  case 2:
    ckb->emplace_back<nd::trivial_copy_kernel<2>>(kernreq);
    break;
  case 4:
    ckb->emplace_back<nd::trivial_copy_kernel<4>>(kernreq);
    break;
  case 8:
    ckb->emplace_back<nd::trivial_copy_kernel<8>>(kernreq);
    break;
  default:
    ckb->emplace_back<nd::unaligned_copy_ck>(kernreq, data_size);
    break;
  }
}
