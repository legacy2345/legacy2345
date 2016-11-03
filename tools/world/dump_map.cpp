/**
 * @file tools/world/dump_map.cpp
 * @brief A tool to dump a map as text.
 * This tool is a test driver for the Legacy 2345 local map.
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
#include <iostream>
#include "legacy/world/map.h"
#include "legacy/world/mapbuildersimple.h"


int
main(int argc, char* argv[])
{
  Legacy::World::MapBuilderSimple map_builder(48, 48, 20, 1);
  Legacy::World::Map map(map_builder);

  std::cout << "map is " << map.length() << "x" << map.width() << "x" << map.height() << "\n";
  for (unsigned i = 0; i < map.height(); ++i)
  {
    Legacy::World::MapLayer& layer = map.layer(i);
    std::cout << "layer " << i << "\n";
    for (unsigned y = 0; y < layer.width(); ++y)
    {
      for (unsigned x = 0; x < layer.length(); ++x)
      {
        std::cout << layer.cell_index_at(x, y) << " ";
      }
      std::cout << "\n";
    }
  }

  return 0;
}
