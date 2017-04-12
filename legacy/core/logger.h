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
#ifndef LEGACY_CORE_LOGGER_H
#define LEGACY_CORE_LOGGER_H

#include <iosfwd>
#include <fstream>


namespace Legacy
{
namespace Core
{


/**
 * An RAII object to redirect/restore the original stream buffer of an
 * ostream object.
 *
 * This is necessary because otherwise tearing down the original ostream
 * may result in undefined behaviour, such as a crash on shutdown.
 */
class StreambufRedirector
{
public:
  explicit
  StreambufRedirector(std::ostream& wrapped_ostream)
  : wrapped_ostream_(wrapped_ostream)
  , original_streambuf_(wrapped_ostream_.rdbuf())
  { }

  virtual
  ~StreambufRedirector()
  { wrapped_ostream_.rdbuf(original_streambuf_); }

protected:
  std::ostream&   wrapped_ostream_;
  std::streambuf* original_streambuf_;
};


/**
 * An RAII object to redirect an ostream to a named file.
 */
class StreamRedirector
: public StreambufRedirector
{
public:
  StreamRedirector(std::ostream& stream, std::string const& filename)
  : StreambufRedirector(stream)
  , file_(filename)
  { wrapped_ostream_.rdbuf(file_.rdbuf()); }

private:
  std::ofstream file_;
};


} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_LOGGER_H */
