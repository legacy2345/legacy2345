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

