/**
 * @file legacy/core/argparse.h
 * @brief Public interface of the Legacy core command-line arguemnt parsing submodule.
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
#ifndef LEGACY_CORE_ARGPARSE_H
#define LEGACY_CORE_ARGPARSE_H

#include <functional>
#include <string>
#include <vector>


namespace Legacy
{
namespace Core
{

class Config;

namespace CLI
{

/**
 * Possible results when parsing an option and its arguments.
 */
enum class ActionResult
{
  SUCCESS,
  INVALID_ARG,
  MISSING_ARG,
  TOO_MANY_ARGS
};


/**
 * The callback type for processing options and their arguments.
 */
using OptionAction = std::function<ActionResult(std::string              name,
                                                std::vector<std::string> args,
                                                Config&                  config)>;

/**
 * Appends the argument list to a StringList.
 */
ActionResult
append(std::string name, std::vector<std::string> args, Config& config);

/**
 * Increments the int value.
 */
ActionResult
count(std::string name, std::vector<std::string> args, Config& config);

/**
 * Stores the int value.
 */
ActionResult
store_int(std::string name, std::vector<std::string> args, Config& config);

/**
 * Stores the string value.
 */
ActionResult
store_string(std::string name, std::vector<std::string> args, Config& config);

/**
 * Sets the boolean value.
 */
ActionResult
store_true(std::string name, std::vector<std::string> args, Config& config);

/**
 * Clears the boolean value.
 */
ActionResult
store_false(std::string name, std::vector<std::string> args, Config& config);

/**
 * Prints the version string and exits.
 */
ActionResult
version(std::string name, std::vector<std::string> args, Config& config);


/**
 * A description of an individual command-line option.
 */
struct Option
{
  /**
   * The name of the option or positional argument.
   *
   * Names beginning with two dashes are long-form command-line options,
   * anything else is named positional parameter.
   */
  std::string  name;

  /**
   * The (optional) single-letter command-line switch.
   * A zero indicates no short option equivalent, and the value is ignored if
   * the name is not a long-form command line option.
   */
  char         short_option;

  /**
   * The number of arguments expected by the command-line option.
   *
   * Most options are going to take 0 or 1 arguments, but there is no upper
   * limit, keeping in mind more than 1 integer value does not make sense here.
   *
   * If a specific integer is indicated that number of arguments is mandatory.
   *
   * The special values of '*' (for zero or more arguments, up until the next
   * option) and '+' (for at least one but more up until the next option) are
   * available, under the assumption that 42 or 43 required arguments are
   * ridiculous.
   */
  int          num_args;

  /**
   * What action to take with the option and/or arguments.
   *
   * A set of functions (cf.) are provided with basic operations, or a custom
   * function may be passed.
   */
  OptionAction action;

  /**
   * The Config key value for the option value(s).  If this is the empty string,
   * then a default key is created by trimming off any leading '--' fro the name
   * and using that as the key.
   */
  std::string  config_key;

  /**
   * A descriptive string to appear in the usage/help message.
   */
  std::string  description;
};


/**
 * The set of command-line options to be parsed.
 */
using OptionSet = std::vector<Option>;

/**
 * Possible results from parsing the command-line arguments.
 */
enum struct ArgParseResult
{
  SUCCESS,
  SUCCESS_AND_EXIT,
  INVALID_OPTION
};


/**
 * Parses the given command-line arguments into a COnfig object using the option_list as rules.
 *
 * @arg[in]  option_set the set of options expected
 * @arg[in]  args       the set of command-line arguments supplied
 * @arg[out] config     the Config object into which the parsed arguments should be put
 */
ArgParseResult
arg_parse(OptionSet const& option_set, std::vector<std::string> args, Config& config);

} // namespace CLI
} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_ARGPARSE_H */
