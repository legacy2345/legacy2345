/**
 * @file legacy/character/character.h
 * @brief Public interface of the Legacy character submodule character class.
 */
/*
 * Copyright 2016 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#ifndef LEGACY_CHARACTER_CHARACTER_H_
#define LEGACY_CHARACTER_CHARACTER_H_

#include "legacy/character/sexuality.h"
#include <string>


namespace Legacy
{
namespace Character
{

class CharacterBuilder;

class Character
{
public:
  Character(CharacterBuilder& builder);

  ~Character();

  int
  age() const
  { return age_; }

  std::string const&
  given_name() const
  { return given_name_; }

  std::string const&
  surname() const
  { return surname_; }

private:
  int         age_;
  std::string given_name_;
  std::string surname_;
  Sexuality   sexuality_;
};


} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_CHARACTER_H_ */
