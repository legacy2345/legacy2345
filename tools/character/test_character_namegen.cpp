/**
 * @file tools/world/test_character_namegen.cpp
 * @brief A tool to exercise the character name generator submodule.
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
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include "legacy/character/nameconfig.h"
#include "legacy/character/namegenerator.h"
#include "legacy/core/random.h"
#include <stdexcept>


void
test_character_namegen(Legacy::Character::NameConfig const& config)
{
  auto given_name_generator = Legacy::Character::get_name_generator(config);
  auto familial_name_generator = Legacy::Character::get_name_generator(config);
  auto rng = Legacy::Core::RandomNumberGenerator();
  std::cerr << given_name_generator->pick_name(rng)
            << " " << familial_name_generator->pick_name(rng)
            << "\n";
}


void
print_help(char const* argv0)
{
  std::cerr << "Usage: " << argv0 << " [ options ]\n"
            << "Options:\n"
            << "  -h, --help                  Prints this message and exits\n";
}


int
main(int argc, char* argv[])
{
  std::string savefile_name;

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
    class FakeNameConfig
    : public Legacy::Character::NameConfig
    {
    public:
      std::string
      generator_type() const override
      { return "static"; }

    } fake_name_config;
    test_character_namegen(fake_name_config);
  }
  catch (std::exception const& ex)
  {
    std::cerr << "exception caught: " << ex.what() << "\nexiting...\n";
    return -1;
  }
  return 0;
}
