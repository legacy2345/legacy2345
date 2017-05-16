/**
 * @file legacy/tests/character/test_character.cpp
 * @brief Tests for the Legacy character submodule.
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
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "catch_reporter_tap.hpp"
#include "legacy/character/character.h"
#include "legacy/character/characterbuilder.h"
#include "legacy/core/config.h"
#include "legacy/core/random.h"


using Legacy::Character::CharacterBuilder;
using Legacy::Character::Sexuality;


class FakeCharacterBuilder
: public CharacterBuilder
{
  std::string
  choose_given_name(Sexuality::Gender) override
  { return "Jethro"; }

  std::string
  choose_surname(Sexuality::Gender) override
  { return "Smith"; }

  Legacy::Character::Sexuality
  choose_sexuality() override
  {
    Legacy::Core::RandomNumberGenerator rng;
    Legacy::Core::Config                config;

    return Sexuality::generate(config, rng);
  }

};


SCENARIO("A basic instatiation of a charcter object.")
{
  GIVEN("A character builder object")
  {
    FakeCharacterBuilder builder;

    WHEN("a character is constructed")
    {
      Legacy::Character::Character character(builder);
      THEN("it succeeds")
      {
        CHECK(character.age() >= 18);
        CHECK(character.given_name().length() > 0);
        CHECK(character.surname().length() > 0);
      }
    }
  }
}


int
main(int argc, char* argv[])
{
  Catch::Session session;

  int return_code = session.applyCommandLine(argc, argv);
  if (return_code != 0)
    return return_code;

  session.configData().reporterNames.push_back("tap");

  int num_failed = session.run();
  return num_failed < 0xff ? num_failed : 0xff;
}

