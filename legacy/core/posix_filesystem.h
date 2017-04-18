/**
 * @file legacy/core/posix_filesystem.h
 * @brief Public interface of the Legacy core posix filesystem module.
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
#ifndef LEGACY_CORE_POSIX_FILESYSTEM_H
#define LEGACY_CORE_POSIX_FILESYSTEM_H

#include "legacy/core/filesystem.h"


namespace Legacy
{
namespace Core
{


/**
 * An POSIX-based filesystem class.
 */
class PosixFileSystem
: public FileSystem
{
public:
  ~PosixFileSystem() override = default;

  FileInfoOwningPtr
  get_fileinfo(Path const& path) const override;

  std::unique_ptr<std::istream>
  open_for_input(Path const&) const override;
};


} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_POSIX_FILESYSTEM_H */
