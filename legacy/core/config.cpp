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
#include "legacy/core/filesystem.h"
#include "legacy/core/logger.h"
#include <stdlib.h>
#include <unistd.h>
#include <utility>


namespace Legacy
{
namespace Core
{

namespace
{
  PathList
  generate_config_paths()
  {
    PathList config_paths;

    char* cwd = ::getcwd(NULL, 0);
    if (cwd)
    {
      config_paths.push_back(Path(cwd));
      ::free(cwd);
    }

    // user config
    Path user_config(get_env_or_default("XDG_CONFIG_HOME", get_home_dir()+"/.config"));
    config_paths.push_back(user_config / app_dir);

    // system config
    std::string xdg_config_path_string = get_env_or_default("XDG_CONFIG_DIRS", "/etc/xdg");
    PathList xdg_config_paths = create_pathlist_from_string(xdg_config_path_string);
    std::transform(std::begin(xdg_config_paths), std::end(xdg_config_paths),
                   std::back_inserter(config_paths),
                   [](Path const& path) { return path / app_dir; });

    return config_paths;
  }

  PathList
  generate_data_paths()
  {
    PathList data_paths;

    // a subdirectory of the current working directory called 'data', for testing
    char* cwd = ::getcwd(NULL, 0);
    if (cwd)
    {
      data_paths.push_back(Path(cwd));
      ::free(cwd);
    }

    // user data
    Path user_data_path(get_env_or_default("XDG_DATA_HOME", get_home_dir()+"/.local/share"));
    data_paths.push_back(user_data_path / app_dir);

    // XDG data paths
    std::string xdg_data_path_string = get_env_or_default("XDG_DATA_DIRS", " /usr/local/share/:/usr/share/");
    PathList xdg_data_paths = create_pathlist_from_string(xdg_data_path_string);
    std::transform(std::begin(xdg_data_paths), std::end(xdg_data_paths),
                   std::back_inserter(data_paths),
                   [](Path const& path) { return path / app_dir; });

    return data_paths;
  }
} // anonymous namespace


template<> int Config::
get(std::string const& tag) const
{
  return int_values_.at(tag);
}


template<> int Config::
get(std::string const& tag, int default_value) const
{
  auto it = int_values_.find(tag);
  if (it == std::end(int_values_))
  {
    return default_value;
  }
  return it->second;
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
get(std::string const& tag) const
{
  return double_values_.at(tag);
}


template<> double Config::
get(std::string const& tag, double default_value) const
{
  auto it = double_values_.find(tag);
  if (it == std::end(double_values_))
  {
    return default_value;
  }
  return it->second;
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
get(std::string const& tag) const
{
  return string_values_.at(tag);
}


template<> std::string Config::
get(std::string const& tag, std::string default_value) const
{
  auto it = string_values_.find(tag);
  if (it == std::end(string_values_))
  {
    return default_value;
  }
  return it->second;
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
get(std::string const& tag) const
{
  return stringlist_values_.at(tag);
}


template<> std::vector<std::string> Config::
get(std::string const& tag, StringList default_value) const
{
  auto it = stringlist_values_.find(tag);
  if (it == std::end(stringlist_values_))
  {
    return default_value;
  }
  return it->second;
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


void Config::
init(StringList const& args, FileSystem const& fs)
{
  std::string config_file_name;
  StringList  non_options;

  for (auto it = args.begin(); it != args.end(); ++it)
  {
    if (*it == "--config" || *it == "-f")
    {
      auto opt = *it++;
      if (it == args.end())
        throw std::runtime_error("missing argument for " + opt);
      config_file_name = *it;
    }
    else if ((*it)[0] == '-')
    {
      std::cerr << "unknown option '"<< *it << "'\n";
    }
    else
    {
      non_options.push_back(*it);
    }
  }

  config_paths_ = generate_config_paths();
  std::for_each(config_paths_.crbegin(), config_paths_.crend(),
    [this, &fs](Path const& path)
    {
      auto file_info = fs.get_fileinfo(path / "config.txt");
      if (file_info->exists() && file_info->is_readable())
      {
        // looks for and load config file here
      }
    }
  );

  data_paths_ = generate_data_paths();
  set<StringList>("cli-args", non_options);
}


std::unique_ptr<std::istream> Config::
open_data_file(FileSystem const& fs, std::string const& data_file_name) const
{
  auto it = std::find_if(std::begin(data_paths_), std::end(data_paths_),
                          [&fs, &data_file_name](Path const& path) {
                            auto file_info = fs.get_fileinfo(path / data_file_name);
                            std::clog << LogLevel::DEBUG << "trying " << file_info->name() << "\n";
                            return file_info->exists() && file_info->is_readable();
                          });
  if (it == std::end(data_paths_))
    return std::unique_ptr<std::istream>();
  return fs.open_for_input(*it / data_file_name);
}


} // namespace Core
} // namespace Legacy
