//
// Copyright (C) 2011-16 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <dynd/arithmetic.hpp>
#include <dynd/callables/arithmetic_dispatch_callable.hpp>
#include <dynd/functional.hpp>
#include <dynd/kernels/arithmetic.hpp>
#include <dynd/types/scalar_kind_type.hpp>

using namespace std;
using namespace dynd;

namespace {

typedef type_id_sequence<uint8_id, uint16_id, uint32_id, uint64_id, int8_id, int16_id, int32_id, int64_id, float32_id,
                         float64_id, complex_float32_id, complex_float64_id>
    binop_ids;

template <template <type_id_t> class CallableType, template <type_id_t> class Condition, typename TypeIDSequence>
nd::callable make_unary_arithmetic() {
  dispatcher<nd::callable> dispatcher = nd::callable::make_all_if<CallableType, Condition, TypeIDSequence>();

  const ndt::type &tp = ndt::type("(Any) -> Any");
  for (type_id_t i0 : i2a<dim_ids>()) {
    dispatcher.insert({{i0}, nd::get_elwise()});
  }

  return nd::make_callable<nd::arithmetic_dispatch_callable<1>>(tp, dispatcher);
}

} // anonymous namespace