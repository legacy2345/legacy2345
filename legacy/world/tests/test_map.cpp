/**
 * @file legacy/tests/world/map.h
 * @brief Tests for the Legacy world map unit.
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
#include "fake_mapbuilder.h"
#include "legacy/world/map.h"
#include "legacy/world/mapbuilderstatic.h"
#include <stdexcept>


SCENARIO("basic interface for the MapBuilderStatic class")
{
  GIVEN("A Static MapBuilder")
  {
    Legacy::World::MapBuilderStatic map_builder;
  }
}

SCENARIO("basic interface for the Map class")
{
  GIVEN("A Map built from a fake map builder")
  {
    Legacy::Tests::World::MapBuilderFake map_builder;
    Legacy::World::Map map(map_builder);

    WHEN("the map is first created")
    {
      THEN("the map size should match the map builder values")
      {
        REQUIRE(map.length() == map_builder.map_length());
        REQUIRE(map.width()  == map_builder.map_width());
        REQUIRE(map.height() == map_builder.map_height());
      }
    }

    WHEN("a requested layer index is out of bounds")
    {
      THEN("an out-of-range exception gets raised")
      {
        CHECK_THROWS_AS(map.layer(map_builder.map_height() + 3), std::out_of_range);
      }
    }

    WHEN("a requested layer is retrieved, it has the right size")
    {
      Legacy::World::MapLayer layer = map.layer(1);
      REQUIRE(layer.length() == map_builder.map_length());
      REQUIRE(layer.width()  == map_builder.map_width());
    }
  }
}

