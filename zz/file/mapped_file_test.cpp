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

#include "zz/file/mapped_file.h"

#include <gtest/gtest.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <span>
#include <string>
#include <system_error>
#include <type_traits>
#include <utility>

namespace zz {
namespace {

static_assert(!std::is_copy_constructible_v<MappedFile>);
static_assert(!std::is_copy_assignable_v<MappedFile>);
static_assert(std::is_move_constructible_v<MappedFile>);
static_assert(std::is_move_assignable_v<MappedFile>);
static_assert(std::is_same_v<decltype(std::declval<const MappedFile&>().data()),
                             std::span<const uint8_t>>);
static_assert(std::is_same_v<decltype(std::declval<MappedFile&>().data()),
                             std::span<uint8_t>>);

std::string ToString(std::span<const uint8_t> data) {
  return std::string(data.begin(), data.end());
}

class MappedFileTest : public ::testing::Test {
 protected:
  void SetUp() override {
    temp_dir_ = std::filesystem::temp_directory_path() /
                ("zz_mapped_file_test_" + std::to_string(::getpid()));

    std::error_code ec;
    std::filesystem::remove_all(temp_dir_, ec);
    ASSERT_TRUE(std::filesystem::create_directories(temp_dir_, ec))
        << ec.message();
  }

  void TearDown() override {
    std::error_code ec;
    std::filesystem::remove_all(temp_dir_, ec);
  }

  std::filesystem::path WriteFile(const std::string& name,
                                  const std::string& contents) const {
    const std::filesystem::path path = temp_dir_ / name;
    std::ofstream out(path, std::ios::binary);
    out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    out.close();
    return path;
  }

  std::filesystem::path temp_dir_;
};

TEST_F(MappedFileTest, LoadMapsFileContents) {
  const std::string contents = "hello, mapped file!";
  const std::filesystem::path path = WriteFile("contents.txt", contents);

  auto result = MappedFile::Load(path);
  ASSERT_TRUE(result.has_value()) << result.error();

  const MappedFile& mapped = result.value();
  EXPECT_EQ(mapped.data().size(), contents.size());
  EXPECT_EQ(ToString(mapped.data()), contents);
}

TEST_F(MappedFileTest, LoadHandlesBinaryData) {
  const std::string contents("abc\0def\n", 8);
  const std::filesystem::path path = WriteFile("binary.bin", contents);

  auto result = MappedFile::Load(path);
  ASSERT_TRUE(result.has_value()) << result.error();

  const MappedFile& mapped = result.value();
  EXPECT_EQ(mapped.data().size(), contents.size());
  EXPECT_EQ(ToString(mapped.data()), contents);
}

TEST_F(MappedFileTest, LoadAcceptsCStringPath) {
  const std::string contents = "loaded through a C string";
  const std::filesystem::path path = WriteFile("cstring.txt", contents);

  auto result = MappedFile::Load(path.c_str());
  ASSERT_TRUE(result.has_value()) << result.error();

  EXPECT_EQ(ToString(result.value().data()), contents);
}

TEST_F(MappedFileTest, LoadMissingFileReturnsError) {
  const std::filesystem::path path = temp_dir_ / "does_not_exist.txt";

  auto result = MappedFile::Load(path);
  ASSERT_TRUE(result.is_error());
  EXPECT_NE(result.error().find("does not exist"), std::string::npos);
}

TEST_F(MappedFileTest, MoveConstructorTransfersMapping) {
  const std::string contents = "moved contents";
  const std::filesystem::path path = WriteFile("move_ctor.txt", contents);

  auto result = MappedFile::Load(path);
  ASSERT_TRUE(result.has_value()) << result.error();

  MappedFile moved(std::move(result.value()));
  EXPECT_EQ(ToString(moved.data()), contents);

  // The moved-from object should no longer own a mapping.
  EXPECT_TRUE(result.value().data().empty());
}

TEST_F(MappedFileTest, MoveAssignmentReplacesExistingMapping) {
  const std::string first_contents = "first mapping";
  const std::string second_contents = "second mapping";
  const std::filesystem::path first_path =
      WriteFile("first.txt", first_contents);
  const std::filesystem::path second_path =
      WriteFile("second.txt", second_contents);

  auto first = MappedFile::Load(first_path);
  auto second = MappedFile::Load(second_path);
  ASSERT_TRUE(first.has_value()) << first.error();
  ASSERT_TRUE(second.has_value()) << second.error();

  MappedFile mapped(std::move(first.value()));
  EXPECT_EQ(ToString(mapped.data()), first_contents);

  mapped = std::move(second.value());
  EXPECT_EQ(ToString(mapped.data()), second_contents);
  EXPECT_TRUE(second.value().data().empty());
}

TEST_F(MappedFileTest, SelfMoveAssignmentIsNoOp) {
  const std::string contents = "self move";
  const std::filesystem::path path = WriteFile("self_move.txt", contents);

  auto result = MappedFile::Load(path);
  ASSERT_TRUE(result.has_value()) << result.error();

  MappedFile mapped(std::move(result.value()));
  const uint8_t* const data = mapped.data().data();
  const std::size_t size = mapped.data().size();

  MappedFile& self = mapped;
  mapped = std::move(self);

  EXPECT_EQ(mapped.data().data(), data);
  EXPECT_EQ(mapped.data().size(), size);
  EXPECT_EQ(ToString(mapped.data()), contents);
}

}  // namespace
}  // namespace zz
