/**
 * @file legacy/character/character.cpp
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
#include "legacy/character/character.h"

#include "legacy/character/characterbuilder.h"


Legacy::Character::Character::
Character(Legacy::Character::CharacterBuilder& builder)
: age_(builder.age())
, given_name_(builder.choose_given_name())
, surname_(builder.choose_surname())
, sexuality_(builder.choose_sexuality())
{ }

Legacy::Character::Character::
~Character()
{ }
