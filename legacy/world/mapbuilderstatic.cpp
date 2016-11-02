/**
 * @file legacy/world/mapbuilderstatic.cpp
 * @brief Implementation of the static map builder.
 */

/*
 * Copyright 2016 Stephen M. Webb <stephen.webb@bregmasoft.ca>
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
#include "legacy/world/mapbuilderstatic.h"


Legacy::World::MapBuilderStatic::
~MapBuilderStatic()
{ }

unsigned Legacy::World::MapBuilderStatic::
map_length()
{
  return 40;
}

unsigned Legacy::World::MapBuilderStatic::
map_width()
{
  return 40;
}

unsigned Legacy::World::MapBuilderStatic::
map_height()
{
  return 10;
}

Legacy::World::MapLayerBag Legacy::World::MapBuilderStatic::
layers()
{
  return Legacy::World::MapLayerBag(this->map_height(),
                        Legacy::World::MapLayer(this->map_length(), this->map_width()));
}

