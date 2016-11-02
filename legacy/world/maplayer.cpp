/**
 * @file legacy/world/maplayer.cpp
 * @brief Implementation of the Legacy world MapLayer class.
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
#include "legacy/world/maplayer.h"
#include <stdexcept>


Legacy::World::MapLayer::
MapLayer(unsigned length, unsigned width)
: length_(length)
, width_(width)
, cells_(length*width)
{ }

unsigned
Legacy::World::MapLayer::
length() const
{ return length_; }

unsigned
Legacy::World::MapLayer::
width() const
{ return width_; }


int Legacy::World::MapLayer::
cell_index_at(unsigned x, unsigned y) const
{
  return cells_[this->cell_offset_of(x, y)];
}


unsigned Legacy::World::MapLayer::
cell_offset_of(unsigned x, unsigned y) const
{
  if (x >= length_ || y >= width_)
    throw std::out_of_range("cell index out of range");
  return y * length_ + x;
}

