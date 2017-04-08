/**
 * @file legacy/core/posix_filesystem.cpp
 * @brief Implementation of the Legacy core posix filesystem module.
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
#include "legacy/core/posix_filesystem.h"

#include <fstream>
#include <sys/stat.h>


namespace Legacy
{
namespace Core
{

/**
 * A collection of information about a file object.
 */
class PosixFileInfo
: public FileInfo
{
public:
  PosixFileInfo(Path const& path)
  : path_(path)
  {
    struct stat f_stat;
    int sstat = ::stat(path_.string().c_str(), &f_stat);
    if (0 == sstat)
    {
      exists_ = true;
      if (f_stat.st_mode & S_IRUSR || f_stat.st_mode & S_IRGRP || f_stat.st_mode & S_IROTH)
      {
        is_readable_ = true;
      }
      if (f_stat.st_mode & S_IWUSR || f_stat.st_mode & S_IWGRP || f_stat.st_mode & S_IWOTH)
      {
        is_writable_ = true;
      }
    }
  }

  ~PosixFileInfo() override = default;
  
  std::string 
  name() const override
  { return path_.basename(); }

  bool 
  exists() const override
  { return exists_; }

  bool
  is_readable() const override
  { return is_readable_; }

  bool 
  is_writable() const override
  { return is_writable_; }

private:
  Path path_;
  bool exists_ = false;
  bool is_readable_ = false;
  bool is_writable_ = false;
};


/**
 * An POSIX-based filesystem class.
 */

FileInfoOwningPtr PosixFileSystem::
get_fileinfo(Path const& path) const
{
  FileInfoOwningPtr file_info(new PosixFileInfo(path));
  return file_info;
}


std::unique_ptr<std::istream> PosixFileSystem::
open_for_input(Path const& path) const 
{
  return std::unique_ptr<std::istream>(new std::ifstream(path.string()));
}


} // namespace Core
} // namespace Legacy

