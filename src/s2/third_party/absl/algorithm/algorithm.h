// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS-IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// -----------------------------------------------------------------------------
// File: algorithm.h
// -----------------------------------------------------------------------------
//
// This header file contains Google extensions to the standard <algorithm> C++
// header.

#ifndef S2_THIRD_PARTY_ABSL_ALGORITHM_ALGORITHM_H_
#define S2_THIRD_PARTY_ABSL_ALGORITHM_ALGORITHM_H_

#include <algorithm>
#include <iterator>

namespace absl {

namespace internal_algorithm {

// Performs comparisons with operator==, similar to C++14's `std::equal_to<>`.
struct EqualTo {
  template <typename T, typename U>
  bool operator()(const T& a, const U& b) const {
    return a == b;
  }
};

template <typename InputIter1, typename InputIter2, typename Pred>
bool EqualImpl(InputIter1 first1, InputIter1 last1, InputIter2 first2,
               InputIter2 last2, Pred pred, std::input_iterator_tag,
               std::input_iterator_tag) {
  while (true) {
    if (first1 == last1) return first2 == last2;
    if (first2 == last2) return false;
    if (!pred(*first1, *first2)) return false;
    ++first1;
    ++first2;
  }
}

template <typename InputIter1, typename InputIter2, typename Pred>
bool EqualImpl(InputIter1 first1, InputIter1 last1, InputIter2 first2,
               InputIter2 last2, Pred pred, std::random_access_iterator_tag,
               std::random_access_iterator_tag) {
  return (last1 - first1 == last2 - first2) &&
         std::equal(first1, last1, first2, pred);
}

}  // namespace internal_algorithm

// -----------------------------------------------------------------------------
// Function Template: equal()
// -----------------------------------------------------------------------------
//
// Compares the equality of two ranges specified by pairs of iterators, using
// the given predicate, returning true iff for each corresponding iterator i1
// and i2 in the first and second range respectively, pred(*i1, *i2) == true
//
// This comparison takes at most min(`last1` - `first1`, `last2` - `first2`)
// invocations of the predicate. Additionally, if InputIter1 and InputIter2 are
// both random-access iterators, and `last1` - `first1` != `last2` - `first2`,
// then the predicate is never invoked and the function returns false.
//
// This is a C++11-compatible implementation of C++14 `std::equal`.  See
// http://en.cppreference.com/w/cpp/algorithm/equal for more information.
template <typename InputIter1, typename InputIter2, typename Pred>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2,
           InputIter2 last2, Pred pred) {
  return internal_algorithm::EqualImpl(
      first1, last1, first2, last2, pred,
      typename std::iterator_traits<InputIter1>::iterator_category{},
      typename std::iterator_traits<InputIter2>::iterator_category{});
}

// Performs comparison of two ranges specified by pairs of iterators using
// operator==.
template <typename InputIter1, typename InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2,
           InputIter2 last2) {
  return absl::equal(first1, last1, first2, last2,
                     internal_algorithm::EqualTo{});
}

// -----------------------------------------------------------------------------
// Function Template: linear_search()
// -----------------------------------------------------------------------------
//
// Performs a linear search for `value` using the iterator `first` up to
// but not including `last`, returning true if [`first`, `last`) contains an
// element equal to `value`.
//
// A linear search is of O(n) complexity which is guaranteed to make at most
// n = (`last` - `first`) comparisons. A linear search over short containers
// may be faster than a binary search, even when the container is sorted.
template <typename InputIterator, typename EqualityComparable>
bool linear_search(InputIterator first, InputIterator last,
                   const EqualityComparable& value) {
  return std::find(first, last, value) != last;
}

}  // namespace absl

#endif  // S2_THIRD_PARTY_ABSL_ALGORITHM_ALGORITHM_H_