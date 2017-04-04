/**
 * @file legacy/core/filesystem.h
 * @brief Public interface of the Legacy core abstrace filesystem module.
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
#ifndef LEGACY_CORE_FILESYSTEM_H
#define LEGACY_CORE_FILESYSTEM_H

#include <memory>
#include <string>
#include <vector>


namespace Legacy
{
namespace Core
{

/**
 * An abstract representation of an object in a filesystem.
 *
 * For the purpose of this module, a filesystem is a colleciton of named data
 * stores (@e files) organized in a heirarchical tree structure in which each node
 * of the tree (@e directories) also has a name and can be enumerated vian an
 * iterator.
 *
 * A file or directory in the filesystem can identified by a uniaue string (@e path) that
 * consists of hte path of its parent directory with the target file or directory appended.
 * The elements of a path are separated by the path separate character, '/',
 * which can not be used as a part of a file or directory name.
 */
class Path
{
public:
  static const std::string root;
  static const char sep;

public:

  /** Constructs a Path from a string. */
  Path(std::string const& p);

  /** Tears down a Path. */
  ~Path();

  /** Gets the path as a (multibyte) string. */
  std::string
  string() const;

  /** Gets the directory-path parth of the path (if any). */
  std::string
  basename() const;

  /** Gets the filename part of the path. */
  std::string
  dirname() const;

  /** Appends another component to the path. */
  Path&
  operator/=(Path const& rhs);

private:
  std::string path_;
};


inline bool
operator==(Path const& lhs, Path const& rhs)
{ return lhs.string() == rhs.string(); }

inline bool
operator!=(Path const& lhs, Path const& rhs)
{ return !(lhs == rhs); }

inline Path
operator/(Path lhs, Path const& rhs)
{
  return lhs /= rhs;
}

inline Path
operator/(Path lhs, std::string const& rhs)
{
  return lhs /= Path(rhs);
}


/**
 * A(n) (ordered) collection of paths.
 */
using PathList = std::vector<Path>;

/**
 * Creates a PathList from a string containing a colon-separated list of
 * filesystem paths.
 */
PathList
create_pathlist_from_string(std::string const& path_string);


/**
 * A collection of information about a file object.
 */
class FileInfo
{
public:
  virtual
  ~FileInfo() = 0;
  
  virtual std::string
  name() const = 0;

  virtual bool
  exists() const = 0;

  virtual bool
  is_readable() const = 0;

  bool virtual
  is_writable() const = 0;
};

using FileInfoOwningPtr = std::unique_ptr<FileInfo>;


/**
 * An abstract base class for filesystem wrappers.
 */
class FileSystem
{
public:
  virtual
  ~FileSystem() = 0;

  virtual FileInfoOwningPtr
  get_fileinfo(Path const& path) const = 0;
};


} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_FILESYSTEM_H */
