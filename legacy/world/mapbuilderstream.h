/**
 * @file legacy/world/mapbuilderstream.h
 * @brief A builder of maps from IOstreams.
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
#ifndef LEGACY_WORLD_MAPBUILDERSTREAM_H_
#define LEGACY_WORLD_MAPBUILDERSTREAM_H_

#include <iosfwd>
#include "legacy/world/map.h"


namespace Legacy {
namespace World {

/**
 * Builds a stream map.
 */
class MapBuilderStream
: public MapBuilder
{
public:
  MapBuilderStream(std::istream& istr);

  ~MapBuilderStream();

  unsigned
  map_length() override;

  unsigned
  map_width() override;

  unsigned
  map_height() override;

  Legacy::World::MapLayerBag
  layers() override;

private:
  std::istream&  istr_;
  unsigned       length_;
  unsigned       width_;
  unsigned       height_;
};

} // namespace World
} // namespace Legacy

#endif // LEGACY_WORLD_MAPBUILDERSTREAM_H_
