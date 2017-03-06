/**
 * @file legacy/character/characterbuilder.h
 * @brief Public interface of the Legacy character builder class.
 */
/*
 * Copyright 2015-2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#ifndef LEGACY_CHARACTER_CHARACTERBUILDER_H_
#define LEGACY_CHARACTER_CHARACTERBUILDER_H_

#include "legacy/character/sexuality.h"
#include <string>


namespace Legacy
{
namespace Character
{

class CharacterBuilder
{
public:
  virtual
  ~CharacterBuilder() = 0;

  virtual int
  age();

  virtual std::string
  choose_given_name(Sexuality::Gender gender) = 0;

  virtual std::string
  choose_surname(Sexuality::Gender gender) = 0;

  virtual Sexuality
  choose_sexuality() = 0;
};


} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_CHARACTERBUILDER_H_ */
