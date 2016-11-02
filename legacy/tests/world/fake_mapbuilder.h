/**
 * @file legacy/tests/world/fake_mapbuilder.h
 * @brief A test fake map builder.
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
#ifndef LEGACY_TESTS_WORLD_FAKE_MAPBUILDER_H_
#define LEGACY_TESTS_WORLD_FAKE_MAPBUILDER_H_


#include "legacy/world/map.h"
#include "legacy/world/maplayer.h"


namespace Legacy {
namespace Tests {
namespace World {


class MapBuilderFake
: public Legacy::World::MapBuilder
{
public:
  ~MapBuilderFake()
  {}

  unsigned
  map_length()
  { return 10; }

  unsigned
  map_width()
  { return 10; }

  unsigned
  map_height()
  { return 10; }

  Legacy::World::MapLayerBag
  layers()
  {
    return Legacy::World::MapLayerBag(map_height(),
                          Legacy::World::MapLayer(map_length(), map_width()));
  }
};


} // namespace World
} // namespace Tests
} // namespace Legacy
#endif // LEGACY_TESTS_WORLD_FAKE_MAPBUILDER_H_
