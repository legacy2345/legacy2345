/**
 * @file legacy/core/filesystem.cpp
 * @brief Implementation of the Legacy core abstrace filesystem module.
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
#include "legacy/core/filesystem.h"

#include <algorithm>
#include <iterator>
#include <regex>


namespace Legacy
{
namespace Core
{

const std::string Path::root = "/";
const char Path::sep = '/';

Path::
Path(std::string const& p)
: path_(p)
{
  // trim any trailing sep
  if (path_.length() > 1 && path_.back() == sep)
  {
    path_ = path_.substr(0, path_.size()-1);
  }
}


Path::
~Path()
{
}

std::string Path::
string() const
{
  return path_;
}

std::string Path::
basename() const
{
  if (path_.length() == 0)
    return "";
  if (path_.length() == 1 && path_[0] == sep)
    return root;

  auto s = path_.length() - 1;
  auto t = s;
  if (path_[s] == sep)
  {
    --s;
    --t;
  }
  while (s > 0 && path_[s] != sep)
    --s;
 
  // Special case path starting with slash
  if (path_[s] == sep)
    s = s+1;
  return path_.substr(s, t-s+1);
}


std::string Path::
dirname() const
{
  auto s = path_.length() - 1;
  for (; s > 1; --s)
  {
    if (path_[s] == sep)
    {
      return path_.substr(0, s);
    }
  }
  if (path_[s] == sep)
    return root;
  return ".";
}


Path& Path::
operator/=(Path const& rhs)
{
  path_ = path_ + sep + rhs.path_;
  return *this;
}

PathList
create_pathlist_from_string(std::string const& path_string)
{
  PathList pathlist;

  auto start = std::begin(path_string);
  auto finish = std::end(path_string);
  if (start == finish)
    return pathlist;

  // Skip any leading path separators.
  while (*start == ':')
    start++;

  // Magic for the uninitiated: this chunk of code will add a Path to
  // pathlist for every chunk of the path_string that is *not* a path
  // separator.
  //
  // Yeah, I could just walk the string using two pointers or walk using two
  // indexes and the substr() operator.  Where is the elegance in that?
  //
  std::regex re(":+");
  std::transform(std::sregex_token_iterator(start, finish, re, -1),
                 std::sregex_token_iterator(),
                 std::back_inserter(pathlist),
                 [](std::sregex_token_iterator::value_type const& sm)
                 {
                   return Path(std::string(sm));
                 });

  return pathlist;
}


FileInfo::
~FileInfo()
{ }

FileSystem::
~FileSystem()
{ }

} // namespace Core
} // namespace Legacy

