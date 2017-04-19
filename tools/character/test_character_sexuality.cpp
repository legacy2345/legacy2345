/**
 * @file tools/character/test_character_sexuality.cpp
 * @brief A tool to exercise the character sexuality generator submodule.
 */

/*
 * Copyright 2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include "legacy/character/sexuality.h"
#include "legacy/core/config.h"
#include "legacy/core/random.h"
#include <stdexcept>


static void
test_character_sexuality(Legacy::Core::Config const&         config,
                         Legacy::Core::RandomNumberGenerator rng)
{
  auto sexuality = Legacy::Character::Sexuality::generate(config, rng);
  std::cout << sexuality << "\n";
}


static void
print_help(char const* argv0)
{
  std::cerr << "Usage: " << argv0 << " [ options ]\n"
            << "Options:\n"
            << "  -h, --help                  Prints this message and exits\n";
}


int
main(int argc, char* argv[])
{
  Legacy::Core::Config config;

  static const option options[] = {
    { "help",       no_argument,       0,    'h' },
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

      case '?':
        print_help(argv[0]);
        std::exit(1);
        break;
    }
  }

  try
  {
    Legacy::Core::RandomNumberGenerator rng;
    test_character_sexuality(config, rng);
  }
  catch (std::exception const& ex)
  {
    std::cerr << "exception caught: " << ex.what() << "\nexiting...\n";
    return -1;
  }
  return 0;
}
