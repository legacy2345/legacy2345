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

#include <iostream>
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


Legacy::World::MapLayer const& Legacy::World::Map::
layer(unsigned i) const
{
  if (i >= height_)
    throw std::out_of_range("layer index out of range");
  return layers_[i];
}


std::ostream& Legacy::World::
operator<<(std::ostream& ostr, Map const& map)
{
  ostr << "version 20161108\n";
  ostr << "lwh " << map.length() << " " << map.width() << " " << map.height() << "\n";
  for (unsigned i = 0; i < map.height(); ++i)
  {
    ostr << "layer " << i << "\n";
    ostr << map.layer(i);
  }
  return ostr;
}


bool Legacy::World::
operator==(Map const& lhs, Map const& rhs)
{
  if (lhs.length() != rhs.length()) return false;
  if (lhs.width()  != rhs.width())  return false;
  if (lhs.height() != rhs.height()) return false;

  for (unsigned i = 0; i < lhs.height(); ++i)
  {
    if (lhs.layer(i) != rhs.layer(i)) return false;
  }

  return true;
}
