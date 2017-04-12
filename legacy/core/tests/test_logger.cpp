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

using namespace Legacy::Core;


SCENARIO("redirect stderr to a file")
{
  WHEN("stderr is redirected to a know-good file")
  {
    std::string logfile = "/tmp/garbage";
    std::string test_line = "line1";
    {
      StreamRedirector log(std::cerr, "/tmp/garbage");
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
}
