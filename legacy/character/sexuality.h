/**
 * @file legacy/character/sexuality.h
 * @brief Public interface of the Legacy character sexuality submodule.
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
#ifndef LEGACY_CHARACTER_SEXUALITY_H_
#define LEGACY_CHARACTER_SEXUALITY_H_

#include <iosfwd>


namespace Legacy
{

namespace Core
{
  class Config;
  class RandomNumberGenerator;
}

namespace Character
{

/**
 * The embodiment of sexual characteristics for an individual.
 */
class Sexuality
{
public:
  enum class Physically { male, female };
  enum class Gender { masculine, feminine };

public:
  /**
   * The anatomically correct bits.
   *
   * For simplification purposes, there are only two possibilities.  It's a
   * game.
   */
  Physically
  sex() const
  { return sex_; }

  /**
   * The individual's primary social gender identity.
   *
   * Again, there are only two, because it's a game.
   */
  Gender
  gender() const;

  /**
   * The relative alignment of the individual's sex and gender on a scale of 0
   * to 1.0.  Zero would be sex and gender are aligned, 1.0 would be sex and
   * gender are opposites. Most individuals identify on a spectrum.
   */
  double
  gender_bias() const
  { return gender_bias_; }

  /**
   * The individual's attraction to their own physical sex.  Scale of 0-1.0.
   */
  double
  same_sex_preference() const
  { return same_sex_pref_; }

  /**
   * The individual's attraction to their opposite physical sex.  Scale of 0-1.0.
   */
  double
  opposite_sex_preference() const
  { return opposite_sex_pref_; }

  /**
   * Randomly generates the sexual characteristics.
   */
  static Sexuality
  generate(Core::Config const& config, Core::RandomNumberGenerator& rng);

  friend std::istream&
  operator>>(std::istream& istr, Sexuality& sex);

  friend std::ostream&
  operator<<(std::ostream& ostr, Sexuality const& sex);

private:
  Sexuality(Physically sex,
            double     gender_bias,
            double     same_sex_pref,
            double     opposite_sex_pref);

private:
  Physically sex_;
  double     gender_bias_;
  double     same_sex_pref_;
  double     opposite_sex_pref_;
};


std::istream&
operator>>(std::istream& istr, Sexuality& sex);

std::ostream&
operator<<(std::ostream& ostr, Sexuality const& sex);

bool
operator==(Sexuality const& lhs, Sexuality const& rhs);

} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_SEXUALITY_H_ */
