/**
 * @file legacy/world/mapbuildersimple.cpp
 * @brief Implementation of the simple map builder.
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
#include "legacy/world/mapbuildersimple.h"

#include "FastNoise/FastNoise.h"


Legacy::World::MapBuilderSimple::
MapBuilderSimple(unsigned length, unsigned width, unsigned height, std::uint_fast32_t seed)
: length_(length)
, width_(width)
, height_(height)
, seed_(seed)
{ }


Legacy::World::MapBuilderSimple::
~MapBuilderSimple()
{ }


unsigned Legacy::World::MapBuilderSimple::
map_length()
{
  return length_;
}


unsigned Legacy::World::MapBuilderSimple::
map_width()
{
  return width_;
}


unsigned Legacy::World::MapBuilderSimple::
map_height()
{
  return height_;
}


Legacy::World::MapLayerBag Legacy::World::MapBuilderSimple::
layers()
{
  // Set up a noise-based heightmap generator.
  FastNoise noise;
  noise.SetSeed(seed_);
  noise.SetNoiseType(FastNoise::GradientFractal);

  float base_height = map_height() / 2.0f;
  float surface_variance = map_height() / 4.0f;

  Legacy::World::MapLayerBag layers(map_height(), Legacy::World::MapLayer(map_length(), map_width()));
  for (unsigned y = 0; y < map_width(); ++y)
  {
    for (unsigned x = 0; x < map_length(); ++x)
    {
      unsigned height = base_height + surface_variance * noise.GetNoise(x, y) + 1.0f;
      for (unsigned h = 0; h < height; ++h)
      {
        layers[h].set_cell_index_at(x, y, 1);
      }
    }
  }

  return layers;
}

