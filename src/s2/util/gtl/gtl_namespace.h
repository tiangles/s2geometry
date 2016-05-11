// Copyright 2016 Google Inc. All Rights Reserved.
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

// Temporary header providing transition support for the gtl namespace

#ifndef S2_UTIL_GTL_GTL_NAMESPACE_H_
#define S2_UTIL_GTL_GTL_NAMESPACE_H_

namespace gtl {}

// Namespace alias to support legacy code that refers to util::gtl.
namespace util {
namespace gtl = ::gtl;
}  // namespace util

#endif  // S2_UTIL_GTL_GTL_NAMESPACE_H_