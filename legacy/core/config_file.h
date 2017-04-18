/**
 * @file legacy/core/config_file.h
 * @brief Public interface of the Legacy core config file submodule.
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
#ifndef LEGACY_CORE_CONFIG_FILE_H
#define LEGACY_CORE_CONFIG_FILE_H

#include <string>


namespace Legacy
{
namespace Core
{

/**
 * Looks for a config file in the given path.
 *
 * @returns the fully-qualified file name if found, and empty string otherwise.
 */
std::string
find_config_file_in_path(std::string const& path);

} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_CONFIG_FILE_H */
