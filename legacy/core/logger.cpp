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

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Legacy
{
namespace Core
{


std::ostream&
operator<<(std::ostream& ostr, LogLevel level)
{
  auto buf = dynamic_cast<DebugStreambuf*>(ostr.rdbuf());
  if (buf)
  {
    buf->set_level(level);
  }
  return ostr;
}


std::ostream&
operator<<(std::ostream& ostr, LogTagSetter const lts)
{
  auto buf = dynamic_cast<DebugStreambuf*>(ostr.rdbuf());
  if (buf)
  {
    buf->set_tag(lts.tag());
  }
  return ostr;
}


std::ostream&
operator<<(std::ostream& ostr, ShowTimeSetter const sts)
{
  auto buf = dynamic_cast<DebugStreambuf*>(ostr.rdbuf());
  if (buf)
  {
    buf->set_show_time(sts.show_time());
  }
  return ostr;
}


DebugStreambuf::
DebugStreambuf(std::streambuf* real_buf)
: real_buf_(real_buf)
, bol_(true)
, level_(LogLevel::INFO)
, show_time_(false)
{ }


DebugStreambuf::int_type DebugStreambuf::
overflow(DebugStreambuf::int_type c)
{
  int_type retval = traits_type::not_eof(c);
  if (!traits_type::eq_int_type(c, traits_type::eof()))
  {
    if (bol_)
    {
      if (show_time_)
      {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%dT%X");
        auto timestamp = ss.str();
        real_buf_->sputn(timestamp.c_str(), timestamp.length());
      }

      real_buf_->sputc('-');
      real_buf_->sputc(static_cast<char>(level_));
      real_buf_->sputc('-');
      bol_ = false;
      level_ = LogLevel::INFO;

      if (!tag_.empty())
      {
        real_buf_->sputn(tag_.c_str(), tag_.length());
        real_buf_->sputc(' ');
        tag_.clear();
      }
    }

    // Send the real character out.
    retval =  real_buf_->sputc(c);

    // If the end-of-line was seen, reset the beginning-of-line indicator and
    // the default log level.
    if (traits_type::eq_int_type(c, traits_type::to_int_type('\n')))
    {
      bol_ = true;
    }
  }

  return retval;
}


} // namespace Core
} // namespace Legacy


