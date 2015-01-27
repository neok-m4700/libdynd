//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

#include <benchmark/benchmark.h>

#include <dynd/func/arithmetic.hpp>
#include <dynd/func/random.hpp>

using namespace std;
using namespace dynd;

static const int size = 256 * 256 * 2;

static void BM_Func_Arithmetic_Add(benchmark::State &state)
{
  nd::array a = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  nd::array b = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  nd::array c = nd::empty(ndt::make_fixed_dim(size, ndt::make_type<float>()));
  while (state.KeepRunning()) {
    static_cast<nd::arrfunc>(nd::add).call_out(a, b, c);
  }
}

BENCHMARK(BM_Func_Arithmetic_Add);

#ifdef DYND_CUDA
static void BM_Func_Arithmetic_CUDADevice_Add(benchmark::State &state)
{
  nd::array a = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  a = a.to_cuda_device();
  nd::array b = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  b = b.to_cuda_device();
  nd::array c = nd::empty(ndt::make_cuda_device(ndt::make_fixed_dim(size, ndt::make_type<float>())));
  while (state.KeepRunning()) {
    static_cast<nd::arrfunc>(nd::add).call_out(a, b, c);
  }
}

BENCHMARK(BM_Func_Arithmetic_CUDADevice_Add);

#endif

static void BM_Func_Arithmetic_Mul(benchmark::State &state)
{
  nd::array a = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  nd::array b = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  nd::array c = nd::empty(ndt::make_fixed_dim(size, ndt::make_type<float>()));
  while (state.KeepRunning()) {
    static_cast<nd::arrfunc>(nd::mul).call_out(a, b, c);
  }
}

BENCHMARK(BM_Func_Arithmetic_Mul);

#ifdef DYND_CUDA

static void BM_Func_Arithmetic_CUDADevice_Mul(benchmark::State &state)
{
  nd::array a = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  a = a.to_cuda_device();
  nd::array b = nd::random::uniform(kwds("dst_tp", ndt::make_fixed_dim(size, ndt::make_type<float>())));
  b = b.to_cuda_device();
  nd::array c = nd::empty(ndt::make_cuda_device(ndt::make_fixed_dim(size, ndt::make_type<float>())));
  while (state.KeepRunning()) {
    static_cast<nd::arrfunc>(nd::mul).call_out(a, b, c);
  }
}

BENCHMARK(BM_Func_Arithmetic_CUDADevice_Mul);

#endif