/**
 * @file tools/core/find_data_file.cpp
 * @brief A tool to exercise the data file location algorithm.
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
#include <algorithm>
#include <iostream>
#include "legacy/core/config.h"
#include "legacy/core/logger.h"
#include "legacy/core/posix_filesystem.h"

using namespace Legacy::Core;
using namespace std;

int
main(int argc, char* argv[])
{
  DebugRedirector logger(cout);
  cout << show_time(true);

  StringList opts { argv, argv+argc };
  Config config;
  CLI::OptionSet  option_set{
    { "cli-args", 0, '+', CLI::append, "", "datafile-name..." },
  };

  PosixFileSystem filesystem;
  auto config_init_result = config.init(option_set, opts, filesystem);
  if (config_init_result != CLI::ArgParseResult::SUCCESS)
  {
    return static_cast<int>(config_init_result);
  }

  StringList args(config.get("cli-args", StringList()));
  assert(args.size() > 0);

  for_each(begin(args), end(args), [&](string const& filename)
           {
             cout << log_tag("find_file") << "\"" << filename << "\": ";
             auto istr = config.open_data_file(filesystem, filename);
             if (istr && istr->good())
             {
               cout << "OK\n";
             }
             else
             {
               cout << "(no)\n";
             }
           });
}
