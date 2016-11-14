/**
 * @file legacy/world/mapbuilderstream.cpp
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
#include "legacy/world/mapbuilderstream.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>


namespace {

//
// A handy iomanipulator that confirms a fixed string is present in the input
// stream.
//
struct confirm_input
{
  char const *str;

  confirm_input( char const *in )
  : str( in )
  { }

  friend std::istream&
  operator>>(std::istream &istr, confirm_input const& op)
  {
    if (!istr.good())
      return istr;

    std::istream::sentry skip_leading_ws(istr);
    for (char const* p = op.str; *p; ++p)
    {
      if (std::isspace(*p))
      {
        std::istream::sentry k(istr); // discard whitespace
      }
      else
      {
        char c;
        istr.get(c);
        if (c != *p)
        {
          istr.setstate( std::ios::failbit ); // stop extracting
          break;
        }
      }
    }
    return istr;
  }
};

} // anonymous namespace


Legacy::World::MapBuilderStream::
MapBuilderStream(std::istream& istr)
: istr_(istr)
, length_(0), width_(0), height_(0)
{
  std::string version;
  istr_ >> confirm_input("version ");
  if (!istr_)
    throw std::runtime_error("error reading map: expected 'version'");
  istr_ >> version;
  istr_ >> confirm_input("lwh ");
  if (!istr_)
    throw std::runtime_error("error reading map: expected 'lwh'");
  istr_ >> length_ >> width_ >> height_;
  if (!istr_)
    throw std::runtime_error("error reading map: expected integers for l,w,h");
}


Legacy::World::MapBuilderStream::
~MapBuilderStream()
{ }


unsigned Legacy::World::MapBuilderStream::
map_length()
{
  return length_;
}


unsigned Legacy::World::MapBuilderStream::
map_width()
{
  return width_;
}


unsigned Legacy::World::MapBuilderStream::
map_height()
{
  return height_;
}


Legacy::World::MapLayerBag Legacy::World::MapBuilderStream::
layers()
{
  MapLayerBag layers(height_, MapLayer(length_, width_));
  for (unsigned i = 0; i < height_; ++i)
  {
    istr_ >> confirm_input("layer ");
    if (!istr_)
      throw std::runtime_error("error reading map: expected 'layer'");
    int num;
    istr_ >> num;
    if (!istr_)
      throw std::runtime_error("error reading map: expected layer number");
    for (unsigned y = 0; y < width_; ++y)
    {
      for (unsigned x = 0; x < length_; ++x)
      {
        istr_ >> num;
        if (!istr_)
          throw std::runtime_error("error reading map: expected index");
        layers[i].set_cell_index_at(x, y, num);
      }
    }
  }
  return layers;
}

