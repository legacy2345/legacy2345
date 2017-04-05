/**
 * @file legacy/core/test/mock_filesystem.cpp
 * @brief Declaration of a mock Filesystem class.
 */
/*
 * Copyright 2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "legacy/core/tests/mock_filesystem.h"

#include <sstream>


namespace Legacy
{
namespace Core
{
namespace Tests
{

class MockFileInfo
: public FileInfo
{
public:
  MockFileInfo(Path const& path)
  : path_(path)
  {
    if (name() == "non-existent")
      exists_ = false;
    if (name() == "writable")
      is_writable_ = true;
  }

  ~MockFileInfo() = default;
  
  std::string
  name() const
  { return path_.basename(); }

  bool
  exists() const
  { return exists_; }

  bool
  is_readable() const
  { return is_readable_; }

  bool
  is_writable() const
  { return is_writable_; }

  Path path_;
  bool exists_ = true;
  bool is_readable_ = true;
  bool is_writable_ = false;
};

FileInfoOwningPtr MockFileSystem::
get_fileinfo(Path const& path) const
{
  FileInfoOwningPtr file_info(new MockFileInfo(path));
  return file_info;
}


std::unique_ptr<std::istream> MockFileSystem::
open_for_input(Path const&) const
{
  return std::unique_ptr<std::istream>(new std::istringstream("hello"));
}


} // namespace Test
} // namespace core
} // namespace Legacy

