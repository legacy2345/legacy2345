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

#include <iomanip>
#include <iostream>
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
{ return cells_[this->cell_offset_of(x, y)]; }


void Legacy::World::MapLayer::
set_cell_index_at(unsigned x, unsigned y, int index)
{ cells_[this->cell_offset_of(x, y)] = index; }


unsigned Legacy::World::MapLayer::
cell_offset_of(unsigned x, unsigned y) const
{
  if (x >= length_ || y >= width_)
    throw std::out_of_range("cell index out of range");
  return y * length_ + x;
}


std::ostream& Legacy::World::
operator<<(std::ostream& ostr, MapLayer const& layer)
{
  for (unsigned y = 0; y < layer.width(); ++y)
  {
    for (unsigned x = 0; x < layer.length(); ++x)
    {
      ostr << std::setw(4) << layer.cell_index_at(x, y);
    }
    ostr << "\n";
  }
  return ostr;
}


bool Legacy::World::
operator==(MapLayer const& lhs, MapLayer const& rhs)
{
  if (lhs.length() != rhs.length())
    return false;

  if (lhs.width() != rhs.width())
    return false;

  for (unsigned y = 0; y < lhs.width(); ++y)
  {
    for (unsigned x = 0; x < lhs.length(); ++x)
    {
      if (lhs.cell_index_at(x, y) != rhs.cell_index_at(x, y))
        return false;
    }
  }

  return true;
}
