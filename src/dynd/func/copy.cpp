//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <dynd/func/copy.hpp>
#include <dynd/kernels/copy.hpp>

using namespace std;
using namespace dynd;

nd::callable nd::copy::make()
{
  return callable::make<copy_ck>(ndt::type("(A... * S) -> B... * T"), 0);
}

struct nd::copy nd::copy;

nd::callable nd::broadcast_copy::make()
{
  throw runtime_error("TODO: distinguish copy and broadcast_copy");
}

struct nd::broadcast_copy nd::broadcast_copy;