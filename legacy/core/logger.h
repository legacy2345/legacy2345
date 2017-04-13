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

template<typename Char, typename Traits = std::char_traits<Char> >
class DebugStreambuf
: public std::basic_streambuf<Char, Traits>
{
public:
  using traits_type = typename std::basic_streambuf<Char, Traits>::traits_type;
  using int_type = typename std::basic_streambuf<Char, Traits>::int_type;

public:
  DebugStreambuf(std::basic_streambuf<Char, Traits>* real_buf);

protected:
  int_type overflow(int_type c = traits_type::eof());

private:
  DebugStreambuf(const DebugStreambuf&);            ///< unimplimented
  DebugStreambuf& operator=(const DebugStreambuf&); ///< unimplimented


  std::basic_streambuf<Char, Traits>* real_buf_;
  bool                                bol_;
};


template<typename C, typename T>
DebugStreambuf<C,T>::
DebugStreambuf(std::basic_streambuf<C,T>* real_buf)
: real_buf_(real_buf)
, bol_(true)
{ }


template<typename C, typename T>
typename DebugStreambuf<C,T>::int_type DebugStreambuf<C,T>::
overflow(DebugStreambuf<C,T>::int_type c)
{
  int_type retval = traits_type::not_eof(c);
  if (!traits_type::eq_int_type(c, traits_type::eof()))
  {
    if (bol_)
    {
      // Prepend a dummy character for now.
      real_buf_->sputc('!');
      bol_ = false;
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
  , debug_streambuf_(new DebugStreambuf<char>(wrapped_ostream_.rdbuf()))
  { 
    wrapped_ostream_.rdbuf(debug_streambuf_.get());
  }

private:
  std::unique_ptr<DebugStreambuf<char>> debug_streambuf_;
};


} // namespace Core
} // namespace Legacy

#endif /* LEGACY_CORE_LOGGER_H */
