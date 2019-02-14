// MIT License
//
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <list>
#include <iterator>

// Google Test
#include <gtest/gtest.h>

// Thrust include
#include <thrust/sequence.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/discard_iterator.h>
#include <thrust/iterator/retag.h>

// HIP API
#if THRUST_DEVICE_COMPILER == THRUST_DEVICE_COMPILER_HCC
#include <hip/hip_runtime_api.h>
#include <hip/hip_runtime.h>

#define HIP_CHECK(condition) ASSERT_EQ(condition, hipSuccess)
#endif // THRUST_DEVICE_COMPILER == THRUST_DEVICE_COMPILER_HCC

#include "test_utils.hpp"
#include "test_assertions.hpp"

template<
    class InputType
>
struct Params
{
    using input_type = InputType;
};

template<class Params>
class CopyNTests : public ::testing::Test
{
public:
    using input_type = typename Params::input_type;
};

typedef ::testing::Types<
    Params<thrust::host_vector<short>>,
    Params<thrust::host_vector<int>>,
    Params<thrust::host_vector<long long>>,
    Params<thrust::host_vector<unsigned short>>,
    Params<thrust::host_vector<unsigned int>>,
    Params<thrust::host_vector<unsigned long long>>,
    Params<thrust::host_vector<float>>,
    Params<thrust::host_vector<double>>,
    Params<thrust::device_vector<short>>,
    Params<thrust::device_vector<int>>,
    Params<thrust::device_vector<long long>>,
    Params<thrust::device_vector<unsigned short>>,
    Params<thrust::device_vector<unsigned int>>,
    Params<thrust::device_vector<unsigned long long>>,
    Params<thrust::device_vector<float>>,
    Params<thrust::device_vector<double>>
> CopyNTestsParams;

TYPED_TEST_CASE(CopyNTests, CopyNTestsParams);

#if THRUST_DEVICE_COMPILER == THRUST_DEVICE_COMPILER_HCC

TYPED_TEST(CopyNTests, TestCopyNFromConstIterator)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  std::vector<T> v(5);
  v[0] = T(0); v[1] = T(1); v[2] = T(2); v[3] = T(3); v[4] = T(4);

  typename std::vector<T>::const_iterator begin = v.begin();

  // copy to host_vector
  thrust::host_vector<T> h(5, (T) 10);
  typename thrust::host_vector<T>::iterator h_result = thrust::copy_n(begin, h.size(), h.begin());
  ASSERT_EQ(h[0], T(0));
  ASSERT_EQ(h[1], T(1));
  ASSERT_EQ(h[2], T(2));
  ASSERT_EQ(h[3], T(3));
  ASSERT_EQ(h[4], T(4));
  ASSERT_EQ_QUIET(h_result, h.end());

  // copy to device_vector
  thrust::device_vector<T> d(5, (T) 10);
  typename thrust::device_vector<T>::iterator d_result = thrust::copy_n(begin, d.size(), d.begin());
  ASSERT_EQ(d[0], T(0));
  ASSERT_EQ(d[1], T(1));
  ASSERT_EQ(d[2], T(2));
  ASSERT_EQ(d[3], T(3));
  ASSERT_EQ(d[4], T(4));
  ASSERT_EQ_QUIET(d_result, d.end());
}

TYPED_TEST(CopyNTests, TestCopyNToDiscardIterator)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  thrust::host_vector<T> h_input(5, 1);
  thrust::device_vector<T> d_input = h_input;

  // copy from host_vector
  thrust::discard_iterator<> h_result =
    thrust::copy_n(h_input.begin(), h_input.size(), thrust::make_discard_iterator());

  // copy from device_vector
  thrust::discard_iterator<> d_result =
    thrust::copy_n(d_input.begin(), d_input.size(), thrust::make_discard_iterator());

  thrust::discard_iterator<> reference(5);

  ASSERT_EQ_QUIET(reference, h_result);
  ASSERT_EQ_QUIET(reference, d_result);
}

TYPED_TEST(CopyNTests, TestCopyNMatchingTypes)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  Vector v(5);
  v[0] = T(0); v[1] = T(1); v[2] = T(2); v[3] = T(3); v[4] = T(4);

  // copy to host_vector
  thrust::host_vector<T> h(5, (T) 10);
  typename thrust::host_vector<T>::iterator h_result = thrust::copy_n(v.begin(), v.size(), h.begin());
  ASSERT_EQ(h[0], T(0));
  ASSERT_EQ(h[1], T(1));
  ASSERT_EQ(h[2], T(2));
  ASSERT_EQ(h[3], T(3));
  ASSERT_EQ(h[4], T(4));
  ASSERT_EQ_QUIET(h_result, h.end());

  // copy to device_vector
  thrust::device_vector<T> d(5, (T) 10);
  typename thrust::device_vector<T>::iterator d_result = thrust::copy_n(v.begin(), v.size(), d.begin());
  ASSERT_EQ(d[0], T(0));
  ASSERT_EQ(d[1], T(1));
  ASSERT_EQ(d[2], T(2));
  ASSERT_EQ(d[3], T(3));
  ASSERT_EQ(d[4], T(4));
  ASSERT_EQ_QUIET(d_result, d.end());
}

