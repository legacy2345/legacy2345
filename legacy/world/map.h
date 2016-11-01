/**
 * @file legacy/world/map.h
 * @brief Public interface for the Legacy world Map class.
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
#ifndef LEGACY_WORLD_MAP_H_
#define LEGACY_WORLD_MAP_H_

#include "legacy/world/maplayer.h"
#include <vector>


namespace Legacy {
namespace World {


/**
 * A colleciton of MapLayers.
 */
using MapLayerBag = std::vector<MapLayer>;


/**
 * An abstract base class implemented by concrete map builders, used to build
 * maps.
 */
class MapBuilder
{
public:
  virtual ~MapBuilder() = 0;

  // the map extents
  virtual int
  map_length() = 0;

  virtual int
  map_width()  = 0;

  virtual int
  map_height() = 0;

  virtual Legacy::World::MapLayerBag
  layers() = 0;
};


/**
 * The local (playable) part of the world
 */
class Map
{
public:
  Map(MapBuilder& builder);

  int length() const { return length_; }
  int width() const  { return width_;  }
  int height() const { return height_; }

private:
  int          length_;
  int          width_;
  int          height_;
  MapLayerBag  layers_;
};

} // namespace World
} // namespace Legacy

#endif // LEGACY_WORLD_MAP_H_
