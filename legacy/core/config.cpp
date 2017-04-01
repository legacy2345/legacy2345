/**
 * @file legacy/core/config.cpp
 * @brief Implementation of the Legacy core config submodule.
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
#include "legacy/core/config.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include "legacy/core/config_paths.h"
#include <stdlib.h>
#include <unistd.h>
#include <utility>


namespace Legacy
{
namespace Core
{

namespace
{
  StringList
  generate_config_paths()
  {
    StringList config_paths;

    char* cwd = ::getcwd(NULL, 0);
    config_paths.emplace_back(canonicalize_path(cwd));
    ::free(cwd);

    // user config
    config_paths.emplace_back(append_app_dir_to_path(get_env_or_default("XDG_CONFIG_HOME",
                                                                        get_home_dir()+"/.config")));

    // system config
    StringList xdg_config_paths;
    parse_path_into_strings(get_env_or_default("XDG_CONFIG_DIRS", "/etc/xdg"), xdg_config_paths);
    std::transform(xdg_config_paths.begin(), xdg_config_paths.end(),
                   std::back_inserter(config_paths),
                   append_app_dir_to_path);
    return config_paths;
  }

  StringList
  generate_data_paths()
  {
    StringList data_paths;

    // a subdirectory of the current working directory called 'data', for testing
    char* cwd = ::getcwd(NULL, 0);
    data_paths.emplace_back(canonicalize_path(cwd) + "data/");
    ::free(cwd);

    // user data
    data_paths.emplace_back(append_app_dir_to_path(get_env_or_default("XDG_DATA_HOME",
                                                                      get_home_dir()+"/.local/share")));

    // system data
    StringList xdg_data_paths;
    parse_path_into_strings(get_env_or_default("XDG_DATA_DIRS", " /usr/local/share/:/usr/share/"), xdg_data_paths);
    std::transform(xdg_data_paths.begin(), xdg_data_paths.end(),
                   std::back_inserter(data_paths),
                   append_app_dir_to_path);
    return data_paths;
  }
} // anonymous namespace


template<> int Config::
get(std::string const& tag)
{
  return int_values_.at(tag);
}


template<> int Config::
get(std::string const& tag, int default_value)
{
  auto it = int_values_.find(tag);
  if (it == std::end(int_values_))
  {
    auto p = int_values_.insert(std::make_pair(tag, default_value));
    it = p.first;
  }
  return it->second;
}


template<> void Config::
set(std::string const& tag, int value)
{
  if (double_values_.find(tag) != double_values_.end()
    || string_values_.find(tag) != string_values_.end()
    || stringlist_values_.find(tag) != stringlist_values_.end())
  {
    throw std::logic_error("invalid config type, expected 'int'");
  }

  int_values_[tag] = value;
}


template<> double Config::
get(std::string const& tag)
{
  return double_values_.at(tag);
}


template<> double Config::
get(std::string const& tag, double default_value)
{
  auto it = double_values_.find(tag);
  if (it == std::end(double_values_))
  {
    auto p = double_values_.insert(std::make_pair(tag, default_value));
    it = p.first;
  }
  return it->second;
}


template<> void Config::
set(std::string const& tag, double value)
{
  if (int_values_.find(tag) != int_values_.end()
    || string_values_.find(tag) != string_values_.end()
    || stringlist_values_.find(tag) != stringlist_values_.end())
  {
    throw std::logic_error("invalid config type, expected 'double'");
  }
  double_values_[tag] = value;
}


template<> std::string Config::
get(std::string const& tag)
{
  return string_values_.at(tag);
}


template<> std::string Config::
get(std::string const& tag, std::string default_value)
{
  auto it = string_values_.find(tag);
  if (it == std::end(string_values_))
  {
    auto p = string_values_.insert(std::make_pair(tag, default_value));
    it = p.first;
  }
  return it->second;
}


template<> void Config::
set(std::string const& tag, std::string value)
{
  if (int_values_.find(tag) != int_values_.end()
    || double_values_.find(tag) != double_values_.end()
    || stringlist_values_.find(tag) != stringlist_values_.end())
  {
    throw std::logic_error("invalid config type, expected 'string'");
  }

  string_values_[tag] = value;
}


template<> std::vector<std::string> Config::
get(std::string const& tag)
{
  return stringlist_values_.at(tag);
}


template<> std::vector<std::string> Config::
get(std::string const& tag, StringList default_value)
{
  auto it = stringlist_values_.find(tag);
  if (it == std::end(stringlist_values_))
  {
    auto p = stringlist_values_.insert(std::make_pair(tag, default_value));
    it = p.first;
  }
  return it->second;
}


template<> void Config::
set(std::string const& tag, StringList value)
{
  if (int_values_.find(tag) != int_values_.end()
    || double_values_.find(tag) != double_values_.end()
    || string_values_.find(tag) != string_values_.end())
  {
    throw std::logic_error("invalid config type, expected 'StringList'");
  }

  stringlist_values_[tag] = value;
}

Config::
Config(StringList const& args)
{
  std::string config_file_name;

  for (auto it = args.begin(); it != args.end(); ++it)
  {
    if (*it == "--config" || *it == "-f")
    {
      auto opt = *it++;
      if (it == args.end())
        throw std::runtime_error("missing argument for " + opt);
      config_file_name = *it;
    }
    else
    {
      std::cerr << "unknown option '"<< *it << "'\n";
    }
  }

  auto config_paths = generate_config_paths();
  std::for_each(config_paths.crbegin(), config_paths.crend(),
    [](std::string const& path)
    {
      std::cerr << "==smw> processing path '" << path << "'\n";
    }
  );

  this->set("data_paths", generate_data_paths());
}


} // namespace Core
} // namespace Legacy
