/**
 * @file legacy/core/tests/test_random.cpp
 * @brief Tests for the Legacy core random unit.
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
#include "legacy/core/random.h"
#include <sstream>


SCENARIO("random number generator give expected sequences")
{
  GIVEN("Two default-constructed RNGs")
  {
    Legacy::Core::RandomNumberGenerator rng1;
    Legacy::Core::RandomNumberGenerator rng2;

    WHEN("their generated sequences are compared")
    {
      THEN("at least the first 3 numbers should differ")
      {
        REQUIRE(rng1() != rng2());
        REQUIRE(rng1() != rng2());
        REQUIRE(rng1() != rng2());
      }
    }
  }

  GIVEN("Two RNGs constructed with differnt seeds")
  {
    Legacy::Core::RandomNumberGenerator rng1(123);
    Legacy::Core::RandomNumberGenerator rng2(999);

    WHEN("their generated sequences are compared")
    {
      THEN("at least the first 3 numbers should differ")
      {
        REQUIRE(rng1() != rng2());
        REQUIRE(rng1() != rng2());
        REQUIRE(rng1() != rng2());
      }
    }
  }

  GIVEN("Two RNGs constructed with the same seed")
  {
    Legacy::Core::RandomNumberGenerator rng1(100);
    Legacy::Core::RandomNumberGenerator rng2(100);

    WHEN("their generated sequences are compared")
    {
      THEN("at least the first 3 numbers should be the same")
      {
        REQUIRE(rng1() == rng2());
        REQUIRE(rng1() == rng2());
        REQUIRE(rng1() == rng2());
      }
    }
  }
}

SCENARIO("Legacy Core RNGs can be used with C++ standard distributions")
{
  GIVEN("A RNG")
  {
    Legacy::Core::RandomNumberGenerator rng;
    
    WHEN("it is used with a std random distribution")
    {
      std::normal_distribution<> std_normal;
      THEN("it gives a valid result")
      {
        REQUIRE(std_normal(rng) != 0.0f);
      }
    }
  }
}

SCENARIO("Legacy RNGs have savable, restorable state")
{
  GIVEN("A RNG")
  {
    Legacy::Core::RandomNumberGenerator rng1;

    WHEN("it is advanced, then saved")
    {
      rng1(); rng1(); rng1();
      std::stringstream sstr;
      sstr << rng1;

      THEN("when it is loaded into another RNG object, the resulting sequences are identical")
      {
        Legacy::Core::RandomNumberGenerator rng2;
        sstr >> rng2;

        REQUIRE(rng1() == rng2());
        REQUIRE(rng1() == rng2());
        REQUIRE(rng1() == rng2());
      }
    }
  }
}
