/**
 * @file tools/character/test_character_namegen.cpp
 * @brief A tool to exercise the character name generator submodule.
 */

/*
 * Copyright 2016,2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include <iostream>
#include "legacy/character/namegenerator.h"
#include "legacy/character/sexuality.h"
#include "legacy/core/argparse.h"
#include "legacy/core/config.h"
#include "legacy/core/logger.h"
#include "legacy/core/posix_filesystem.h"
#include "legacy/core/random.h"
#include <stdexcept>


using Legacy::Character::get_name_generator;
using Legacy::Character::NameGenerator;
using Legacy::Character::Sexuality;
using namespace Legacy::Core;


static CLI::OptionSet option_set = {
  {"--name-generator", 'g', 1, CLI::store_string, "", "string generator name"},
  {"--count",     'n', 1, CLI::store_int,    "", "repetition count"},
};


void
test_character_namegen(Config const& config, RandomNumberGenerator& rng)
{
  auto given_name_generator = get_name_generator(config, NameGenerator::Part::forename);
  auto familial_name_generator = get_name_generator(config, NameGenerator::Part::surname);
  std::cout << given_name_generator->pick_name(Sexuality::Gender::masculine, rng)
            << " " << familial_name_generator->pick_name(Sexuality::Gender::masculine, rng)
            << "\n";
}


int
main(int argc, char* argv[])
{
  DebugRedirector redirected_cerr(std::cerr);
  DebugRedirector redirected_clog(std::clog);
  std::clog << show_time(true);

  Config config;
  StringList args(argv, argv+argc);

  try
  {
    PosixFileSystem fs;
    auto result = config.init(option_set, args, fs);
    if (result != CLI::ArgParseResult::SUCCESS)
    {
      return 1;
    }

    auto rng = Legacy::Core::RandomNumberGenerator();
    int rep_count = config.get("count", 5);
    for (int i = 0; i < rep_count; ++i)
    {
      test_character_namegen(config, rng);
    }
  }
  catch (std::exception const& ex)
  {
    std::cerr << LogLevel::FATAL << "exception caught: " << ex.what() << "\nexiting...\n";
    return -1;
  }
  return 0;
}
