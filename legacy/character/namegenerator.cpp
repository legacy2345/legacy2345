/**
 * @file legacy/character/namegenerator.cpp
 * @brief part of the Legacy character name submodule.
 */
/*
 * Copyright 2015,2016,2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include "legacy/character/namegenerator.h"
#include "legacy/character/statisticalnamegenerator.h"
#include "legacy/core/posix_filesystem.h"

#include <stdexcept>


/**
 * A static name generator for testing.
 */
class StaticNameGenerator
: public Legacy::Character::NameGenerator
{
public:
  ~StaticNameGenerator() { }

  std::string
  pick_name(Legacy::Character::Sexuality::Gender,
            Legacy::Core::RandomNumberGenerator&)
  {
    return "Moon";
  }
};


/**
 * Abstract base class for various kinds of character name generators.
 */
Legacy::Character::NameGenerator::
~NameGenerator()
{ }


Legacy::Character::NameGenerator::OwningPtr Legacy::Character::
get_name_generator(Core::Config const& config,
                   NameGenerator::Part part)
{
  std::string generator_type = config.get<std::string>("name-generator", "statistical");

  if (generator_type == "static")
  {
    return NameGenerator::OwningPtr(new StaticNameGenerator());
  }
  else if (generator_type == "statistical")
  {
    Core::PosixFileSystem fs;
    return NameGenerator::OwningPtr(new StatisticalNameGenerator(config, fs, part));
  }
  throw std::out_of_range("invalid name generator type specified");
}


