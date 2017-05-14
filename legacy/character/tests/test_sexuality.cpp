/**
 * @file legacy/tests/character/sexuality.cpp
 * @brief Tests for the Legacy character sexuality submodule.
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
#include "catch.hpp"
#include "legacy/character/sexuality.h"
#include "legacy/core/config.h"
#include "legacy/core/random.h"
#include <sstream>


SCENARIO("the sexuality generator generates a sexuality object without crashing")
{
  Legacy::Core::RandomNumberGenerator rng;
  Legacy::Core::Config                config;

  GIVEN("a generated sexuality")
  {
    Legacy::Character::Sexuality sexuality1 = Legacy::Character::Sexuality::generate(config, rng);
    WHEN("a second sexuality is generated")
    {
      Legacy::Character::Sexuality sexuality2 = Legacy::Character::Sexuality::generate(config, rng);
      THEN("the two sexualities are not equal")
      {
        REQUIRE_FALSE(sexuality1 == sexuality2);
      }
    }
  }
}

SCENARIO("sexuality objects marshall and unmarshall correctly")
{
  Legacy::Core::RandomNumberGenerator rng;
  Legacy::Core::Config                config;

  GIVEN("a generated sexuality")
  {
    Legacy::Character::Sexuality sexuality1 = Legacy::Character::Sexuality::generate(config, rng);

    WHEN("it is marshalled to a stream")
    {
      std::stringstream sstr;
      sstr << sexuality1;

      THEN("when unmarshalled into another objects, the two objects are identical")
      {
        Legacy::Character::Sexuality sexuality2 = Legacy::Character::Sexuality::generate(config, rng);
        REQUIRE_FALSE(sexuality1 == sexuality2);

        sstr >> sexuality2;

        REQUIRE(sexuality1 == sexuality2);
      }
    }
  }
}
