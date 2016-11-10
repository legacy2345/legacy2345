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
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include "legacy/world/map.h"
#include "legacy/world/mapbuildersimple.h"
#include "legacy/world/mapbuilderstream.h"
#include <sstream>
#include <stdexcept>


void
dump_map(Legacy::World::Map const& map)
{
  std::cout << "map is " << map.length() << "x" << map.width() << "x" << map.height() << "\n";
  for (unsigned i = 0; i < map.height(); ++i)
  {
    Legacy::World::MapLayer const& layer = map.layer(i);
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
}


void
dump_static_map()
{
  Legacy::World::MapBuilderSimple map_builder(24, 24, 10, 1);
  Legacy::World::Map map(map_builder);
  dump_map(map);
}


void
dump_savefile_map(std::string const& savefile_name)
{
  std::ifstream istr(savefile_name);
  if (!istr)
  {
    std::ostringstream ostr;
    ostr << "error " << errno << " opening '" << savefile_name << "' -- " << std::strerror(errno);
    throw std::runtime_error(ostr.str());
  }

  Legacy::World::MapBuilderStream map_builder(istr);
  Legacy::World::Map map(map_builder);
  dump_map(map);
}


void
print_help(char const* argv0)
{
  std::cerr << "Usage: " << argv0 << " [ options ]\n"
            << "Options:\n"
            << "  -h, --help                  Prints this message and exits\n"
            << "  -f, --save-file=FILENAME    Dumps a map from a named savefile.\n";
}


int
main(int argc, char* argv[])
{
  std::string savefile_name;

  static const option options[] = {
    { "help",       no_argument,       0,    'h' },
    { "save-file",  required_argument, 0,    'f' },
    { NULL,         no_argument,       NULL,  0  }
  };

  while (1)
  {
    int option_index;
    int c = getopt_long(argc, argv, "f:", options, &option_index);
    if (c < 0)
      break;

    switch (c)
    {
      case 'h':
        print_help(argv[0]);
        std::exit(0);
        break;

      case 'f':
        savefile_name = ::optarg;
        break;

      case '?':
        print_help(argv[0]);
        std::exit(1);
        break;
    }
  }

  try
  {
    if (savefile_name.size() > 0)
    {
      dump_savefile_map(savefile_name);
    }
    else
    {
      dump_static_map();
    }
  }
  catch (std::exception const& ex)
  {
    std::cerr << "exception caught: " << ex.what() << "\nexiting...\n";
    return -1;
  }
  return 0;
}
