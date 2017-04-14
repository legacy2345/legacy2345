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
#include <memory>
#include <streambuf>


namespace Legacy
{
namespace Core
{

/**
 * Severity classifications of log messages.
 */
enum class LogLevel
{
  DEBUG    = 'D',
  VERBOSE  = 'V',
  INFO     = 'I',
  WARNING  = 'W',
  ERROR    = 'E',
  FATAL    = 'F'
};

std::ostream&
operator<<(std::ostream& ostr, LogLevel level);


/**
 * Helper class for setting a tag on the log messages.
 */
class LogTagSetter
{
public:
  std::string const&
  tag() const
  { return tag_; }

private:
  LogTagSetter(std::string const& tag)
  : tag_(tag)
  { }

  friend LogTagSetter const
  log_tag(std::string const& tag);

private:
  std::string const& tag_;
};


/**
 * IO manipulator function to set the log tag for a line.
 */
inline LogTagSetter const
log_tag(std::string const& tag)
{ return LogTagSetter(tag); }

std::ostream&
operator<<(std::ostream& ostr, LogTagSetter const lts);

/**
 * Helper class for the Show Time setting/
 */
class ShowTimeSetter
{
public:
  bool
  show_time() const
  { return show_time_; }

private:
  ShowTimeSetter(bool show_time)
  : show_time_(show_time)
  { }

  friend ShowTimeSetter const
  show_time(bool show_time);

private:
  bool show_time_;
};

/**
 * IO manipulator function to set the show-time flag for a debug stream.
 */
inline ShowTimeSetter const
show_time(bool show_time)
{ return ShowTimeSetter(show_time); }

std::ostream&
operator<<(std::ostream& ostr, ShowTimeSetter const sts);


/**
 * An adaptor to turn any stream into a special stream that formats log
 * messages.
 */
class DebugStreambuf
: public std::streambuf
{
public:
  using traits_type = std::streambuf::traits_type;
  using int_type = std::streambuf::int_type;

public:
  DebugStreambuf(std::streambuf* real_buf);

  void
  set_level(LogLevel level)
  { level_ = level; }

  void
  set_tag(std::string const& tag)
  { tag_ = tag; }

  void
  set_show_time(bool setting = true)
  { show_time_ = setting; }

protected:
  int_type overflow(int_type c = traits_type::eof());

private:
  DebugStreambuf(const DebugStreambuf&) = delete;
  DebugStreambuf& operator=(const DebugStreambuf&) = delete;


  std::streambuf*  real_buf_;
  bool             bol_;
  LogLevel         level_;
  std::string      tag_;
  bool             show_time_;
};


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
  { 
    wrapped_ostream_.rdbuf(file_.rdbuf());
    wrapped_ostream_.setstate(file_.rdstate());
  }

private:
  std::ofstream file_;
};


/**
 * An RAII object to convert an ostream to a debug stream.
 */
class DebugRedirector
: public StreambufRedirector
{
public:
  DebugRedirector(std::ostream& stream)
  : StreambufRedirector(stream)
  , debug_streambuf_(new DebugStreambuf(wrapped_ostream_.rdbuf()))
  { 
    wrapped_ostream_.rdbuf(debug_streambuf_.get());
  }

private:
  std::unique_ptr<DebugStreambuf> debug_streambuf_;
};


} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_LOGGER_H */
