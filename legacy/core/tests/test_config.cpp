/**
 * @file legacy/core/tests/test_config.cpp
 * @brief Tests for the Legacy config unit.
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
#include "legacy/core/tests/mock_filesystem.h"
#include <stdexcept>

using std::out_of_range;
using std::string;
using Legacy::Core::StringList;


SCENARIO("setting and retrieving values from a Config object")
{
  GIVEN("A default-constructed config object, never modified")
  {
    Legacy::Core::Config config;

    WHEN("an attempt is made to get a non-existent int config value")
    {
      THEN("it throws an out_of_range exception")
      {
        REQUIRE_THROWS_AS(config.get<int>("no such tag"), out_of_range);
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
        REQUIRE_THROWS_AS(config.get<double>("no such tag"), out_of_range);
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
        REQUIRE_THROWS_AS(config.get<string>("no such tag"), out_of_range);
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
        REQUIRE_THROWS_AS(config.get<StringList>("no such tag"), out_of_range);
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

  GIVEN("A default-constructed config object with some int values set")
  {
    int test_int_value = 17;
    int not_test_int_value = 91;
    string test_int_tag = "some tag";

    Legacy::Core::Config config;
    config.set(test_int_tag, test_int_value);

    WHEN("the simple get() is called")
    {
      THEN("it returns the same value as was set")
      {
        REQUIRE(config.get<int>(test_int_tag) == test_int_value);
      }
    }
    WHEN("the get() with default is called")
    {
      THEN("it returns the same value as was set and not the default")
      {
        REQUIRE(config.get<int>(test_int_tag, not_test_int_value) == test_int_value);
      }
    }
  }

  GIVEN("A default-constructed config object with some double values set")
  {
    double test_double_value = 17.0;
    double not_test_double_value = 91.0;
    string test_double_tag = "some tag";

    Legacy::Core::Config config;
    config.set(test_double_tag, test_double_value);

    WHEN("the simple get() is called")
    {
      THEN("it returns the same value as was set")
      {
        REQUIRE(config.get<double>(test_double_tag) == test_double_value);
      }
    }
    WHEN("the get() with default is called")
    {
      THEN("it returns the same value as was set and not the default")
      {
        REQUIRE(config.get<double>(test_double_tag, not_test_double_value) == test_double_value);
      }
    }
  }

  GIVEN("A default-constructed config object with some string values set")
  {
    string test_string_value = "seventeem";
    string not_test_string_value = "ninety one";
    string test_string_tag = "some tag";

    Legacy::Core::Config config;
    config.set(test_string_tag, test_string_value);

    WHEN("the simple get() is called")
    {
      THEN("it returns the same value as was set")
      {
        REQUIRE(config.get<string>(test_string_tag) == test_string_value);
      }
    }
    WHEN("the get() with default is called")
    {
      THEN("it returns the same value as was set and not the default")
      {
        REQUIRE(config.get<string>(test_string_tag, not_test_string_value) == test_string_value);
      }
    }
  }

  GIVEN("A default-constructed config object with some StringList values set")
  {
    StringList test_stringlist_value = { "seven", "ten" };
    StringList not_test_stringlist_value = { "ninety", "one" };
    string test_stringlist_tag = "some tag";

    Legacy::Core::Config config;
    config.set(test_stringlist_tag, test_stringlist_value);

    WHEN("the simple get() is called")
    {
      THEN("it returns the same value as was set")
      {
        REQUIRE(config.get<StringList>(test_stringlist_tag) == test_stringlist_value);
      }
    }
    WHEN("the get() with default is called")
    {
      THEN("it returns the same value as was set and not the default")
      {
        REQUIRE(config.get<StringList>(test_stringlist_tag, not_test_stringlist_value) == test_stringlist_value);
      }
    }
  }

  GIVEN("A default-constructed Config object with an int value")
  {
    int original_value = 1;
    int new_value = 2;
    Legacy::Core::Config config;
    config.set("tag", original_value);

    WHEN("an attempt is made to add another value with the same tag and same type")
    {
      config.set("tag", new_value);
      THEN("the new value is returned.")
      {
        REQUIRE(config.get<int>("tag") == new_value);
      }
    }
  }

  GIVEN("A default-constructed Config object with an int value")
  {
    Legacy::Core::Config config;
    config.set("tag", 1);

    WHEN("an attempt is made to add another value with the same tag but a different type")
    {
      THEN("a std::logic_error exception is thrown.")
      {
        REQUIRE_THROWS_AS(config.set("tag", 1.0), std::logic_error);
      }
    }
  }
}

SCENARIO("Finding a data file.")
{
  GIVEN("an empty set of command-line arguments")
  {
    StringList argv{ "test_config" };
    Legacy::Core::Config config;
    Legacy::Core::Tests::MockFileSystem mock_filesystem;
    config.init(Legacy::Core::CLI::OptionSet(), argv, mock_filesystem);

    WHEN("a request is made to open a non-existent file")
    {
      THEN("a null file pointer is returned.")
      {
        auto pf = config.open_data_file(mock_filesystem, "non-existent");
        REQUIRE(!pf);
      }
    }
    WHEN("a request is made to open an existent, readable file")
    {
      THEN("a valid file pointer is returned.")
      {
        auto pf = config.open_data_file(mock_filesystem, "readable");
        REQUIRE(pf);
      }
    }
  }
}
