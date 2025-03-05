// Copyright 2021 Google LLC
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "third_party/highway/hwy/contrib/sort/vqsort.h"  // VQSort

#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "third_party/highway/hwy/contrib/sort/vqsort_128a.cc"
#include "third_party/highway/hwy/foreach_target.h"  // IWYU pragma: keep

// After foreach_target
#include "third_party/highway/hwy/contrib/sort/vqsort-inl.h"

HWY_BEFORE_NAMESPACE();
namespace hwy {
namespace HWY_NAMESPACE {
namespace {

void Sort128Asc(uint128_t* HWY_RESTRICT keys, const size_t num) {
  return VQSortStatic(keys, num, SortAscending());
}

void PartialSort128Asc(uint128_t* HWY_RESTRICT keys, const size_t num,
                       const size_t k) {
  return VQPartialSortStatic(keys, num, k, SortAscending());
}

void Select128Asc(uint128_t* HWY_RESTRICT keys, const size_t num,
                  const size_t k) {
  return VQSelectStatic(keys, num, k, SortAscending());
}

}  // namespace
// NOLINTNEXTLINE(google-readability-namespace-comments)
}  // namespace HWY_NAMESPACE
}  // namespace hwy
HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace hwy {
namespace {
HWY_EXPORT(Sort128Asc);
HWY_EXPORT(PartialSort128Asc);
HWY_EXPORT(Select128Asc);
}  // namespace

void VQSort(uint128_t* HWY_RESTRICT keys, const size_t n, SortAscending) {
  HWY_DYNAMIC_DISPATCH(Sort128Asc)(keys, n);
}

void VQPartialSort(uint128_t* HWY_RESTRICT keys, const size_t n, const size_t k,
                   SortAscending) {
  HWY_DYNAMIC_DISPATCH(PartialSort128Asc)(keys, n, k);
}

void VQSelect(uint128_t* HWY_RESTRICT keys, const size_t n, const size_t k,
              SortAscending) {
  HWY_DYNAMIC_DISPATCH(Select128Asc)(keys, n, k);
}

}  // namespace hwy
#endif  // HWY_ONCE
