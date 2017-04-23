/**
 * @file legacy/core/tests/test_argparse.cpp
 * @brief Tests for the Legacy core argparse module.
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
#include "legacy/core/argparse.h"

#include "legacy/core/config.h"


using namespace Legacy::Core;


SCENARIO("no options expected")
{
  CLI::OptionSet option_set = { };
  Config config;

  WHEN("the version is requested")
  {
    StringList args = { "prog", "--version" };
    THEN("a version string is printed on stderr and success-with-exit is returned")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS_AND_EXIT);
    }
  }

  WHEN("help is requested")
  {
    StringList args = { "prog", "--help" };
    THEN("a help message is printed on stderr and success-with-exit is returned")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS_AND_EXIT);
    }
  }

  WHEN("an unexpect option is submitted")
  {
    StringList args = { "prog", "--garbage", "trash" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }
}

SCENARIO("some basic simple options are expected")
{
  CLI::OptionSet option_set = {
    { "--append",  'a',  1, CLI::append,       "", "test StringList appending" },
    { "--string",  's',  1,  CLI::store_string, "", "test string storage" },
    { "--int",     'i',  1,  CLI::store_int,    "", "test int storage" },
    { "--true",    't',  0,  CLI::store_true,   "", "test true storage" },
    { "--unfalse", 'u',  1,  CLI::store_true,   "", "test true storage with useless argument" },
    { "--false",   'f',  0,  CLI::store_false,  "", "test false storage" },
  };
  Config config;

  WHEN("a string long option is passed")
  {
    StringList args = { "prog", "--string", "buffalo" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<std::string>("string") == "buffalo");
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("a string short option is passed")
  {
    StringList args = { "prog", "-s", "bison" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<std::string>("string") == "bison");
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("a string long option is passed without an argument")
  {
    StringList args = { "prog", "--string" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("an int long option is passed")
  {
    StringList args = { "prog", "--int", "7" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<int>("int") == 7);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("an int short option is passed")
  {
    StringList args = { "prog", "-i", "8" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<int>("int") == 8);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("an int long option is passed with a missing argument")
  {
    StringList args = { "prog", "--int" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("an int long option is passed with an invalid argument")
  {
    StringList args = { "prog", "--int", "kk" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("a bool(true) long option is passed")
  {
    StringList args = { "prog", "--true" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<int>("true"));
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("a bool(true) short option is passed")
  {
    StringList args = { "prog", "-t" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<int>("true"));
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("a bool(true) long option is passed but an argument is expected")
  {
    StringList args = { "prog", "--unfalse", "z" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("a bool(false) long option is passed")
  {
    StringList args = { "prog", "--false" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(!config.get<int>("false"));
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("a bool(false) short option is passed")
  {
    StringList args = { "prog", "-f" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(!config.get<int>("false"));
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("an append option is passed")
  {
    StringList args = { "prog", "--append", "one" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<StringList>("append") == StringList{ "one" });
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }
}

SCENARIO("one positional arguments is expected")
{
  CLI::OptionSet option_set = {
    { "positional-arg",  0,  1, CLI::store_string, "", "a positional argument" },
  };
  Config config;

  WHEN("a value is passed")
  {
    StringList args = { "prog", "value" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(config.get<std::string>("positional-arg") == "value");
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("no value is passed")
  {
    StringList args = { "prog" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }
}

SCENARIO("two positional arguments are expected")
{
  CLI::OptionSet option_set = {
    { "positional-arg",  0,  2, CLI::append, "", "a positional argument" },
  };
  Config config;

  WHEN("two values are passed")
  {
    StringList args = { "prog", "value1", "value2" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      StringList expected_results{ "value1", "value2" };
      REQUIRE(config.get<StringList>("positional-arg") == expected_results);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("no value is passed")
  {
    StringList args = { "prog" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("only one value is passed")
  {
    StringList args = { "prog", "rock" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }
}

SCENARIO("positional arguments with wildcard count is expected")
{
  CLI::OptionSet option_set = {
    { "positional-arg",  0, '+', CLI::append, "", "a positional argument" },
  };
  Config config;

  WHEN("two values are passed")
  {
    StringList args = { "prog", "value1", "value2" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      StringList expected_results{ "value1", "value2" };
      REQUIRE(config.get<StringList>("positional-arg") == expected_results);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }

  WHEN("no value is passed")
  {
    StringList args = { "prog" };
    THEN("failure is indicated.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      REQUIRE(result == CLI::ArgParseResult::INVALID_OPTION);
    }
  }

  WHEN("only one value is passed")
  {
    StringList args = { "prog", "rock" };
    THEN("it is properly stored in the Config object and success is returned.")
    {
      auto result = CLI::arg_parse(option_set, args, config);
      StringList expected_results{ "rock" };
      REQUIRE(config.get<StringList>("positional-arg") == expected_results);
      REQUIRE(result == CLI::ArgParseResult::SUCCESS);
    }
  }
}

