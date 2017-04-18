/**
 * @file legacy/core/tests/test_logger.cpp
 * @brief Tests for the Legacy core logger module.
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
#include "legacy/core/logger.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace Legacy::Core;


SCENARIO("redirect stderr to a file")
{
  WHEN("stderr is redirected to a known-good file")
  {
    std::string logfile = "/tmp/garbage";
    std::string test_line = "line1";
    {
      StreamRedirector log(std::cerr, logfile);
      std::cerr << test_line << "\n";
    }

    THEN("you should be able to read what is written to it.")
    {
      std::ifstream istr(logfile);
      std::string line1;
      istr >> line1;

      REQUIRE(line1 == test_line);
    }
  }

  WHEN("stderr is redirected to a known-bad file")
  {
    std::string logfile = "/garbage/garbage";
    std::string test_line = "line1";

    StreamRedirector log(std::cerr, logfile);

    THEN("the stream should be left in a bad state.")
    {
      REQUIRE(!std::cerr);
    }
  }
}

SCENARIO("convert an ostream to a debug stream")
{
  WHEN("a stringstream is converted to a debug stream")
  {
    std::string test_string = "valuable lessons";
    std::ostringstream sstr;
    DebugRedirector redirector(sstr);
    THEN("writing to it still has the original string as a line tail.")
    {
      sstr << test_string;
      std::string output_line = sstr.str();

      REQUIRE(output_line.substr(output_line.length() - test_string.length()) == test_string);
    }
  }

  WHEN("a loglevel is set")
  {
    std::string test_string = "strident hippos";
    std::ostringstream sstr;
    DebugRedirector redirector(sstr);

    sstr << LogLevel::WARNING << test_string;
    THEN("an appropriate level is indicated on the output.")
    {
      REQUIRE(sstr.str() == "-W-"+test_string);
    }
  }

  WHEN("a tag is added")
  {
    std::string test_string = "nordic pine";
    std::ostringstream sstr;
    DebugRedirector redirector(sstr);

    sstr << log_tag("spiff") << test_string;
    THEN("an appropriate tag is set on the output.")
    {
      REQUIRE(sstr.str() == "-I-spiff "+test_string);
    }
  }
}