TYPED_TEST(CopyNTests, TestCopyNMixedTypes)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  Vector v(5);
  v[0] = T(0); v[1] = T(1); v[2] = T(2); v[3] = T(3); v[4] = T(4);

  // copy to host_vector with different type
  thrust::host_vector<float> h(5, (float) 10);
  typename thrust::host_vector<float>::iterator h_result = thrust::copy_n(v.begin(), v.size(), h.begin());

  ASSERT_EQ(h[0], T(0));
  ASSERT_EQ(h[1], T(1));
  ASSERT_EQ(h[2], T(2));
  ASSERT_EQ(h[3], T(3));
  ASSERT_EQ(h[4], T(4));
  ASSERT_EQ_QUIET(h_result, h.end());

  // copy to device_vector with different type
  thrust::device_vector<float> d(5, (float) 10);
  typename thrust::device_vector<float>::iterator d_result = thrust::copy_n(v.begin(), v.size(), d.begin());
  ASSERT_EQ(d[0], T(0));
  ASSERT_EQ(d[1], T(1));
  ASSERT_EQ(d[2], T(2));
  ASSERT_EQ(d[3], T(3));
  ASSERT_EQ(d[4], T(4));
  ASSERT_EQ_QUIET(d_result, d.end());
}

TEST(CopyNTests, TestCopyNVectorBool)
{
  std::vector<bool> v(3);
  v[0] = true; v[1] = false; v[2] = true;

  thrust::host_vector<bool> h(3);
  thrust::device_vector<bool> d(3);

  thrust::copy_n(v.begin(), v.size(), h.begin());
  thrust::copy_n(v.begin(), v.size(), d.begin());

  ASSERT_EQ(h[0], true);
  ASSERT_EQ(h[1], false);
  ASSERT_EQ(h[2], true);

  ASSERT_EQ(d[0], true);
  ASSERT_EQ(d[1], false);
  ASSERT_EQ(d[2], true);
}

TYPED_TEST(CopyNTests, TestCopyNListTo)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  // copy from list to Vector
  std::list<T> l;
  l.push_back(0);
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);

  Vector v(l.size());

  typename Vector::iterator v_result = thrust::copy_n(l.begin(), l.size(), v.begin());

  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 1);
  ASSERT_EQ(v[2], 2);
  ASSERT_EQ(v[3], 3);
  ASSERT_EQ(v[4], 4);
  ASSERT_EQ_QUIET(v_result, v.end());

  l.clear();

  thrust::copy_n(v.begin(), v.size(), std::back_insert_iterator< std::list<T> >(l));

  ASSERT_EQ(l.size(), 5);

  typename std::list<T>::const_iterator iter = l.begin();
  ASSERT_EQ(*iter, 0);  iter++;
  ASSERT_EQ(*iter, 1);  iter++;
  ASSERT_EQ(*iter, 2);  iter++;
  ASSERT_EQ(*iter, 3);  iter++;
  ASSERT_EQ(*iter, 4);  iter++;
}

TYPED_TEST(CopyNTests, TestCopyNCountingIterator)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  thrust::counting_iterator<T> iter(1);

  Vector vec(4);

  thrust::copy_n(iter, 4, vec.begin());

  ASSERT_EQ(vec[0], T(1));
  ASSERT_EQ(vec[1], T(2));
  ASSERT_EQ(vec[2], T(3));
  ASSERT_EQ(vec[3], T(4));
}

TYPED_TEST(CopyNTests, TestCopyNZipIterator)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  Vector v1(3); v1[0] = T(1); v1[1] = T(2); v1[2] = T(3);
  Vector v2(3); v2[0] = T(4); v2[1] = T(5); v2[2] = T(6);
  Vector v3(3, T(0));
  Vector v4(3, T(0));

  thrust::copy_n(thrust::make_zip_iterator(thrust::make_tuple(v1.begin(),v2.begin())),
                 3,
                 thrust::make_zip_iterator(thrust::make_tuple(v3.begin(),v4.begin())));

  ASSERT_EQ(v1, v3);
  ASSERT_EQ(v2, v4);
}

TYPED_TEST(CopyNTests, TestCopyNConstantIteratorToZipIterator)
{
  using Vector = typename TestFixture::input_type;
  using T = typename Vector::value_type;

  Vector v1(3,T(0));
  Vector v2(3,T(0));

  thrust::copy_n(thrust::make_constant_iterator(thrust::tuple<T,T>(4,7)),
                 v1.size(),
                 thrust::make_zip_iterator(thrust::make_tuple(v1.begin(),v2.begin())));

  ASSERT_EQ(v1[0], T(4));
  ASSERT_EQ(v1[1], T(4));
  ASSERT_EQ(v1[2], T(4));
  ASSERT_EQ(v2[0], T(7));
  ASSERT_EQ(v2[1], T(7));
  ASSERT_EQ(v2[2], T(7));
}

template<typename InputIterator, typename Size, typename OutputIterator>
OutputIterator copy_n(my_system &system, InputIterator, Size, OutputIterator result)
{
    system.validate_dispatch();
    return result;
}

TEST(CopyNTests, TestCopyNDispatchExplicit)
{
  thrust::device_vector<int> vec(1);

  my_system sys(0);
  thrust::copy_n(sys,
                 vec.begin(),
                 1,
                 vec.begin());

  ASSERT_EQ(true, sys.is_valid());
}

template<typename InputIterator, typename Size, typename OutputIterator>
OutputIterator copy_n(my_tag, InputIterator, Size, OutputIterator result)
{
    *result = 13;
    return result;
}

TEST(CopyNTests, TestCopyNDispatchImplicit)
{
  thrust::device_vector<int> vec(1);

  thrust::copy_n(thrust::retag<my_tag>(vec.begin()),
                 1,
                 thrust::retag<my_tag>(vec.begin()));

  ASSERT_EQ(13, vec.front());
}

#endif // THRUST_DEVICE_COMPILER == THRUST_DEVICE_COMPILER_HCC
