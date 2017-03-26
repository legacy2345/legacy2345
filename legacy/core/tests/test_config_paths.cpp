/**
 * @file legacy/core/tests/test_config_paths.cpp
 * @brief Tests for the Legacy config paths unit.
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
#include "legacy/core/config_paths.h"

#include "legacy/core/config.h"
#include <stdlib.h>

using namespace Legacy::Core;


SCENARIO("determining the HOME directory")
{
  char HOME[] = "/home/some_user";

  GIVEN("the environment variable HOME is set")
  {
    setenv("HOME", HOME, ~0);

    WHEN("get_home_dir() is called")
    {
      THEN("it returns the environment variable value.")
      {
        REQUIRE(get_home_dir() == HOME);
      }
    }
  }
}


SCENARIO("canonicalizing a path")
{
  GIVEN("a path not ending in a path separator")
  {
    std::string path = "/foo/bar";
    WHEN("it is passed to canonicalize_path()")
    {
      std::string canonicalized = canonicalize_path(path);

      THEN("the result ends with a path separator.")
      {
        REQUIRE(canonicalized == path + path_sep);
      }
    }
  }
  GIVEN("a path ending in a path separator")
  {
    std::string path = "/foo/bar" + path_sep;
    WHEN("it is passed to canonicalize_path()")
    {
      std::string canonicalized = canonicalize_path(path);

      THEN("the result is unchanged.")
      {
        REQUIRE(canonicalized == path);
      }
    }
  }
}

SCENARIO("appending app_dir to a path")
{
  std::string path = "/some/path";
  GIVEN("a canonicalized path not ending in the app dir")
  {
    std::string canonicalized_path = canonicalize_path(path);
    WHEN("it is passed to append_app_dir_to_path()")
    {
      THEN("the result has the app_dir appended.")
      {
        REQUIRE(append_app_dir_to_path(canonicalized_path) == canonicalized_path + app_dir);
      }
    }
  }
  GIVEN("a non-canonicalized path not ending in the app dir")
  {
    WHEN("it is passed to append_app_dir_to_path()")
    {
      THEN("the result has the app_dir appended.")
      {
        REQUIRE(append_app_dir_to_path(path) == canonicalize_path(path) + app_dir);
      }
    }
  }
  GIVEN("a canonicalized path ending in the app dir")
  {
    std::string full_path = canonicalize_path(path) + app_dir;
    WHEN("it is passed to append_app_dir_to_path()")
    {
      THEN("the result has the app_dir appended.")
      {
        REQUIRE(append_app_dir_to_path(full_path) == full_path);
      }
    }
  }
}

SCENARIO("getting an environment variable with a fallback default")
{
  char env_value[] = "gabifsplk";
  std::string env_name = "ENV_VAR";
  std::string default_value = "crocket";

  GIVEN("an environment variable is set")
  {
    setenv(env_name.c_str(), env_value, ~0);
    WHEN("get_env_or_default() is called to retrieve it")
    {
      THEN("it returns the variable value.")
      {
        REQUIRE(get_env_or_default(env_name, default_value) == env_value);
      }
    }
  }
  GIVEN("an environment variable is not set")
  {
    unsetenv(env_name.c_str());
    WHEN("get_env_or_default() is called to retrieve it")
    {
      THEN("it returns the default value.")
      {
        REQUIRE(get_env_or_default(env_name, default_value) == default_value);
      }
    }
  }
}

SCENARIO("parsing a colon-separated pathlist into a StringList")
{
  std::string path_1 = "/home/gflingus";
  std::string path_2 = "/usr/share/data";
  GIVEN("an empty pathlist")
  {
    std::string pathlist = "";
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should be empty.")
      {
        REQUIRE(paths.size() == 0);
      }
    }
  }
  GIVEN("a pathlist with one entry, no colons")
  {
    std::string pathlist = path_1;
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should have one entry equal to the original string.")
      {
        REQUIRE(paths.size() == 1);
        REQUIRE(paths[0] == pathlist);
      }
    }
  }
  GIVEN("a pathlist with one entry, one colon at the beginning")
  {
    std::string pathlist = ":" + path_1;
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should have one entry.")
      {
        REQUIRE(paths.size() == 1);
        REQUIRE(paths[0] == path_1);
      }
    }
  }
  GIVEN("a pathlist with one entry, one colon at the end")
  {
    std::string pathlist = path_1 + ":";
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should have one entry.")
      {
        REQUIRE(paths.size() == 1);
        REQUIRE(paths[0] == path_1);
      }
    }
  }
  GIVEN("a pathlist with two entries")
  {
    std::string pathlist = path_1 + ":" + path_2;
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should have two entries.")
      {
        REQUIRE(paths.size() == 2);
        REQUIRE(paths[0] == path_1);
        REQUIRE(paths[1] == path_2);
      }
    }
  }
  GIVEN("a pathlist with two entries and two colons")
  {
    std::string pathlist = path_1 + "::" + path_2;
    WHEN("parse_path_into_strings() is called")
    {
      StringList paths;
      parse_path_into_strings(pathlist, paths);
      THEN("the resulting StringList should have two entries.")
      {
        REQUIRE(paths.size() == 2);
        REQUIRE(paths[0] == path_1);
        REQUIRE(paths[1] == path_2);
      }
    }
  }
}
