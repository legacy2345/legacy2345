/**
 * @file legacy/core/config_paths.cpp
 * @brief Implementation of the Legacy core config paths submodule.
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
#include "legacy/core/config_paths.h"

#include <cstdlib>
#include <cstring>
#include <regex>
#include <utility>


std::string Legacy::Core::
get_home_dir()
{
  return std::getenv("HOME");
}


std::string&& Legacy::Core::
canonicalize_path(std::string path)
{
  if (path.find_last_of(path_sep) != path.length()-path_sep.length())
    path += path_sep;
  return std::move(path);
}


std::string&& Legacy::Core::
append_app_dir_to_path(std::string path)
{
  path = canonicalize_path(path);
  int prefix_length =  path.length() - app_dir.length();
  if (prefix_length >= 0)
  {
    if (0 != path.compare(prefix_length, app_dir.length(), app_dir))
    {
      path += app_dir;
    }
  }
  else
  {
    path += app_dir;
  }
  return std::move(path);
}


std::string Legacy::Core::
get_env_or_default(std::string const& env_name, std::string const& default_value)
{
  char const* env_value = std::getenv(env_name.c_str());
  if (env_value && std::strlen(env_value))
  {
    return env_value;
  }
  return default_value;
}


void Legacy::Core::
parse_path_into_strings(std::string const& paths, StringList& path_list)
{
  auto start = paths.begin();
  auto finish = paths.end();
  if (start == finish)
    return;

  while (*start == ':')
    start++;

  std::regex re(":+");
  path_list.insert(path_list.end(),
                   std::sregex_token_iterator(start, finish, re, -1),
                   std::sregex_token_iterator());
}

