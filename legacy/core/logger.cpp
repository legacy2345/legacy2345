/**
 * @file legacy/core/logger.h
 * @brief Public interface of the Legacy core logger submodule.
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
#include "legacy/core/logger.h"

namespace Legacy
{
namespace Core
{


std::ostream&
operator<<(std::ostream& ostr, LogLevel level)
{
  auto buf = dynamic_cast<DebugStreambuf<char>*>(ostr.rdbuf());
  if (buf)
  {
    buf->set_level(level);
  }
  return ostr;
}


std::ostream&
operator<<(std::ostream& ostr, LogTagSetter const lts)
{
  auto buf = dynamic_cast<DebugStreambuf<char>*>(ostr.rdbuf());
  if (buf)
  {
    buf->set_tag(lts.tag());
  }
  return ostr;
}

} // namespace Core
} // namespace Legacy


