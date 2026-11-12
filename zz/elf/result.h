/******************************************************************************/
/*                                                                            */
/*  Copyright 2026 The ZZ Project                                             */
/*                                                                            */
/*  Licensed under the Apache License, Version 2.0 (the "License");           */
/*  you may not use this file except in compliance with the License.          */
/*  You may obtain a copy of the License at                                   */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/*  Unless required by applicable law or agreed to in writing, software       */
/*  distributed under the License is distributed on an "AS IS" BASIS,         */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  */
/*  See the License for the specific language governing permissions and       */
/*  limitations under the License.                                            */
/*                                                                            */
/******************************************************************************/

#ifndef ZZ_ELF_RESULT_H__
#define ZZ_ELF_RESULT_H__

#include <cstdint>

#include "zz/base/error.h"
#include "zz/base/result.h"

namespace zz::elf {

enum class ErrorCode : uint32_t {
  kFileNotFound,
  kFileLoadFailed,
  kNotElfFile,
  kInvalidElfFile,
};

using Error = zz::Error<ErrorCode>;

template <typename V>
using Result = zz::Result<V, Error>;

}  // namespace zz::elf

#endif  // ZZ_ELF_RESULT_H__
