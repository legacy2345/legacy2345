/**
 * @file legacy/core/config_paths.h
 * @brief Internal interface of the Legacy core config paths submodule.
 *
 * This is a collection of functions used to computer various configuration and
 * configured filesystem paths.
 *
 * It's broken into a separate submodule for unit testing purposes and not
 * intended to be exposed to the rest of the stack.
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
#ifndef LEGACY_CORE_CONFIG_PATHS_H
#define LEGACY_CORE_CONFIG_PATHS_H

#include "legacy_config.h"

#include "legacy/core/config.h"
#include <string>


namespace Legacy
{
namespace Core
{

const std::string app_dir = PACKAGE;

/**
 * Gets the current user's "home" directory path.
 */
std::string
get_home_dir();

/**
 * Gets the value of an environment variable, with a default if that variable is
 * not set or is empty.
 */
std::string
get_env_or_default(std::string const& env_name, std::string const& default_value);

} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_CONFIG_PATHS_H */
