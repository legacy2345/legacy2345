/**
 * @file legacy/core/random.cpp
 * @brief Implementation of the Legacy core random number generator.
 */
/*
 * Copyright 2015 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include "legacy/core/random.h"

#include <iostream>


Legacy::Core::RandomNumberGenerator::
RandomNumberGenerator()
: mt_()
{
  std::random_device rd;
  mt_.seed(rd());
}


Legacy::Core::RandomNumberGenerator::
RandomNumberGenerator(Legacy::Core::RandomNumberGenerator::result_type seed)
: mt_(seed)
{ }


Legacy::Core::RandomNumberGenerator::
~RandomNumberGenerator() = default;


Legacy::Core::RandomNumberGenerator::result_type Legacy::Core::RandomNumberGenerator::
min()
{ return mt_.min(); }


Legacy::Core::RandomNumberGenerator::result_type Legacy::Core::RandomNumberGenerator::
max()
{ return mt_.max(); }


Legacy::Core::RandomNumberGenerator::result_type Legacy::Core::RandomNumberGenerator::
operator()()
{ return mt_(); }


std::istream& Legacy::Core::
operator>>(std::istream& istr, Legacy::Core::RandomNumberGenerator& rng)
{
  istr >> rng.mt_;
  return istr;
}


std::ostream& Legacy::Core::
operator<<(std::ostream& ostr, Legacy::Core::RandomNumberGenerator const& rng)
{
  ostr << rng.mt_;
  return ostr;
}

