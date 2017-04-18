/**
 * @file legacy/tests/character/test_name_generator.cpp
 * @brief Tests for the Legacy character name generator submodule.
 */

/*
 * Copyright 2016-2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include "legacy/character/nameconfig.h"
#include "legacy/character/namegenerator.h"
#include <sstream>
#include <stdexcept>


SCENARIO("The name generator factory handles invalid input.")
{
  GIVEN("A fake name config that asks for an invalid generator type")
  {
    class FakeNameConfig
    : public Legacy::Character::NameConfig
    {
    public:
      std::string
      generator_type() const override
      { return "garbage"; }

    } fake_name_config;

    WHEN("the name generator factory is asked for a name generator")
    {
      THEN("it throws an exception.")
      {
        CHECK_THROWS_AS(auto junk = Legacy::Character::get_name_generator(fake_name_config,
                                                                          Legacy::Character::NameGenerator::Part::surname),
                        std::out_of_range);
      }
    }
  }
}

