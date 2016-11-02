/**
 * @file legacy/world/mapbuilderstatic.h
 * @brief A builder of static maps.
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
#ifndef LEGACY_WORLD_MAPBUILDERSTATIC_H_
#define LEGACY_WORLD_MAPBUILDERSTATIC_H_

#include "legacy/world/map.h"


namespace Legacy {
namespace World {

/**
 * Builds a static map.
 */
class MapBuilderStatic
: public MapBuilder
{
public:
  ~MapBuilderStatic();

  unsigned
  map_length() override;

  unsigned
  map_width() override;

  unsigned
  map_height() override;

  Legacy::World::MapLayerBag
  layers() override;
};

} // namespace World
} // namespace Legacy

#endif // LEGACY_WORLD_MAPBUILDERSTATIC_H_
