/**
 * @file legacy/character/sexuality.cpp
 * @brief Implementation of the Legacy random number generator module.
 */
/*
 * Copyright 2015,2016,2017 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include <legacy/character/sexuality.h>

#include <cstdlib>
#include <iostream>
#include <legacy/core/random.h>


Legacy::Character::Sexuality::
Sexuality(Physically sex,
          double     gender_bias,
          double     same_sex_pref,
          double     opposite_sex_pref)
: sex_(sex)
, gender_bias_(gender_bias)
, same_sex_pref_(same_sex_pref)
, opposite_sex_pref_(opposite_sex_pref)
{ }


Legacy::Character::Sexuality::Gender Legacy::Character::Sexuality::
gender() const
{
  if (gender_bias_ > 0.90)
  {
    return (sex_ == Physically::male ? Gender::feminine : Gender::masculine);
  }
  return (sex_ == Physically::male ? Gender::masculine : Gender::feminine);
}


Legacy::Character::Sexuality Legacy::Character::Sexuality::
generate(Legacy::Core::Config const&,
         Legacy::Core::RandomNumberGenerator& rng)
{
  std::bernoulli_distribution sex_chooser(0.49);
  std::exponential_distribution<> bias_chooser(0.5);

  Sexuality sexuality(sex_chooser(rng) ? Sexuality::Physically::male
                                               : Sexuality::Physically::female,
                              std::min(bias_chooser(rng), 1.0),
                              1.0 - std::min(bias_chooser(rng), 1.0),
                              std::min(bias_chooser(rng), 1.0));
  return sexuality;
}


std::istream& Legacy::Character::
operator>>(std::istream& istr, Legacy::Character::Sexuality& sexuality)
{
  char c;
  istr >> c;
  sexuality.sex_ = (c == 'M' ? Sexuality::Physically::male
                             : Sexuality::Physically::female);
  istr >> sexuality.gender_bias_;
  istr >> sexuality.same_sex_pref_;
  istr >> sexuality.opposite_sex_pref_;
  return istr;
}


std::ostream& Legacy::Character::
operator<<(std::ostream& ostr, Legacy::Character::Sexuality const& sexuality)
{
  ostr << (sexuality.sex() == Sexuality::Physically::male ? 'M' : 'F') << " "
       << sexuality.gender_bias() << " "
       << sexuality.same_sex_preference() << " "
       << sexuality.opposite_sex_preference();
  return ostr;
}


bool Legacy::Character::
operator==(Sexuality const& lhs, Sexuality const& rhs)
{
  const double epsilon = 0.001;

  if (lhs.sex() != rhs.sex()) return false;
  if (lhs.gender() != rhs.gender()) return false;
  if (std::abs(lhs.gender_bias() - rhs.gender_bias()) > epsilon) return false;
  if (std::abs(lhs.same_sex_preference() - rhs.same_sex_preference()) > epsilon) return false;
  if (std::abs(lhs.opposite_sex_preference() - rhs.opposite_sex_preference()) > epsilon) return false;

  return true;
}

