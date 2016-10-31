#
# @file legacy/tests/world/Makefile.am
# @brief automake recipe for Legacy world submodule tests
#
# Copyright 2016 Stephen M. Webb  <stephen.webb@bregmasoft.ca>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

check_PROGRAMS = test_world

test_world_SOURCES = \
  test_cell.cpp \
  test_cellcache.cpp \
  test_layer.cpp \
  test_map.cpp \
  test_world.cpp 

test_world_CPPFLAGS = \
  -I$(top_srcdir) \
  -I$(top_srcdir)/legacy/tests/3rd_party

TESTS = $(check_PROGRAMS)
