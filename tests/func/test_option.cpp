//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <inc_gtest.hpp>

#include "../test_memory_new.hpp"
#include "../dynd_assertions.hpp"

#include <dynd/func/option.hpp>

using namespace std;
using namespace dynd;


TEST(Option, IsAvail) {
    nd::array x = nd::empty("?int64");
    nd::assign_na(x);
    EXPECT_FALSE(nd::is_avail(x).as<bool>());

    x = nd::empty("?datetime");
    nd::assign_na(x);
    EXPECT_FALSE(nd::is_avail(x).as<bool>());

    x = parse_json("?time", "\"11:00:13\"");
    EXPECT_TRUE(nd::is_avail(x).as<bool>());
}


TEST(Option, IsAvailArray) {
    nd::array data = parse_json("3 * ?int", "[0, null, 2]");
    nd::array expected = parse_json("3 * bool", "[true, false, true]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("3 * ?int", "[null, null, null]");
    expected = parse_json("3 * bool", "[false, false, false]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("3 * ?datetime", "[null, null, null]");
    expected = parse_json("3 * bool", "[false, false, false]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("3 * ?time", "[\"11:12:11\", \"11:12:12\", \"11:12:13\"]");
    expected = parse_json("3 * bool", "[true, true, true]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("3 * ?void", "[null, null, null]");
    expected = parse_json("3 * bool", "[false, false, false]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("2 * 3 * ?float64", "[[1.0, null, 3.0], [null, \"NaN\", 3.0]]");
    expected = parse_json("2 * 3 * bool", "[[true, false, true], [false, false, true]]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);

    data = parse_json("0 * ?int64", "[]");
    expected = parse_json("0 * bool", "[]");
    EXPECT_ARRAY_EQ(nd::is_avail(data), expected);
}