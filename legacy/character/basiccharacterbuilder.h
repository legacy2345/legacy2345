/**
 * @file legacy/character/basiccharacterbuilder.h
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
#ifndef LEGACY_CHARACTER_BASICCHARACTERBUILDER_H_
#define LEGACY_CHARACTER_BASICCHARACTERBUILDER_H_

#include <legacy/core/random.h>
#include "legacy/character/characterbuilder.h"
#include "legacy/character/characterconfig.h"
#include "legacy/character/namegenerator.h"
#include "legacy/character/sexuality.h"


namespace Legacy
{

namespace Core
{
  class RandomNumberGenerator;
}

namespace Character
{
class BasicCharacterBuilder
: public CharacterBuilder
{
public:
  BasicCharacterBuilder(CharacterConfig const& config, Core::RandomNumberGenerator& rng);

  ~BasicCharacterBuilder();

  std::string
  choose_given_name(Sexuality::Gender gender) override;

  std::string
  choose_surname(Sexuality::Gender gender) override;

  Sexuality
  choose_sexuality() override;

private:
  CharacterConfig             config_;
  Core::RandomNumberGenerator rng_;
  NameGenerator::OwningPtr    givenname_generator_;
  NameGenerator::OwningPtr    surname_generator_;
};


} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_BASICCHARACTERBUILDER_H_ */
