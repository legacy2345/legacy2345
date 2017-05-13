/**
 * @file legacy/character/statisticalnamegenerator.h
 * @brief part of the Legacy character name submodule.
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
#ifndef LEGACY_CHARACTER_STATISTICALNAMEGENERATOR_H
#define LEGACY_CHARACTER_STATISTICALNAMEGENERATOR_H

#include "legacy/character/namegenerator.h"

#include "legacy/core/filesystem.h"
#include <random>
#include <vector>


namespace Legacy
{
namespace Character
{

/**
 * Abstract base class for various kinds of character name generators.
 */
class StatisticalNameGenerator
: public NameGenerator
{
private:
  using Weights = std::vector<double>;
  using Names   = std::vector<std::string>;
  using Chooser = std::discrete_distribution<>;

public:
  StatisticalNameGenerator(Core::Config const& config, Core::FileSystem const& fs, Part part);

  ~StatisticalNameGenerator();

  std::string
  pick_name(Sexuality::Gender            gender,
            Core::RandomNumberGenerator& rng) override;

private:
  Names    names_;
  Weights  weights_;
};


} // namespace Character
} // namespace Legacy

#endif /* LEGACY_CHARACTER_STATISTICALNAMEGENERATOR_H */
