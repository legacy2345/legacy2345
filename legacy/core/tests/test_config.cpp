/**
 * @file legacy/core/tests/test_config.cpp
 * @brief Tests for the Legacy config random unit.
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
#include "catch.hpp"
#include "legacy/core/config.h"
#include <stdexcept>

using std::out_of_range;
using std::string;
using Legacy::Core::StringList;


SCENARIO("default constructed config object")
{
  GIVEN("A default-constructed config object")
  {
    Legacy::Core::Config config;

    WHEN("an attempt is made to get a non-existent int config value")
    {
      THEN("it throws an out_of_range exception")
      {
        CHECK_THROWS_AS(config.get<int>("no such tag"), out_of_range);
      }
    }

    WHEN("an attempt is made to get a non-existent int config value with default")
    {
      THEN("it returns the default")
      {
        REQUIRE(config.get<int>("no such tag", 6) == 6);
      }
    }

    WHEN("an attempt is made to get a non-existent double config value")
    {
      THEN("it throws an out_of_range exception")
      {
        CHECK_THROWS_AS(config.get<double>("no such tag"), out_of_range);
      }
    }

    WHEN("an attempt is made to get a non-existent double config value with default")
    {
      THEN("it returns the default")
      {
        REQUIRE(config.get<double>("no such tag", 6.0) == 6.0);
      }
    }

    WHEN("an attempt is made to get a non-existent string config value")
    {
      THEN("it throws an out_of_range exception")
      {
        CHECK_THROWS_AS(config.get<string>("no such tag"), out_of_range);
      }
    }

    WHEN("an attempt is made to get a non-existent string config value with default")
    {
      THEN("it returns the default")
      {
        REQUIRE(config.get<string>("no such tag", "6") == "6");
      }
    }

    WHEN("an attempt is made to get a non-existent StringList config value")
    {
      THEN("it throws an out_of_range exception")
      {
        CHECK_THROWS_AS(config.get<StringList>("no such tag"), out_of_range);
      }
    }

    WHEN("an attempt is made to get a non-existent StringList config value with default")
    {
      StringList default_value{ "five", "six" };

      THEN("it returns the default")
      {
        REQUIRE(config.get<StringList>("no such tag", default_value) == default_value);
      }
    }

  }
}

