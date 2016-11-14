/**
 * @file legacy/tests/world/test_map_save_and_load.cpp
 * @brief Validate the Legacy World local map save and load.
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
#include "legacy/world/mapbuilderstream.h"
#include <sstream>
#include <stdexcept>


SCENARIO("saving and loading a map object yields an identical copy")
{
  GIVEN("A Map built from a fake map builder")
  {
    Legacy::Tests::World::MapBuilderFake map_builder;
    Legacy::World::Map map(map_builder);

    WHEN("the map is saved to a stream")
    {
      std::stringstream sstr;
      sstr << map;

      THEN("the map loaded from the save it is identical to the original")
      {
        Legacy::World::MapBuilderStream stream_builder(sstr);
        Legacy::World::Map map2(stream_builder);

        REQUIRE(map == map2);
      }
    }
  }
}


SCENARIO("map streamloading failures")
{
  GIVEN("An empty stream")
  {
    std::stringstream sstr;

    WHEN("an attempt is made to laod a map from it")
    {
      THEN("An exception is thrown.")
      {
        CHECK_THROWS_AS(Legacy::World::MapBuilderStream stream_builder(sstr), std::runtime_error);
      }
    }
  }
}

