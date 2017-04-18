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


