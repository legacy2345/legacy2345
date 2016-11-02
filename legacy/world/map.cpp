/**
 * @file legacy/world/map.cpp
 * @brief Implementation of the Legacy world Map class.
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
#include "legacy/world/map.h"
#include <stdexcept>


Legacy::World::MapBuilder::
~MapBuilder()
{ }


Legacy::World::Map::
Map(MapBuilder& builder)
: length_(builder.map_length())
, width_(builder.map_width())
, height_(builder.map_height())
, layers_(builder.layers())
{ }


Legacy::World::MapLayer& Legacy::World::Map::
layer(unsigned i)
{
  if (i >= height_)
    throw std::out_of_range("layer index out of range");
  return layers_[i];
}
