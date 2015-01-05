//
// Copyright (C) 2011-14 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>

#include <dynd/array.hpp>
#include <dynd/view.hpp>
#include <dynd/types/convert_type.hpp>
#include <dynd/types/fixedstring_type.hpp>
#include <dynd/types/string_type.hpp>
#include <dynd/types/byteswap_type.hpp>
#include <dynd/array_range.hpp>
#include <dynd/kernels/assignment_kernels.hpp>
#include <dynd/json_parser.hpp>
#include <dynd/func/apply_arrfunc.hpp>
#include <dynd/func/lift_reduction_arrfunc.hpp>
#include <dynd/kernels/reduction_kernels.hpp>

using namespace std;
using namespace dynd;

int main()
{
  dynd::libdynd_init();
  atexit(&dynd::libdynd_cleanup);

  nd::array a, b, c;

  // a = 1;
  // b = 2;
  a = {1, 2, 3};
  b = {3, 5, 2};

  a = a.to_cuda_device();
  b = b.to_cuda_device();

  cout << "a: " << a << endl;
  cout << "b: " << b << endl;
  cout << "CUDA bug case:" << endl;
  c = a + b;
  cout << "c: " << c << endl;

  return 0;
}
