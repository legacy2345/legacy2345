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

#include <iterator>
#include <utility>


namespace Legacy
{
namespace Core
{

Config::
Config(StringList const& argv)
{
}


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

} // namespace Core
} // namespace Legacy
