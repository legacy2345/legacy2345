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

#include <map>
#include <string>
#include <vector>


namespace Legacy
{
namespace Core
{


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
  template<typename T> T
  get(std::string const& tag);

  template<typename T> T
  get(std::string const& tag, T default_value);

private:
  std::map<std::string, int>         int_values_;
  std::map<std::string, double>      double_values_;
  std::map<std::string, std::string> string_values_;
  std::map<std::string, StringList>  stringlist_values_;
};

} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_CONFIG_H */
