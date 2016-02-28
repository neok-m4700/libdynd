//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

#include "inc_gtest.hpp"
#include "dynd_assertions.hpp"

#include <dynd/dispatch_map.hpp>
#include <dynd/type_registry.hpp>
#include <dynd/types/type_id.hpp>

using namespace std;
using namespace dynd;

TEST(TypeRegistry, Bases)
{
  static const vector<type_id_t> int_base_ids{int_kind_id, scalar_kind_id, any_kind_id};
  EXPECT_EQ(int_base_ids, ndt::type_registry[int8_id].bases());
  EXPECT_EQ(int_base_ids, ndt::type_registry[int16_id].bases());
  EXPECT_EQ(int_base_ids, ndt::type_registry[int32_id].bases());
  EXPECT_EQ(int_base_ids, ndt::type_registry[int64_id].bases());
  EXPECT_EQ(int_base_ids, ndt::type_registry[int128_id].bases());

  static const vector<type_id_t> uint_base_ids{uint_kind_id, scalar_kind_id, any_kind_id};
  EXPECT_EQ(uint_base_ids, ndt::type_registry[uint8_id].bases());
  EXPECT_EQ(uint_base_ids, ndt::type_registry[uint16_id].bases());
  EXPECT_EQ(uint_base_ids, ndt::type_registry[uint32_id].bases());
  EXPECT_EQ(uint_base_ids, ndt::type_registry[uint64_id].bases());
  EXPECT_EQ(uint_base_ids, ndt::type_registry[uint128_id].bases());

  static const vector<type_id_t> float_base_ids{float_kind_id, scalar_kind_id, any_kind_id};
  EXPECT_EQ(float_base_ids, ndt::type_registry[float16_id].bases());
  EXPECT_EQ(float_base_ids, ndt::type_registry[float32_id].bases());
  EXPECT_EQ(float_base_ids, ndt::type_registry[float64_id].bases());
  EXPECT_EQ(float_base_ids, ndt::type_registry[float128_id].bases());

  /*
    static const vector<type_id_t> bytes_base_ids{bytes_kind_id, scalar_kind_id, any_kind_id};
    //  EXPECT_EQ(bytes_base_ids, ndt::type_registry[fixed_bytes_id].bases());
    //  EXPECT_EQ(bytes_base_ids, ndt::type_registry[bytes_id].bases());

    static const vector<type_id_t> string_base_ids{string_kind_id, scalar_kind_id, any_kind_id};
    for (type_id_t id : ndt::type_registry[string_id].bases()) {
      std::cout << id << std::endl;
    }

    std::exit(-1);
    EXPECT_EQ(string_base_ids, ndt::type_registry[string_id].bases());
  */
}

/*
TEST(TypeRegistry, IsBaseIDOf)
{
  for (type_id_t id = ndt::type_registry.min(); id < callable_id; id = static_cast<type_id_t>(id + 1)) {
    for (type_id_t base_id : ndt::type_registry[id].bases()) {
      EXPECT_TRUE(is_base_id_of(base_id, id));
    }
  }
}
*/

TEST(Sort, TopologicalSort)
{
  std::vector<std::vector<intptr_t>> edges{{}, {}, {3}, {1}, {0, 1}, {0, 2}};

  std::vector<intptr_t> res(6);
  topological_sort(std::vector<intptr_t>{0, 1, 2, 3, 4, 5}, edges, res.begin());

  EXPECT_EQ(5, res[0]);
  EXPECT_EQ(4, res[1]);
  EXPECT_EQ(2, res[2]);
  EXPECT_EQ(3, res[3]);
  EXPECT_EQ(1, res[4]);
  EXPECT_EQ(0, res[5]);
}

TEST(DispatchMap, Unary)
{
  typedef dispatch_map<int, 1> map_type;
  typedef typename map_type::value_type value_type;

  map_type map{{any_kind_id, 0}, {scalar_kind_id, 1}, {int32_id, 2}, {float32_id, 3}};
  EXPECT_EQ(value_type(int32_id, 2), *map.find(int32_id));
  EXPECT_EQ(value_type(float32_id, 3), *map.find(float32_id));
  EXPECT_EQ(value_type(scalar_kind_id, 1), *map.find(float64_id));
  EXPECT_EQ(value_type(scalar_kind_id, 1), *map.find(int64_id));
  EXPECT_EQ(value_type(any_kind_id, 0), *map.find(option_id));
}

TEST(DispatchMap, Binary)
{
  typedef dispatch_map<int, 2> map_type;
  typedef typename map_type::value_type value_type;

  map_type map{{{any_kind_id, int64_id}, 0},
               {{scalar_kind_id, int64_id}, 1},
               {{int32_id, int64_id}, 2},
               {{float32_id, int64_id}, 3}};
  EXPECT_EQ(value_type({int32_id, int64_id}, 2), *map.find({int32_id, int64_id}));
  EXPECT_EQ(value_type({float32_id, int64_id}, 3), *map.find({float32_id, int64_id}));
  EXPECT_EQ(value_type({scalar_kind_id, int64_id}, 1), *map.find({float64_id, int64_id}));
  EXPECT_EQ(value_type({scalar_kind_id, int64_id}, 1), *map.find({int64_id, int64_id}));
  EXPECT_EQ(value_type({any_kind_id, int64_id}, 0), *map.find({option_id, int64_id}));
  EXPECT_EQ(map.end(), map.find({int64_id, int32_id}));
}