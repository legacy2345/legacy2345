/**
 * @file legacy/character/statisticalnamegenerator.cpp
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
#include "legacy/character/statisticalnamegenerator.h"

#include <iostream>
#include "legacy/core/logger.h"

using Legacy::Core::LogLevel;


namespace
{
std::string
name_part_to_config_key(Legacy::Character::NameGenerator::Part part)
{
  if (part == Legacy::Character::NameGenerator::Part::surname)
  {
    return "surname-datafile";
  }
  else 
  {
    return "forename-datafile";
  }
}


std::string
default_filename_for_part(Legacy::Character::NameGenerator::Part part)
{
  if (part == Legacy::Character::NameGenerator::Part::surname)
  {
    return "dist.all.last";
  }
  else 
  {
    return "dist.female.first";
  }
}

} // anonymous namespace


Legacy::Character::StatisticalNameGenerator::
StatisticalNameGenerator(Legacy::Core::Config const&            config,
                         Legacy::Core::FileSystem const&        fs,
                         Legacy::Character::NameGenerator::Part part)
{
  std::clog << LogLevel::INFO << __PRETTY_FUNCTION__ << "() begins\n";
  std::string file_name = config.get(name_part_to_config_key(part), default_filename_for_part(part));
  std::clog << LogLevel::INFO << __PRETTY_FUNCTION__ << "() filename=\"" << file_name << "\"\n";
  auto ifs = config.open_data_file(fs, file_name);
  if (!ifs)
  {
    throw std::runtime_error("error opening dist file");
  }

  while (*ifs)
  {
    std::string name;
    double      weight;
    double      cum_weight;
    int         index;
    *ifs >> name >> weight >> cum_weight >> index;
    weights_.push_back(weight);
    names_.push_back(name);
  }
  std::clog << LogLevel::INFO << __PRETTY_FUNCTION__ << "() ends\n";
}


Legacy::Character::StatisticalNameGenerator::
~StatisticalNameGenerator()
{ }


std::string Legacy::Character::StatisticalNameGenerator::
pick_name(Legacy::Character::Sexuality::Gender,
          Legacy::Core::RandomNumberGenerator& prng)
{
  Chooser chooser(std::begin(weights_), std::end(weights_));
  return names_[chooser(prng)];
}


