/**
 * @file legacy/character/nameconfig.h
 * @brief part of the Legacy character name submodule.
 */
/*
 * Copyright 2015-2016 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#ifndef LEGACY_CHARACTER_NAMECONFIG_H
#define LEGACY_CHARACTER_NAMECONFIG_H

#include <string>


namespace Legacy
{
namespace Character
{

/**
 * Configurable aspects of the character name generator.
 */
class NameConfig
{
public:
  virtual std::string
  generator_type() const;

  virtual std::string
  data_file_path() const;
};


} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_NAMECONFIG_H */
