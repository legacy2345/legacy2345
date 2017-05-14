/**
 * @file legacy/character/basiccharacterbuilder.cpp
 * @brief Public interface of the basic Legacy character builder class.
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
#include "legacy/character/basiccharacterbuilder.h"


Legacy::Character::BasicCharacterBuilder::
BasicCharacterBuilder(Core::Config const& config, Core::RandomNumberGenerator& rng)
: config_(config)
, rng_(rng)
, givenname_generator_(get_name_generator(config_, NameGenerator::Part::forename))
, surname_generator_(get_name_generator(config_, NameGenerator::Part::surname))
{
}


Legacy::Character::BasicCharacterBuilder::
~BasicCharacterBuilder()
{
}


std::string Legacy::Character::BasicCharacterBuilder::
choose_given_name(Legacy::Character::Sexuality::Gender gender)
{
  return givenname_generator_->pick_name(gender, rng_);
}


std::string Legacy::Character::BasicCharacterBuilder::
choose_surname(Legacy::Character::Sexuality::Gender gender)
{
  return surname_generator_->pick_name(gender, rng_);
}


Legacy::Character::Sexuality Legacy::Character::BasicCharacterBuilder::
choose_sexuality()
{
  return Sexuality::generate(config_, rng_);
}

