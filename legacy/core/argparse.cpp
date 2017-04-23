
/**
 * @file legacy/core/argparse.cpp
 * @brief Implementation of the Legacy core command-line arguemnt parsing submodule.
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
#include "legacy/core/argparse.h"

#include <cassert>
#include "legacy/core/config.h"
#include <iostream>
#include <stdexcept>


namespace Legacy
{
namespace Core
{
namespace CLI
{

ActionResult
append(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() < 1)
    return ActionResult::MISSING_ARG;

  StringList string_list = config.get<StringList>(name, StringList());
  for (auto const& s: args)
  {
    string_list.push_back(s);
  }
  config.set<StringList>(name, string_list);

  return ActionResult::SUCCESS;
}


ActionResult
count(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() > 0)
    return ActionResult::TOO_MANY_ARGS;

  int count = config.get<int>(name, 0);
  config.set<int>(name, count + 1);

  return ActionResult::SUCCESS;
}


ActionResult
store_int(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() < 1)
    return ActionResult::MISSING_ARG;
  if (args.size() > 1)
    return ActionResult::TOO_MANY_ARGS;

  try
  {
    int val = std::stoi(args[0]);
    config.set<int>(name, val);
  }
  catch (std::exception const&)
  {
    return ActionResult::INVALID_ARG;
  }

  return ActionResult::SUCCESS;
}


ActionResult
store_string(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() < 1)
    return ActionResult::MISSING_ARG;

  std::string string_val;
  for (auto const& s: args) string_val += s;
  config.set<std::string>(name, string_val);

  return ActionResult::SUCCESS;
}


ActionResult
store_true(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() > 0)
    return ActionResult::TOO_MANY_ARGS;

  config.set<int>(name, 1);
  return ActionResult::SUCCESS;
}


ActionResult
store_false(std::string name, std::vector<std::string> args, Config& config)
{
  if (args.size() > 0)
    return ActionResult::TOO_MANY_ARGS;

  config.set<int>(name, 0);
  return ActionResult::SUCCESS;
}


ActionResult
version(std::string, std::vector<std::string>, Config&)
{
  // @TODO: maybe later
  return ActionResult::INVALID_ARG;
}


namespace
{

/**
 * Indicates if the passed argument is an option (begins with a '-') or not.
 */
bool
arg_is_option(std::string const& arg)
{
  if (arg.length() < 2)
    return false;

  return arg[0] == '-';
}

/**
 * Indicates if the passed option is a long-form or a short-form option.
 */
bool
option_is_short_option(std::string const& option)
{
  assert(option.length() >= 2);
  return option[1] != '-';
}

/**
 * Looks for the Option in the option set matching the option found in the
 * command line.
 *
 * @returns the index of the Option found, or the index of one-past-the-end of
 * the option_set if not found.
 */
OptionSet::size_type
match_option(std::string const& option, OptionSet const& option_set)
{
  if (option_is_short_option(option))
  {
    for (OptionSet::size_type optind = 0; optind < option_set.size(); ++optind)
    {
      if (option_set[optind].short_option == option[1])
      {
        return optind;
      }
    }
  }
  else
  {
    for (OptionSet::size_type optind = 0; optind < option_set.size(); ++optind)
    {
      if (option_set[optind].name == option)
      {
        return optind;
      }
    }
  }
  return option_set.size();
}

std::string
get_config_key_from_option(Option const& option)
{
  if (!option.config_key.empty())
  {
    return option.config_key;
  }
  if (option.name.length() > 2 && option.name[0] == '-' && option.name[1] == '-')
  {
    return option.name.substr(2);
  }
  return option.name;
}

} // anonymous namespace


ArgParseResult
arg_parse(OptionSet const& option_set, std::vector<std::string> args, Config& config)
{
  ArgParseResult parse_result = ArgParseResult::SUCCESS;

  std::vector<std::string>::size_type arg_index = 0;
  if (args.size() < 1)
    return ArgParseResult::INVALID_OPTION;

  std::string prog_name = args[arg_index++];

  while (arg_index < args.size())
  {
    std::string const& arg = args[arg_index];
    if (arg == "--version" || arg == "-v")
    {
      version("version", std::vector<std::string>(), config);
      return ArgParseResult::SUCCESS_AND_EXIT;
    }
    else if (arg == "--help" || arg == "-h")
    {
      return ArgParseResult::SUCCESS_AND_EXIT;
    }

    if (arg_is_option(arg))
    {
      auto optind = match_option(arg, option_set);
      if (optind < option_set.size())
      {
        auto const& option = option_set[optind];
        std::vector<std::string> optargs;
        int i = 0;
        while (i < option.num_args && arg_index + i < (args.size()-1))
        {
          ++i;
          optargs.push_back(args[arg_index+i]);
        }
        arg_index += i;
        auto result = option.action(get_config_key_from_option(option), optargs, config);
        if (result != ActionResult::SUCCESS)
        {
          parse_result = ArgParseResult::INVALID_OPTION;
        }
      }
      else
      {
        parse_result = ArgParseResult::INVALID_OPTION;
      }
    }
    else
    {
std::clog << "==smw> arg is not an option\n";
      // TBD
    }
    ++arg_index;
  }

  return parse_result;
}


} // namespace CLI
} // namespace Core
} // namespace Legacy

