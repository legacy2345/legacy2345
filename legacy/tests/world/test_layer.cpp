/**
 * @file legacy/tests/world/layer.h
 * @brief Tests for the Legacy world layer unit.
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
#include "legacy/world/maplayer.h"


SCENARIO("basic interface for the MapLayer class")
{
  GIVEN("A MapLayer constructed for given dimensions")
  {
    static const int given_length = 12;
    static const int given_width = 12;
    Legacy::World::MapLayer map_layer(given_length, given_width);

    WHEN("the map layer is first created")
    {
      THEN("its size should match the given dimensions")
      {
        REQUIRE(map_layer.length() == given_length);
        REQUIRE(map_layer.width()  == given_width);
      }
    }
  }
}
