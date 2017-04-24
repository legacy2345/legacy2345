/**
 * @file legacy/core/config.h
 * @brief Public interface of the Legacy core config submodule.
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
#ifndef LEGACY_CORE_CONFIG_H
#define LEGACY_CORE_CONFIG_H

#include "legacy/core/argparse.h"
#include "legacy/core/filesystem.h"
#include <map>
#include <string>
#include <vector>


namespace Legacy
{
namespace Core
{

class FileSystem;

/**
 * A collection of strings.
 */
using StringList = std::vector<std::string>;


/**
 * A set of configuration values.
 *
 * Yer typical usage would be to retrieve a value by tag.  For example,
 *
 * int leg_length = config.get<int>("leg_length")
 */
class Config
{
public:

  /**
   * Initializes the configuration from command-line arguments and files.
   *
   * This is not an initializer and is not required to construct a valid Config
   * object.  It's for setting up an initial configuration from values passed
   * on the command line and set in config files, for which the loading order
   * can be affected by the command-line arguments.
   */
  CLI::ArgParseResult
  init(CLI::OptionSet const& option_set, StringList const& argv, FileSystem const& fs);

  template<typename T> T
  get(std::string const& tag);

  template<typename T> T
  get(std::string const& tag, T default_value);

  template<typename T> void
  set(std::string const& tag, T value);

  /**
   * Finds and opens a file in the given filesystem using the configured
   * data file search paths.
   * @param[in] fs              The filesystem to search for the file.
   * @param[in] data_file_name  The name of the data file.
   *
   * @returns a pointer to an opened input stream if one is found, otherwise a null
   * pointer.
   */
  std::unique_ptr<std::istream>
  open_data_file(FileSystem const& fs, std::string const& data_file_name);

private:
  std::map<std::string, int>         int_values_;
  std::map<std::string, double>      double_values_;
  std::map<std::string, std::string> string_values_;
  std::map<std::string, StringList>  stringlist_values_;

  PathList                           config_paths_;
  PathList                           data_paths_;
};

} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_CONFIG_H */
