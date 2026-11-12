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

#ifndef ZZ_FILE_MAPPED_FILE_H__
#define ZZ_FILE_MAPPED_FILE_H__

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <span>
#include <string>

#include "zz/base/result.h"

namespace zz::file {

class MappedFile {
 public:
  ~MappedFile();

  MappedFile(const MappedFile&) = delete;

  MappedFile(MappedFile&& other) {
    if (&other == this) {
      return;
    }

    Unmap();
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;
  }

  MappedFile& operator=(const MappedFile&) = delete;

  MappedFile& operator=(MappedFile&& rhs) {
    if (&rhs == this) {
      return *this;
    }

    Unmap();
    data_ = rhs.data_;
    size_ = rhs.size_;

    rhs.data_ = nullptr;
    rhs.size_ = 0;
    return *this;
  }

  static Result<MappedFile, std::string> Load(
      const std::filesystem::path& path);

  static Result<MappedFile, std::string> Load(const char* path) {
    return Load(std::filesystem::path(path));
  }

  std::span<const uint8_t> data() const {
    return std::span<const uint8_t>(data_, size_);
  }

  std::span<uint8_t> data() { return std::span<uint8_t>(data_, size_); }

 private:
  MappedFile(uint8_t* data, size_t size) : data_(data), size_(size) {}

  void Unmap();

  uint8_t* data_ = nullptr;
  size_t size_ = 0;
};

}  // namespace zz::file

#endif  // ZZ_FILE_MAPPED_FILE_H__
